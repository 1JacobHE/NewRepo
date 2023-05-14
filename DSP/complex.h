#ifndef MODEM_COMPLEX_H_INCLUDED_
#define MODEM_COMPLEX_H_INCLUDED_

#include <MODEM/types.h>

typedef MODEM_real_t MODEM_complex_t[2];

void
MODEM_complex_new(const MODEM_real_t a, const MODEM_real_t b, MODEM_complex_t c);

void
MODEM_complex_assign(const MODEM_complex_t x, MODEM_complex_t r);

void
MODEM_complex_sum(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r);

void
MODEM_complex_sub(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r);

void
MODEM_complex_mul(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r);

MODEM_real_t
MODEM_complex_abs(const MODEM_complex_t nr);

MODEM_real_t
MODEM_complex_abs_sqr(const MODEM_complex_t nr);

void
MODEM_complex_conj(const MODEM_complex_t x, MODEM_complex_t r);

void
MODEM_complex_jexp(const MODEM_hiprecision_t x, MODEM_complex_t r);

void
MODEM_complex_sum_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r);

void
MODEM_complex_sub_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r);

void
MODEM_complex_mul_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r);

void
MODEM_complex_print(const MODEM_complex_t x);

#endif
