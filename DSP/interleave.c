#ifndef MODEM_INTERLEAVE_C_INCLUDED_
#define MODEM_INTERLEAVE_C_INCLUDED_

#include <stdlib.h>
#include <interleave.h>


static const unsigned c_prime_min = 5;

unsigned
MODEM_utils_primes_get_previous(unsigned nr)
{
    while (nr)
    {
        if (MODEM_utils_primes_is_prime(nr))
            return nr;

        --nr;
    }

    return 0;
}

unsigned
MODEM_interleave_q(unsigned length)
{
  // Find the lowest prime number which is not a factor of length.
  // @fixme: there's something more to this.
  unsigned k = c_prime_min;
  unsigned prime = 0;

  while (1)
  {
    prime = MODEM_utils_primes_get_previous(k);
    if (((length / prime) < prime) && ((length % prime) != 0))
      break;
    ++k;
  }

  return prime;
}

void
MODEM_interleave(const MODEM_uint8_t* inp, unsigned inp_len, MODEM_uint8_t* out)
{
  unsigned prime = MODEM_interleave_q(inp_len);
  unsigned i = 0;
  unsigned* perm = (unsigned*)malloc(sizeof(unsigned) * inp_len);

  // Build permutation table.
  perm[0] = 0;
  for (i = 1; i < inp_len; ++i)
    perm[i] = (perm[i - 1] + prime) % inp_len;

  // Perform permutation.
  for (i = 0; i < inp_len; ++i)
    out[i] = inp[perm[i]];

  free(perm);
}

#endif
