/*
 * channel_coding.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _CHANNLE_CODING_H_
#define _CHANNLE_CODING_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <MODEM_types.h>

struct channel_coding
{
    const char*         channel_coding;
    double              code_rate;
    MODEM_uint16_p        interleave_enable;
};

typedef struct channel_coding* channel_coding_p;

channel_coding_p channel_coding_new(param_p pa);

MODEM_uint16_p MODEM_utils_primes_is_prime(MODEM_uint16_p nr);

MODEM_uint16_p MODEM_utils_primes_get_previous(MODEM_uint16_p nr);

MODEM_uint16_p MODEM_interleave_q(MODEM_uint16_p length);

void channel_coding_convolve(const MODEM_uint8_p* inp, MODEM_uint16_p inp_len, MODEM_uint8_p* out);

void channel_coding_ldpc();

void channel_coding_interleave(const MODEM_uint8_p* inp, MODEM_uint16_p inp_len, MODEM_uint8_p* out);

void channel_coding_free(channel_coding_p cs);


#endif /* CHANNLE_CODING_H_ */
