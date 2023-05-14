#ifndef MODEM_INTERLEAVE_H_INCLUDED_
#define MODEM_INTERLEAVE_H_INCLUDED_

#include <types.h>

void
MODEM_interleave(const MODEM_uint8_t* inp, unsigned inp_len, MODEM_uint8_t* out);

unsigned
MODEM_interleave_q(unsigned length);

#endif
