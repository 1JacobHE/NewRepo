/*
 * stream.h
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _STREAM_H_
#define _STREAM_H_

#include <param.h>

#include <memory.h>
#include <string.h>
#include <stdlib.h>

struct stream{
	long long sampling_frequency;
};

typedef struct stream* stream_p;

stream_p stream_new(param_p pa);

void stream_free(stream_p stream);


#endif