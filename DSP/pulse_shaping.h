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
#include <math.h>
#include <MODEM_complex.h>
#include <MODEM_types.h>

struct pulse_shaping{
	const char* pulse_shaping;
};

typedef struct pulse_shaping* pulse_shaping_p;

pulse_shaping_p pulse_shaping_new(param_p pa);

void root_raised_cosine(MODEM_real_p* csf, MODEM_uint16_p Nb, MODEM_real_p beta);

void pulse_shaping_shape(MODEM_complex_p* symbol, MODEM_complex_p* shaped_symbol, MODEM_uint16_p filter_length); // input one symbol, output one shaped symbol

void pulse_shaping_free(pulse_shaping_p ps);


#endif