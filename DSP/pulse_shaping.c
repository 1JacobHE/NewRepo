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

#define FILTER_LENGTH 101  // 滤波器长度
#define SYMBOL_RATE 100    // 符号速率
#define ROLLOFF_FACTOR 0.5 // 滚降因子

// Raised Cosine滤波器
void raised_cosine_filter(float* filter) {
    int i;
    float t;
    float T = 1.0 / SYMBOL_RATE;
    float alpha = ROLLOFF_FACTOR;

    for (i = 0; i < FILTER_LENGTH; i++) {
        t = (i - FILTER_LENGTH / 2) * T;
        if (t == 0) {
            filter[i] = 1.0;
        }
        else if (fabs(t) == T / (2 * alpha)) {
            filter[i] = alpha / (2 * sqrt(2.0));
        }
        else {
            filter[i] = (sin(2 * M_PI * t / T * (1 - alpha)) + 4 * alpha * t / T * cos(2 * M_PI * t / T * (1 + alpha))) / (M_PI * t / T * (1 - (4 * alpha * t / T) * (4 * alpha * t / T)));
        }
    }
}

// 脉冲成型函数
void pulse_shaping(float* symbol, float* shaped_symbol) {
    float filter[FILTER_LENGTH];
    raised_cosine_filter(filter);

    int i, j;
    for (i = 0; i < FILTER_LENGTH; i++) {
        float real_part = symbol[0] * filter[i];
        float imag_part = symbol[1] * filter[i];
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