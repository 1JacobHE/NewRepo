#ifndef MODEM_COMPLEX_H_INCLUDED_
#define MODEM_COMPLEX_H_INCLUDED_

#include <MODEM_types.h>

#include <stdlib.h>
#include <MODEM_types.h>

typedef MODEM_real_p MODEM_complex_p[2];

void
MODEM_complex_new(const MODEM_real_p a, const MODEM_real_p b, MODEM_complex_p c);

void
MODEM_complex_assign(const MODEM_complex_p x, MODEM_complex_p r);

void
MODEM_complex_sum(const MODEM_complex_p x, const MODEM_complex_p y, MODEM_complex_p r);

void
MODEM_complex_sub(const MODEM_complex_p x, const MODEM_complex_p y, MODEM_complex_p r);

void
MODEM_complex_mul(const MODEM_complex_p x, const MODEM_complex_p y, MODEM_complex_p r);

MODEM_real_p
MODEM_complex_abs(const MODEM_complex_p nr);

MODEM_real_p
MODEM_complex_abs_sqr(const MODEM_complex_p nr);

void
MODEM_complex_conj(const MODEM_complex_p x, MODEM_complex_p r);

void
MODEM_complex_jexp(const MODEM_hiprecision_p x, MODEM_complex_p r);

void
MODEM_complex_sum_real(const MODEM_complex_p x, const MODEM_real_p y, MODEM_complex_p r);

void
MODEM_complex_sub_real(const MODEM_complex_p x, const MODEM_real_p y, MODEM_complex_p r);

void
MODEM_complex_mul_real(const MODEM_complex_p x, const MODEM_real_p y, MODEM_complex_p r);

void
MODEM_complex_print(const MODEM_complex_p x);

#endif
