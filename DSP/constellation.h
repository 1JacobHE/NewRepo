/*
 * constellation.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _CONSTELLATION_H_
#define _CONSTELLATION_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <stdlib.h>

struct constellation
{
    const char      constellation_scheme;
    int             bits_per_symbol;
};

typedef struct constellation* constellation_p;

constellation_p constellation_new(param_p pa);

void constellation_constellate();// input bits, output symbols, by block

void constellation_free(constellation_p cm);


#endif /* CONSTELLATION_MAP_H_ */
