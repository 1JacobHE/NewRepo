/*
 * Goertzel.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _GOERTZEL_C_
#define _GOERTZEL_C_

#include <Goertzel.h>

#define BUFFER_SIZE 200
#define NN 199
#define KK 36
#define CC 0.83556

long detectwut(unsigned int* buf)
{
    unsigned int* p=buf;
    long P;
    long Q0;
    long Q1=0;
    long Q2=0;
    unsigned int countN=0;
    while(countN<NN)
    {
        Q0=CC*Q1-Q2+buf[countN];
        countN++;
    }
    P=Q1*Q1+Q2*Q2-CC*Q1*Q2;
    return P;
}

#endif