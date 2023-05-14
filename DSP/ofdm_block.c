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

void ofdm_block_add_ZPorCP(char* ZPorCP, unsigned int ZPorCP_length_in_sample, unsigned int input_size, MODEM_complex_p** input, MODEM_complex_p** output)
{
	int i = 0;
	if (strcmp(ZPorCP, "ZP")) {
		for (i = 0; i < ZPorCP_length_in_sample; i++) {
			output[i][0] = 0;
			output[i][1] = 0;
		}
	}
	else if (strcmp(ZPorCP, "CP")) {
		for (i = 0; i < ZPorCP_length_in_sample; i++) {
			output[i][0] = input[i + input_size - ZPorCP_length_in_sample][0];
			output[i][1] = input[i + input_size - ZPorCP_length_in_sample][1];
		}
	}
	for (i = 0; i < input_size; i++) {
		output[i + ZPorCP_length_in_sample][0] = input[i][0];
		output[i + ZPorCP_length_in_sample][1] = input[i][1];
	}
}

void ofdm_block_precoding(unsigned int K, MODEM_complex_p** input, MODEM_complex_p** output)
{
		FILE* file = fopen("precoding_matrix.txt", "r");
		if (file == NULL) {
			printf("Failed to open file.\n");
			return;
		}

		MODEM_complex_p** matrix = (MODEM_complex_p**)malloc(K * sizeof(MODEM_complex_p));
		MODEM_complex_p* temp = (MODEM_complex_p*)malloc(sizeof(MODEM_complex_p));

		for (int i = 0; i < K; ++i) {
			for (int j = 0; j < K; ++j) {
				fscanf(file, "%lf, %lf", &matrix[j][0], &matrix[j][1]);
			}
			output[i][0] = 0;
			output[i][1] = 0;
			for (int j = 0; j < K; ++j) {
				MODEM_complex_mul(input[i], matrix[i], temp);
				output[i][0] += temp[0];
				output[i][1] += temp[1];
			}
		}

		fclose(file);
		free(matrix);
		free(temp);
}

void ofdm_block_ifft(unsigned int ifft_size, MODEM_complex_p** input, MODEM_complex_p** output)
{

}

void ofdm_block_free(ofdm_block_p block)
{
  MODEM_UTILS_MEMORY_FREE(block);
}

#endif



