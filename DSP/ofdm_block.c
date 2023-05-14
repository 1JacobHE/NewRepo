/*
 * ofdm_block.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _OFDM_BLOCK_C_
#define _OFDM_BLOCK_C_

#include <ofdm_block.h>

ofdm_block_p ofdm_block_new(param_p pa)
{
	ofdm_block_p block = MODEM_UTILS_MEMORY_NEW_ZERO(struct ofdm_block, 1);

	block->bandwidth = pa->ofdm_bandwidth;
	block->subcarrier_number = pa->ofdm_subcarrier_number;
	block->data_subcarrier_number=pa->ofdm_data_subcarrier_number;
	block->pilot_subcarrier_number = pa->ofdm_pilot_subcarrier_number;
	block->null_subcarrier_number=pa->ofdm_null_subcarrier_number;
	block->subcarrier_pattern=pa->ofdm_pattern;
	block->precoding=pa->ofdm_precoding;
	block->ZPorCP=pa->ofdm_zpcp;
	block->ZPorCP_length=pa->ofdm_zpcp_length;

	return block;
}

void ofdm_block_add_ZPorCP(char* ZPorCP, unsigned int ZPorCP_length, unsigned int oversmpling_factor, MODEM_complex_p** input, MODEM_complex_p** output)
{

}

void ofdm_block_precoding(unsigned int K, MODEM_complex_p** input, MODEM_complex_p** output)
{

}

void ofdm_block_ifft(unsigned int ifft_size, MODEM_complex_p** input, MODEM_complex_p** output)
{

}

void ofdm_block_free(ofdm_block_p block)
{
  MODEM_UTILS_MEMORY_FREE(block);
}

#endif



