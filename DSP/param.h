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
#include <MODEM_types.h>

struct param{
	//frame params
	MODEM_uint16_p 	max_block_per_frame;
	MODEM_uint32_p 	center_frequency;
	MODEM_uint16_p 	wakeup_tone_frequency;
	MODEM_uint16_p 	wake_up_tone_length; //in seconds
	const char*  	leading1;
	const char*  	leading2;
	MODEM_real_p    pad_length; //in seconds

	//MIMO params
	MODEM_uint16_p 	transducers;
	MODEM_uint16_p 	hydrophones;

	//modulation params
	const char* 	baseband_modulation_mode;

	//OFDM params
	MODEM_real_p 	ofdm_bandwidth;
	MODEM_uint16_p 	ofdm_subcarrier_number;
	MODEM_uint16_p 	ofdm_data_subcarrier_number;
	MODEM_uint16_p 	ofdm_pilot_subcarrier_number;
	MODEM_uint16_p 	ofdm_null_subcarrier_number;
	const char* 	ofdm_pattern;
	const char* 	ofdm_precoding;
	MODEM_uint16_p 	ofdm_zpcp; //1 for zp, 0 for cp
	MODEM_uint16_p 	ofdm_zpcp_length; //in 1/bandwidth

	//block params
	const char*		pilot_scheme;
	MODEM_uint16_p 	pilot_length; //in 1/bandwidth
	MODEM_uint16_p 	guard_interval;

	//channel coding params
	const char*		channel_coding_scheme;
	MODEM_real_p 	channel_coding_rate;
	MODEM_uint16_p 	interleave_enable;

	//constellation params
	const char* 	constellation_scheme;

	//pulse shaping params
	const char*		pulse_shaping_scheme;

	//stream params
	MODEM_uint32_p 	sampling_frequency;
};

typedef struct param* param_p;

param_p param_new(void);

void param_free(param_p pa);



#endif /* PARAM_H_ */
