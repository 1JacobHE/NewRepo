#ifndef MODEM_COMPLEX_C_INCLUDED_
#define MODEM_COMPLEX_C_INCLUDED_
#include <MODEM/complex.h>
#include <stdlib.h>

void
MODEM_complex_new(const MODEM_real_t a, const MODEM_real_t b, MODEM_complex_t c)
{
  c[0] = a;
  c[1] = b;
}

void
MODEM_complex_assign(const MODEM_complex_t x, MODEM_complex_t r)
{
  r[0] = x[0];
  r[1] = x[1];
}

void
MODEM_complex_sum(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r)
{
  r[0] = x[0] + y[0];
  r[1] = x[1] + y[1];
}

void
MODEM_complex_sub(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r)
{
  r[0] = x[0] - y[0];
  r[1] = x[1] - y[1];
}

void
MODEM_complex_mul(const MODEM_complex_t x, const MODEM_complex_t y, MODEM_complex_t r)
{
  MODEM_real_t amc = (x[0] * y[0]);
  MODEM_real_t bmd = (x[1] * y[1]);
  MODEM_real_t apbmcpd = (x[0] + x[1]) * (y[0] + y[1]);

  r[0] = amc - bmd;
  r[1] = apbmcpd - amc - bmd;
}

MODEM_real_t
MODEM_complex_abs(const MODEM_complex_t nr)
{
  return MODEM_SQRT(nr[0] * nr[0] + nr[1] * nr[1]);
}

MODEM_real_t
MODEM_complex_abs_sqr(const MODEM_complex_t nr)
{
  return nr[0] * nr[0] + nr[1] * nr[1];
}

void
MODEM_complex_conj(const MODEM_complex_t x, MODEM_complex_t r)
{
  r[0] = x[0];
  r[1] = -x[1];
}

void
MODEM_complex_jexp(const MODEM_hiprecision_t x, MODEM_complex_t r)
{
  r[0] = MODEM_HP_COS(x);
  r[1] = MODEM_HP_SIN(x);
}

void
MODEM_complex_sum_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r)
{
  r[0] = x[0] + y;
  r[1] = x[1];
}

void
MODEM_complex_sub_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r)
{
  r[0] = x[0] - y;
  r[1] = x[1];
}

void
MODEM_complex_mul_real(const MODEM_complex_t x, const MODEM_real_t y, MODEM_complex_t r)
{
  r[0] = x[0] * y;
  r[1] = x[1] * y;
}

void
MODEM_complex_print(const MODEM_complex_t x)
{
	printf("%.2f + %.2f i \n",x[0],x[1]);
}

#endif
