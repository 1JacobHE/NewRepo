#ifndef JANUS_CONVOLVE_C_INCLUDED_
#define JANUS_CONVOLVE_C_INCLUDED_

void
janus_convolve(const janus_trellis_t trellis, const janus_uint8_t* inp, unsigned inp_len, janus_uint8_t* out)
{
  unsigned state = 0;
  unsigned idx = 0;
  unsigned n = 0;

  for (n = 0; n < inp_len; ++n)
  {
    idx = state + inp[n] * trellis->state_count;
    out[n << 1] = (trellis->outputs[idx] >> 1) & 1;
    out[(n << 1) + 1] = (trellis->outputs[idx] & 1);
    state = trellis->next_states[idx];
  }
}

#endif
