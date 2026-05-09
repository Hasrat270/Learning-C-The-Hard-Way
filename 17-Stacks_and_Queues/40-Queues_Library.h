#ifndef _lcthw_Queue_h
#define _lcthw_Queue_h

#include "30-DoubleLinkedLists_Library.h"

typedef List Queue;

#define Queue_create() List_create()
#define Queue_destroy(Q) List_destroy((Q))
#define Queue_send(Q, V) List_push((Q), (V))
#define Queue_recv(Q) List_shift((Q))
#define Queue_peek(Q) List_first((Q))
#define Queue_count(Q) List_count((Q))

#define QUEUE_FOREACH(Q, V) LIST_FOREACH((Q), first, next, (V))

#endif
