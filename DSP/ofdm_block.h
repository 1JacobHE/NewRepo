/*
 * ofdm_block.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _OFDM_BLOCK_H_
#define _OFDM_BLOCK_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <MODEM_types.h>
#include <stdlib.h>
#include <MODEM_complex.h>
#include <stdio.h>
#include <fftw3.h>

//--------------------------------------------------------
struct ofdm_block{
	MODEM_real_p 		bandwidth;
	MODEM_uint16_p 		subcarrier_number;
	MODEM_uint16_p 		data_subcarrier_number;
	MODEM_uint16_p 		pilot_subcarrier_number;
	MODEM_uint16_p 		null_subcarrier_number;
	const char* 		subcarrier_pattern;
	const char* 		precoding;
	const char* 		ZPorCP;
	MODEM_uint16_p 		ZPorCP_length;
};

typedef struct ofdm_block* ofdm_block_p;

ofdm_block_p ofdm_block_new(param_p pa);

void ofdm_block_add_ZPorCP(char* ZPorCP, MODEM_uint16_p ZPorCP_length, MODEM_uint16_p oversamping_factor, MODEM_uint16_p input_size, MODEM_complex_p* input, MODEM_complex_p* output);

void ofdm_block_precoding(MODEM_uint16_p K, MODEM_complex_p* input, MODEM_complex_p* output);

void ofdm_block_ifft(MODEM_uint16_p ifft_size, MODEM_complex_p* input, MODEM_complex_p* output);

void ofdm_block_free(ofdm_block_p block);


#endif /* OFDM_BLOCK_H_ */
