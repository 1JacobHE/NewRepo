/*
 * MODEM_tx.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#include <MODEM_tx.h>

MODEM_tx_execute(param_p param, MIMO_p MIMO, frame_p frame, block_p block, ofdm_block_p ofdm_block, channel_coding_p channel_coding, 
	constellation_p constellation, pulse_shaping_p pulse_shaping, stream_p stream, unsigned short* output, int* len_output)
{
	unsigned dat_len = janus_packet_get_cargo_size(packet);
	unsigned dat_bits = (dat_len == 0) ? 0 : ((dat_len + JANUS_CONV_MEM_SIZE) * 8);
	unsigned dat_chip_count = dat_bits * JANUS_ALPHABET_SIZE;
	unsigned chip_count = JANUS_PREAMBLE_CHIP_COUNT + tx->pkt_chip_count + dat_chip_count;
	unsigned sample_count = 0;
	janus_uint8_t* coded = NULL;
	janus_uint8_t* coded_ptr = NULL;
	janus_uint8_t* pkt = NULL;
	janus_uint8_t* pkt_conv = NULL;
	janus_uint8_t* dat = NULL;
	janus_uint8_t* dat_conv = NULL;
	janus_trellis_t trellis = janus_trellis_default();

	// transmit prologue silence
	//	if(tx->pad)
	//	{
	//		// write_silence(tx->ostream,tx->pad_size);
	//		sample_count+=tx->pad_size;
	//	}
	// 这一步调整duc的相位，以和VS中一致，但是samples的输出不对，应该都为0(静音信号)，但是不影响后续发送，暂时不管。
	janus_real_t* P_to_be_dealt;
	janus_complex_t tmp = { 0 };
	unsigned j;
	for (j = 0; j < tx->pad_size; j++)
	{
		janus_duc_execute(tx->duc, &tmp, 1, P_to_be_dealt);
		//		printf("%.3f ", samples_out[j]);
	}



	// transmit optional wake-up tones
	//	if(tx->wut)
	//	{
	// janus_wake_up_tones(tx->ostream,tx->pset->ubwidth,tx->pset->chip_dur);
	// sample_count+=rv;

	// write_silence(tx->ostream,(unsigned)(JANUS_WUT_GAP*tx->ostream->fs));
	// sample_count+=tx->pad_size;
	//	}

	// Prepare output memory.
	// coded作为最后处理完成的数据包(前导码+基线包+可选载荷包)的首地址
	coded = JANUS_UTILS_MEMORY_NEW(janus_uint8_t, chip_count);
	// coded_ptr作为每一阶段处理的首地址，用以连接三个包
	coded_ptr = coded;

	// -------------------------这里处理32位的前导码-------------------------
	coded_ptr += JANUS_PREAMBLE_CHIP_COUNT;
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 24, coded);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 16, coded + 8);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 8, coded + 16);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 0, coded + 24);
	// ----------------------------end----------------------------------

	// 数据包完整性由CRC8来保证，CRC计算结果附加在JANUS基线包的56位之后，组成完整的64位基线数据包
	janus_packet_set_crc(packet);

	// ------------------进行基线包的分解、卷积编码和交织------------------------
	pkt = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, tx->pkt_bits);
	// 将基线包分解成0/1码，基线包共64位，编码之前要在64位基线包后附加8个0用于清空编码多项式的运算缓冲区，共72位
	janus_utils_dec2bin(janus_packet_get_bytes(packet), JANUS_MIN_PKT_SIZE, pkt);
	// 对上面得到的72位包进行卷积编码，得到144个符号的卷积编码包
	pkt_conv = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, tx->pkt_chip_count);
	janus_convolve(trellis, pkt, tx->pkt_bits, pkt_conv);
	// JANUS_UTILS_MEMORY_FREE(pkt);
	// 对卷积编码包进行时间交织
	janus_interleave(pkt_conv, tx->pkt_chip_count, coded_ptr);
	// JANUS_UTILS_MEMORY_FREE(pkt_conv);
	coded_ptr += tx->pkt_chip_count;
	// ----------------------------------end--------------------------------------


	// ------------------进行基线包的分解、卷积编码和交织------------------------
	if (dat_bits)
	{
		dat = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, dat_bits);
		// 将cargo包分解为0/1码
		janus_utils_dec2bin(janus_packet_get_cargo(packet), dat_len, dat);
		dat_conv = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, dat_chip_count);
		// 对cargo的0/1码包进行卷积编码
		janus_convolve(trellis, dat, dat_bits, dat_conv);
		// JANUS_UTILS_MEMORY_FREE(dat);
		// 对cargo的卷积编码包进行交织
		janus_interleave(dat_conv, dat_chip_count, coded_ptr);
		// JANUS_UTILS_MEMORY_FREE(dat_conv);
	}
	// -----------------------------end-------------------------------

	// 截止以上，前导码、基线包和数据包已经处理为待发送的比特流(验证通过)

	// modulate data and generate the waveform
	janus_complex_t* out = NULL;
	unsigned i, k;
	janus_real_t* samples_out;
	unsigned chip_len = (unsigned)(tx->modulator->chip_len_factor + 1);
	samples_out = calloc(chip_len, sizeof(double));
	int idx = 0, idx2 = 0;
	short amp = (short)(32768);

	for (i = 0; i < chip_count; ++i)
	{
		unsigned rv = janus_modulator_execute(tx->modulator, coded[i], &out);
		//	janus_ostream_write(tx->ostream,out,rv)
		// 这一步执行发送，其中包含上变频处理。计划实现方式：
		// 1.先进行单chip的上变频，然后依次拼接波形
		// 2.统一发送波形（设计开发板的音频发送）------> （想法失败，仿真这一步暂时跑不通，仍旧需要单chip发送）。
		janus_duc_execute(tx->duc, out, rv, samples_out);

		for (k = 0; k < rv; k++)
		{
			output[idx++] = (short)(amp * samples_out[k]);
			output[idx++] = (short)(amp * samples_out[k]);
		}
	}
	*len_output = idx;

}
