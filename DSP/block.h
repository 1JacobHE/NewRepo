/*
 * block.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <MODEM_types.h>

struct block{
	const char* 		pilot_scheme;
	unsigned int 		pilot_length;
	unsigned int 		guard_interval;
};

typedef struct block* block_p;

block_p block_new(param_p pa);

void block_load_pilot(unsigned int pilot_length, unsigned int oversampling_factor, unsigned int start, MODEM_real_p* output);

void block_set_guard(unsigned int guard_interval, unsigned int oversampling_factor, unsigned int start, MODEM_real_p* output);

void block_free(block_p block);


#endif /* BLOCK_H_ */
