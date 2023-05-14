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

//--------------------------------------------------------
struct block{
	const char* 		pilot_scheme;
	unsigned int 		pilot_length;
	unsigned int 		guard_interval;
};

typedef struct block* block_p;

block_p block_new(param_p pa);

void block_load_pilot(short* pilot); // 将指针添加pilot后返回

void block_free(block_p block);


#endif /* BLOCK_H_ */
