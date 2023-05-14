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
	// ��һ������duc����λ���Ժ�VS��һ�£�����samples��������ԣ�Ӧ�ö�Ϊ0(�����ź�)�����ǲ�Ӱ��������ͣ���ʱ���ܡ�
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
	// coded��Ϊ�������ɵ����ݰ�(ǰ����+���߰�+��ѡ�غɰ�)���׵�ַ
	coded = JANUS_UTILS_MEMORY_NEW(janus_uint8_t, chip_count);
	// coded_ptr��Ϊÿһ�׶δ�����׵�ַ����������������
	coded_ptr = coded;

	// -------------------------���ﴦ��32λ��ǰ����-------------------------
	coded_ptr += JANUS_PREAMBLE_CHIP_COUNT;
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 24, coded);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 16, coded + 8);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 8, coded + 16);
	janus_utils_dec2bin_byte(tx->pset->c32_sequence >> 0, coded + 24);
	// ----------------------------end----------------------------------

	// ���ݰ���������CRC8����֤��CRC������������JANUS���߰���56λ֮�����������64λ�������ݰ�
	janus_packet_set_crc(packet);

	// ------------------���л��߰��ķֽ⡢�������ͽ�֯------------------------
	pkt = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, tx->pkt_bits);
	// �����߰��ֽ��0/1�룬���߰���64λ������֮ǰҪ��64λ���߰��󸽼�8��0������ձ������ʽ�����㻺��������72λ
	janus_utils_dec2bin(janus_packet_get_bytes(packet), JANUS_MIN_PKT_SIZE, pkt);
	// ������õ���72λ�����о�����룬�õ�144�����ŵľ�������
	pkt_conv = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, tx->pkt_chip_count);
	janus_convolve(trellis, pkt, tx->pkt_bits, pkt_conv);
	// JANUS_UTILS_MEMORY_FREE(pkt);
	// �Ծ�����������ʱ�佻֯
	janus_interleave(pkt_conv, tx->pkt_chip_count, coded_ptr);
	// JANUS_UTILS_MEMORY_FREE(pkt_conv);
	coded_ptr += tx->pkt_chip_count;
	// ----------------------------------end--------------------------------------


	// ------------------���л��߰��ķֽ⡢�������ͽ�֯------------------------
	if (dat_bits)
	{
		dat = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, dat_bits);
		// ��cargo���ֽ�Ϊ0/1��
		janus_utils_dec2bin(janus_packet_get_cargo(packet), dat_len, dat);
		dat_conv = JANUS_UTILS_MEMORY_NEW_ZERO(janus_uint8_t, dat_chip_count);
		// ��cargo��0/1������о������
		janus_convolve(trellis, dat, dat_bits, dat_conv);
		// JANUS_UTILS_MEMORY_FREE(dat);
		// ��cargo�ľ����������н�֯
		janus_interleave(dat_conv, dat_chip_count, coded_ptr);
		// JANUS_UTILS_MEMORY_FREE(dat_conv);
	}
	// -----------------------------end-------------------------------

	// ��ֹ���ϣ�ǰ���롢���߰������ݰ��Ѿ�����Ϊ�����͵ı�����(��֤ͨ��)

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
		// ��һ��ִ�з��ͣ����а����ϱ�Ƶ�����ƻ�ʵ�ַ�ʽ��
		// 1.�Ƚ��е�chip���ϱ�Ƶ��Ȼ������ƴ�Ӳ���
		// 2.ͳһ���Ͳ��Σ���ƿ��������Ƶ���ͣ�------> ���뷨ʧ�ܣ�������һ����ʱ�ܲ�ͨ���Ծ���Ҫ��chip���ͣ���
		janus_duc_execute(tx->duc, out, rv, samples_out);

		for (k = 0; k < rv; k++)
		{
			output[idx++] = (short)(amp * samples_out[k]);
			output[idx++] = (short)(amp * samples_out[k]);
		}
	}
	*len_output = idx;

}
