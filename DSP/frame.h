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

//--------------------------------------------------------
struct frame{
	unsigned int 		max_blocks_per_frame;
	long long 			center_frequency;
	unsigned int 		wakeup_tone_frequency;
	unsigned int 		wakeup_tone_length;
	const char* 		leading1;
	const char* 		leading2;	
	double 				pad_length;
};

typedef struct frame* frame_p;

frame_p frame_new(param_p pa);

void frame_load_wakeup_tone(short* wut); // 将指针填充wut后返回

void frame_load_leading1(short* lead); // 将指针填充leading1后返回

void frame_load_leading2(short* lead); // 将指针填充leading2后返回

void frame_set_pad(short* pad); // 将指针填充pad后返回

void frame_free(frame_p frame);

#endif /* FRAME_H_ */
