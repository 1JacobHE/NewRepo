/*
 * param.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _PARAM_C_
#define _PARAM_C_

#include <param.h>

param_p param_new(void) {
	param_p pa = JANUS_UTILS_MEMORY_NEW_ZERO(struct param, 1);

	char filename[]="param.csv";
	FILE* fd=fopen(filename,"r");
	int matches=0;

	if(fd==NULL) return JANUS_ERROR_FILE;

	while(!feof(fd)) {
		matches=fscanf(fd,"%u, %u, %u, %u, %u, %25, %25, %d,"
						"%u, %u,"
						"%25,"
						"%d, %u, %u, %u, %u, %25, %25, %25, %u,"
						"%25, %u, %u,"
						"%25, %d, %u,"
						"%25,"
						"%25,"
						"%l [^\n]\n",
						&pa->max_block_per_frame,
						&pa->center_frequency,
						&pa->wakeup_tone_frequency,
						&pa->wakeup_tone_length,
						pa->leading1,
						pa->leading2,
						&pa->pad_length,

						&pa->transducers,
						&pa->hydrophones,

						pa->baseband_modulation_mode,

						&pa->ofdm_bandwidth,
						&pa->ofdm_subcarrier_number,
						&pa->ofdm_data_subcarrier_number,
						&pa->ofdm_pilot_subcarrier_number,
						&pa->ofdm_null_subcarrier_number,
						pa->ofdm_pattern,
						pa->ofdm_precoding,
						&pa->ofdm_zpcp,
						&pa->ofdm_zpcp_length,

						pa->pilot_scheme,
						&pa->guard_interval,
						&pa->pilot_length,

						pa->channel_coding_scheme,
						&pa->channel_coding_rate,
						&pa->interleave_enable,

						pa->constellation_scheme,

						pa->pulse_shaping_scheme,

						&pa->sampling_frequency,
						)
		if(matches!=28) {
			matches=fscanf(fd, "%*[^\n]\n");
			continue;
		}
	}
	fclose(fd);
	return pa;
}

void param_free(param_p pa) {
	MODEM_UTILS_MEMORY_FREE(pa);
}

#endif