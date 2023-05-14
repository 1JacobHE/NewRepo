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

void block_load_pilot(short* pilot)
{
	aaa;
}

void block_free(block_p block) {
	MODEM_UTILS_MEMORY_FREE(block);
}

#endif
