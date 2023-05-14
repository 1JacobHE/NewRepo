/*
 * MODEM_tx.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef MODEM_TX_H_INCLUDED_
#define MODEM_TX_H_INCLUDED_

#include <param.h>
#include <MIMO.h>
#include <frame.h>
#include <MIMO.h>
#include <block.h>
#include <ofdm_block.h>
#include <channel_coding.h>
#include <constellation.h>
#include <pulse_shaping.h>
#include <stream.h>

void
MODEM_tx_execute(param_p param, MIMO_p MIMO, frame_p frame, block_p block, ofdm_block_p ofdm_block, channel_coding_p channel_coding,
	constellation_p constellation, pulse_shaping_p pulse_shaping, stream_p stream, unsigned short* output, int* len_output);

#endif
