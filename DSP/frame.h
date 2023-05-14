/*
 * frame.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _FRAME_H_
#define _FRAME_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <MODEM_types.h>
#include <stdlib.h>

struct frame{
	MODEM_uint16_p 		max_blocks_per_frame;
	MODEM_uint32_p 		center_frequency;
	MODEM_uint16_p 		wakeup_tone_frequency;
	MODEM_uint16_p 		wakeup_tone_length;
	const char* 		leading1;
	const char* 		leading2;	
	MODEM_real_p 		pad_length;
};

typedef struct frame* frame_p;

frame_p frame_new(param_p pa);

void frame_load_wakeup_tone(MODEM_uint16_p wakeup_tone_length, MODEM_uint32_p sampling_frequency, MODEM_uint32_p start, MODEM_real_p* output);

void frame_load_leading1(MODEM_uint32_p start, MODEM_real_p* output);

void frame_load_leading2(MODEM_uint32_p start, MODEM_real_p* output);

void frame_set_pad(MODEM_uint16_p pad_length, MODEM_uint16_p oversampling_factor, MODEM_uint32_p start, MODEM_real_p* output);

void frame_free(frame_p frame);

#endif /* FRAME_H_ */
