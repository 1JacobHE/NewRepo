/*
 * pulse_shaping.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _PULSE_SHAPING_H_
#define _PULSE_SHAPING_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <stdlib.h>

//--------------------------------------------------------
struct pulse_shaping{
	const char* pulse_shaping;
};

typedef struct pulse_shaping* pulse_shaping_p;

pulse_shaping_p pulse_shaping_new(param_p pa);

void pulse_shaping_shape(); // input one symbol, output one shaped symbol

void pulse_shaping_free(pulse_shaping_p ps);


#endif