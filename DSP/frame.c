/*
 * frame.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _FRAME_C_
#define _FRAME_C_

#include <frame.h>

frame_p frame_new(param_p pa)
{
	frame_p frame = MODEM_UTILS_MEMORY_NEW_ZERO(struct frame, 1);

	frame->max_blocks_per_frame = pa->max_block_per_frame;
	frame->center_frequency = pa->center_frequency;
	frame->wakeup_tone_frequency = pa->wakeup_tone_frequency;
	frame->wakeup_tone_length = pa->wake_up_tone_length;
	frame->leading1=pa->leading1;
	frame->leading2=pa->leading2;
	frame->pad_length=pa->pad_length;

	return frame;
}

void frame_load_wakeup_tone(short* wut)
{

}

void frame_load_leading1(short* lead)
{

}

void frame_load_leading2(short* lead)
{

}

void frame_set_pad(short* pad)
{
	
}

void frame_free(frame_p frame)
{
  MODEM_UTILS_MEMORY_FREE(frame);
}

#endif



