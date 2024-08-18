#ifndef _CFIFO_H
#define _CFIFO_H

#include "ctype.h"

typedef struct
{
    u16 in;
    u16 out;
    u16 mask;
} cfifo;

#define CFIFO_ERROR_INDEX 0xFFFF

static inline void _cfifo_init(cfifo *fifo, u16 size)
{
    fifo->mask = (u16)(size - 1);
    fifo->in = 0;
    fifo->out = 0;
}

#define CFIFO_INIT(fifo, size) \
    _cfifo_init(fifo, CLIBS_STATIC_CHECK_2POW(size))

static inline u16 cfifo_usedspace(cfifo *fifo)
{
    return (fifo->in + fifo->mask + 1 - fifo->out) & fifo->mask;
}

static inline u32 cfifo_freespace(cfifo *fifo)
{
    return fifo->mask + 1 - cfifo_usedspace(fifo);
}

static inline bool cfifo_isempty(cfifo *fifo)
{
    return fifo->in == fifo->out;
}

static inline bool cfifo_isfull(cfifo *fifo)
{
    return 0 == cfifo_usedspace(fifo);
}

static inline void cfifo_reset(cfifo *fifo)
{
    fifo->in = 0;
    fifo->out = 0;
}

static inline u16 cfifo_get(cfifo *fifo)
{
    if (cfifo_isempty(fifo))
        return CFIFO_ERROR_INDEX;
    return fifo->out;
}

static inline void cfifo_afterget(cfifo *fifo)
{
    fifo->out = (fifo->out + 1) & fifo->mask;
}

static inline u16 cfifo_put(cfifo *fifo)
{
    if (cfifo_isfull(fifo))
        return CFIFO_ERROR_INDEX;
    return fifo->in;
} 

static inline void cfifo_afterput(cfifo *fifo)
{
    fifo->in = (fifo->in + 1) & fifo->mask;
}


#endif