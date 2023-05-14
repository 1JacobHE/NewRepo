/*
 * constellation.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _CONSTELLATION_C_
#define _CONSTELLATION_C_

#include <constellation.h>

constellation_p constellation_new(param_p pa)
{
	constellation_p cm = MODEM_UTILS_MEMORY_NEW_ZERO(struct constellation, 1);
	char s1[]="QPSK";
	char s2[]="16QAM";
	char s3[]="64QAM";
    cm->constellation_scheme=pa->constellation_scheme;
    if(strcmp(cm->mapping_scheme,s1)==0)
    {
    	cm->bits_per_symbol=2;
    }
    else if(strcmp(cm->mapping_scheme,s2)==0)
    {
    	cm->bits_per_symbol=4;
    }
    else if(strcmp(cm->mapping_scheme,s3)==0)
    {
    	cm->bits_per_symbol=6;
    }
    return cm;
}

void constellation_constellate(int m, int* input, MODEM_complex* output, int len)
{
    if (m == 2) {
        int i;
        int n = len;

        int map[4] = { 0, 1, 3, 2 };
        int temp = n % 2;
        if (temp != 0) {
            n = n + 1;
            input[n] = 0;
        }

        int sym_length = n / 2;
        int sym_value[sym_length];

        for (i = 0; i < sym_length; i++) {
            sym_value[i] = input[i * 2] * 2 + input[i * 2 + 1];
        }

        for (i = 0; i < sym_length; i++) {
            sym_value[i] = map[sym_value[i]];
            output[i][0] = cos(PI / 2 * sym_value[i]);
            output[i][1] = sin(PI / 2 * sym_value[i]);
        }
    }
 }
        if (m == 4) {
            for (i = 0; i < length; i += 4) {
                int I1 = input[i];
                int Q1 = input[i + 1];
                int I2 = input[i + 2];
                int Q2 = input[i + 3];

                double I_out = (2 * I1 - 1) / sqrt(10) + (2 * I2 - 1) / sqrt(10);
                double Q_out = (2 * Q1 - 1) / sqrt(10) + (2 * Q2 - 1) / sqrt(10);

                output[index++] = I_out;
                output[index++] = Q_out;
            }
        }
        if (m == 6) {
            for (i = 0; i < length; i += 6) {
                int I1 = input[i];
                int Q1 = input[i + 1];
                int I2 = input[i + 2];
                int Q2 = input[i + 3];
                int I3 = input[i + 4];
                int Q3 = input[i + 5];

                double I_out = (2 * I1 - 1) / sqrt(42) + (2 * I2 - 1) / sqrt(42) + (2 * I3 - 1) / sqrt(42);
                double Q_out = (2 * Q1 - 1) / sqrt(42) + (2 * Q2 - 1) / sqrt(42) + (2 * Q3 - 1) / sqrt(42);

                output[index++] = I_out;
                output[index++] = Q_out;
            }
        }
}





void constellation_free(constellation_p cm)
{
    MODEM_UTILS_MEMORY_FREE(cm);
}


#endif





