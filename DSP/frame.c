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

void frame_load_wakeup_tone(unsigned int wakeup_tone_length, unsigned int sampling_frequency, unsigned int start, MODEM_real_p* output)
{
	unsigned int samples = wakeup_tone_length * sampling_frequency;

	FILE* file = fopen("Fs44100\wakeup_tone.txt", "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		return;
	}

	unsigned int i = 0;
	while (fscanf(file, "%lf", &output[i + start]) != EOF && i < samples) {
		i++;
	}

	fclose(file);
}

void frame_load_leading1(unsigned int start, MODEM_real_p* output)
{
	FILE* file = fopen("Fs44100\LFM.txt", "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		return;
	}

	unsigned int i = 0;
	while (fscanf(file, "%lf", &output[i + start]) != EOF) {
		i++;
	}

	fclose(file);
}

void frame_load_leading2(unsigned int start, MODEM_real_p* output)
{
	FILE* file = fopen("Fs44100\mSeq.txt", "r");
	if (file == NULL) {
		printf("Failed to open the file.\n");
		return;
	}

	unsigned int i = 0;
	while (fscanf(file, "%lf", &output[i + start]) != EOF) {
		i++;
	}

	fclose(file);
}

void frame_set_pad(unsigned int pad_length, unsigned int oversampling_factor, unsigned int start, MODEM_real_p* output)
{
	int samples = pad_length * oversampling_factor;

	unsigned int i;
	for (i = 0; i < samples; i++) {
		output[i + start] = 0;
	}
}

void frame_free(frame_p frame)
{
  MODEM_UTILS_MEMORY_FREE(frame);
}

#endif



