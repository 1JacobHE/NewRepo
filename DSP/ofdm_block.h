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

//--------------------------------------------------------
struct ofdm_block{
	double 				bandwidth;
	unsigned int 		subcarrier_number;
	unsigned int 		data_subcarrier_number;
	unsigned int 		pilot_subcarrier_number;
	unsigned int 		null_subcarrier_number;
	const char* 		subcarrier_pattern;
	const char* 		precoding;
	const char* 		ZPorCP;
	unsigned int 		ZPorCP_length;
};

typedef struct ofdm_block* ofdm_block_p;

ofdm_block_p ofdm_block_new(param_p pa);

void ofdm_block_free(ofdm_block_p block);


#endif /* OFDM_BLOCK_H_ */
