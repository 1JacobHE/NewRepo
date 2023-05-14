/*
 * block.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */
#ifndef _BLOCK_C_
#define _BLOCK_C_

#include <block.h>

block_p block_new(param_p pa) {
	block_p block = JANUS_UTILS_MEMORY_NEW_ZERO(struct block, 1);

	block->pilot_scheme=pa->pilot_scheme;
	block->pilot_length=pa->pilot_length;
	block->guard_interval=pa->guard_interval;
	
	return block;
}

void block_load_pilot(MODEM_uint16_p start, MODEM_real_p* output)
{
    FILE* file = fopen("Fs44100/block_pilot.txt", "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    MODEM_uint16_p i = 0;
    while (fscanf(file, "%lf", &output[i + start]) != EOF) {
        i++;
    }

    fclose(file);
}

void block_set_guard(MODEM_uint16_p guard_interval, MODEM_uint16_p oversampling_factor, MODEM_uint32_p start, MODEM_real_p* output)
{
    MODEM_uint16_p samples = guard_interval * oversampling_factor;

    MODEM_uint16_p i;
    for (i = 0; i < samples; i++) {
        output[i + start] = 0;
    }
}

void block_free(block_p block) {
	MODEM_UTILS_MEMORY_FREE(block);
}

#endif
