#ifndef MODEM_TRELLIS_H_INCLUDED_
#define MODEM_TRELLIS_H_INCLUDED_

#include <types.h>

struct MODEM_trellis
{
  //! Number of input symbols.
  unsigned inp_sym_count;
  //! Number of output symbols.
  unsigned out_sym_count;
  //! Number of states.
  unsigned state_count;
  //! Outputs for all combinations of current state and current input.
  const MODEM_uint8_t* outputs;
  //! Next states for all combinations of current state and current input.
  const MODEM_uint8_t* next_states;
};

typedef struct MODEM_trellis* MODEM_trellis_t;

const MODEM_trellis_t
MODEM_trellis_default();

#endif
