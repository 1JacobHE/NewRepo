/*
 * pulse_shaping.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _PULSE_SHAPING_C_
#define _PULSE_SHAPING_C_

#include <pulse_shaping.h>

pulse_shaping_p pulse_shaping_new(param_p pa)
{
	pulse_shaping_p ps = MODEM_UTILS_MEMORY_NEW_ZERO(struct pulse_shaping, 1);

    ps->pulse_shaping=pa->pulse_shaping_scheme;

    return ps;
}

void root_raised_cosine(MODEM_real_p* csf, MODEM_uint16_p Nb, MODEM_real_p beta) {
    MODEM_uint16_p Nfilt = 2;
    MODEM_uint16_p len = 2 * Nfilt * Nb + 1;
    MODEM_real_p T = 1.0;
    MODEM_real_p* x = (MODEM_real_p*)malloc(len * sizeof(MODEM_real_p));
    MODEM_real_p* y = (MODEM_real_p*)malloc(len * sizeof(MODEM_real_p));
    MODEM_real_p* numerator = (MODEM_real_p*)malloc(len * sizeof(MODEM_real_p));
    MODEM_real_p* denominator = (MODEM_real_p*)malloc(len * sizeof(MODEM_real_p));

    for (int i = 0; i < len; ++i) {
        x[i] = -Nfilt + i / (MODEM_real_p)Nb;
        numerator[i] = sin(M_PI * (1 - beta) * x[i] / T) + (4 * beta * x[i] / T) * cos(M_PI * (1 + beta) * x[i] / T);
        denominator[i] = sqrt(T) * (M_PI * x[i] / T) * (1 - (4 * beta * x[i] / T) * (4 * beta * x[i] / T));

        if (x[i] == 0) {
            y[i] = (1 - beta + 4 * beta / M_PI) / sqrt(T);
        }
        else if ((1 - (4 * beta * x[i] / T) * (4 * beta * x[i] / T)) == 0) {
            y[i] = beta * ((1 + 2 / M_PI) * sin(M_PI / (4 * beta)) + (1 - 2 / M_PI) * cos(M_PI / (4 * beta))) / sqrt(2 * T);
        }
        else {
            y[i] = numerator[i] / denominator[i];
        }
    }

    MODEM_real_p norm = 0;
    MODEM_uint16_p i;
    for (i = 0; i < len; ++i) {
        norm += y[i] * y[i];
    }
    norm = sqrt(norm);

    for (i = 0; i < len; ++i) {
        csf[i] = y[i] / norm;
    }

    free(x);
    free(y);
    free(numerator);
    free(denominator);
}

// Âö³å³ÉÐÍº¯Êý
void pulse_shaping_shape(MODEM_complex_p* symbol, MODEM_complex_p* shaped_symbol, MODEM_uint16_p filter_length) {
    MODEM_real_p* filter = (MODEM_real_p*)malloc(filter_length * sizeof(MODEM_real_p));
    root_raised_cosine(filter, filter_length, 0.2);

    MODEM_uint16_p i, j;
    for (i = 0; i < filter_length; i++) {
        MODEM_real_p real_part = symbol[0] * filter[i];
        MODEM_real_p imag_part = symbol[1] * filter[i];
        for (j = i; j > 0; j--) {
            shaped_symbol[2 * j] += real_part;
            shaped_symbol[2 * j + 1] += imag_part;
        }
    }
}

void pulse_shaping_free(pulse_shaping_p ps)
{
    MODEM_UTILS_MEMORY_FREE(ps);
}

#endif