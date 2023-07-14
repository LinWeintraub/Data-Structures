#ifndef __QUEUE__
#define __QUEUE__

#include <stddef.h>

#include "sll.h"

typedef sll_t queue_t;

queue_t *QueueCreate(void);

void *QueuePeek(const queue_t *queue);

int Enqueue(queue_t *queue, const void *value);

void *Dequeue(queue_t *queue);

size_t QueueSize(const queue_t *queue);

void QueueDestroy(queue_t *queue);

int QueueIsEmpty(const queue_t *queue);

void QueueAppend(queue_t *dest, queue_t *src);

#endif /* __QUEUE__ */
