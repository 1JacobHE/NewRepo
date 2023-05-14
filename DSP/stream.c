/*
 * stream.c
 *
 *  Created on: 2023.5.12
 *      Author: admin
 */

#ifndef _STREAM_C_
#define _STREAM_C_

#include <stream.h>

stream_p stream_new(param_p pa)
{
	stream_p stream = MODEM_UTILS_MEMORY_NEW_ZERO(struct stream, 1);

    stream->sampling_frequency=pa->sampling_frequency;

    return stream;
}

void stream_free(stream_p stream)
{
    MODEM_UTILS_MEMORY_FREE(stream);
}

#endif