/*
 * MIMO.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _MIMO_C_
#define _MIMO_C_

#include <MIMO.h>

MIMO_p
MIMO_new(param_p pa)
{
	MIMO_p mimo = MODEM_UTILS_MEMORY_NEW_ZERO(struct MIMO, 1);

    mimo->transducers=pa->transducers;
    mimo->hydrophones=pa->hydrophones;

    return mimo;
}

void MIMO_free(MIMO_p mimo)
{
    MODEM_UTILS_MEMORY_FREE(mimo);
}

#endif