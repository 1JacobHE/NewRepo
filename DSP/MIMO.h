/*
 * MIMO.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _MIMO_H_
#define _MIMO_H_

#include <param.h>

#include <memory.h>
#include <stdlib.h>

//--------------------------------------------------------
struct MIMO{
	unsigned int transducers;
    unsigned int hydrophones;
};

typedef struct MIMO* MIMO_p;

MIMO_p
MIMO_new(param_p pa);

void
MIMO_free(MIMO_p mimo);

#endif
