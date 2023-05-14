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
	char s1[] = "QPSK";
	char s2[] = "16QAM";
	char s3[] = "64QAM";
	cm->constellation_scheme = pa->constellation_scheme;
	if (strcmp(cm->mapping_scheme, s1) == 0)
	{
		cm->bits_per_symbol = 2;
	}
	else if (strcmp(cm->mapping_scheme, s2) == 0)
	{
		cm->bits_per_symbol = 4;
	}
	else if (strcmp(cm->mapping_scheme, s3) == 0)
	{
		cm->bits_per_symbol = 6;
	}
	return cm;
}

void constellation_constellate(int m, int* input, MODEM_complex* output, int len)
{
	int i;
	int n = len;
	int sym_length = n / m;
	unsigned int Es = 1;
	unsigned int delta = sqrt(3 * Es / (2 * (2 ^ m - 1)));

	if (m == 2) {
		int map[4] = { 0, 1, 3, 2 };
		int temp = n % 2;
		if (temp != 0) {
			n = n + 1;
			input[n] = 0;
		}

		int sym_value[sym_length];

		for (i = 0; i < sym_length; i++) {
			sym_value[i] = input[i * m] * 2 + input[i * m + 1];
		}

		for (i = 0; i < sym_length; i++) {
			sym_value[i] = map[sym_value[i]];
			output[i][0] = cos(M_PI / 2 * sym_value[i]);
			output[i][1] = sin(M_PI / 2 * sym_value[i]);
		}
	}
	else if (m == 4)
	{
		double map[4] = { -3 * delta, -1 * delta, 3 * delta, 1 * delta };

		double sym_value_inphase[sym_length];
		double sym_value_quadrature[sym_length];
		for (i = 0; i < sym_length; i++) {
			sym_value_inphase[i] = map[input[i * m + 1] + input[i * m] * 2];
			sym_value_quadrature[i] = map[input[i * m + 3] + input[i * m + 2] * 2];
			output[i][0] = sym_value_inphase[i];
			output[i][1] = sym_value_quadrature[i];
		}
	}
	else if (m == 6) {
		double map[8] = { -7 * delta, -5 * delta, -1 * delta, -3 * delta, 7 * delta, 5 * delta, 1 * delta, 3 * delta };

		double sym_value_inphase[sym_length];
		double sym_value_quadrature[sym_length];
		for (i = 0; i < sym_length; i++) {
			sym_value_inphase[i] = map[input[i * m + 2] + input[i * m + 1] * 2 + input[i * m] * 4];
			sym_value_quadrature[i] = map[input[i * m + 5] + input[i * m + 4] * 2 + input[i * m + 3] * 4];
			output[i][0] = sym_value_inphase[i];
			output[i][1] = sym_value_quadrature[i];
		}
	}
}

void constellation_free(constellation_p cm)
{
	MODEM_UTILS_MEMORY_FREE(cm);
}


#endif





