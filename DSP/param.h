/*
 * param.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _PARAM_H_
#define _PARAM_H_

#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct param{
	//frame params
	unsigned int 	max_block_per_frame;
	unsigned int 	center_frequency;
	unsigned int 	wakeup_tone_frequency;
	unsigned int 	wake_up_tone_length; //in seconds
	const char*  	leading1;
	const char*  	leading2;
	double       	pad_length; //in seconds

	//MIMO params
	unsigned int 	transducers;
	unsigned int 	hydrophones;

	//modulation params
	const char* 	baseband_modulation_mode;

	//OFDM params
	double 			ofdm_bandwidth;
	unsigned int 	ofdm_subcarrier_number;
	unsigned int 	ofdm_data_subcarrier_number;
	unsigned int 	ofdm_pilot_subcarrier_number;
	unsigned int 	ofdm_null_subcarrier_number;
	const char* 	ofdm_pattern;
	const char* 	ofdm_precoding;
	unsigned int 	ofdm_zpcp; //1 for zp, 0 for cp
	unsigned int 	ofdm_zpcp_length; //in 1/bandwidth

	//block params
	const char*		pilot_scheme;
	unsigned int 	pilot_length; //in 1/bandwidth
	unsigned int 	guard_interval;

	//channel coding params
	const char*		channel_coding_scheme;
	double 			channel_coding_rate;
	unsigned int 	interleave_enable;

	//constellation params
	const char* 	constellation_scheme;

	//pulse shaping params
	const char*		pulse_shaping_scheme;

	//stream params
	long 			sampling_frequency;
};

typedef struct param* param_p;

param_p param_new(void);

void param_free(param_p pa);



#endif /* PARAM_H_ */
