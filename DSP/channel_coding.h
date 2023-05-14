/*
 * channel_coding.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _CHANNLE_CODING_H_
#define _CHANNLE_CODING_H_

#include <param.h>

#include <trellis.h>
#include <interleave.h>

#include <memory.h>
#include <string.h>
#include <stdlib.h>

struct channel_coding
{
    const char*         channel_coding;
    double              code_rate;
    unsigned int        interleave_enable;
};

typedef struct channel_coding* channel_coding_p;

channel_coding_p channel_coding_new(param_p pa);

void channel_coding_convolve(const MODEM_trellis_t trellis, const MODEM_uint8_t* inp, unsigned inp_len, MODME_uint8_t* out);

void channel_coding_ldpc();

void channel_coding_interleave(const MODEM_uint8_t* inp, unsigned inp_len, MODEM_uint8_t* out);

void channel_coding_free(channel_coding_p cs);


#endif /* CHANNLE_CODING_H_ */
