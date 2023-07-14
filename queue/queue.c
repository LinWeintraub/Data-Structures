/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Queue                                           *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdlib.h>
#include <assert.h>

#include "sll.h"
#include "queue.h"

queue_t *QueueCreate(void)
{
	queue_t *queue_list = SListCreate();	
	
	if (NULL == queue_list)
	{
		return NULL;
	}

	return queue_list;
}

void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	
	return (SListGetValue(SListIteratorFirst(queue)));
}

int Enqueue(queue_t *queue, const void *value)
{	
	int status = 0;
	iterator_t new_node = SListInsert(SListIteratorEnd(queue), (void *)value);
	
	assert(queue);
	
	if (NULL == new_node)
	{
		status = 1;
	}
	return status;
}

void *Dequeue(queue_t *queue)
{
	void *temp = SListGetValue(SListIteratorFirst(queue));
	
	assert(queue);
		
	SListRemove(SListIteratorFirst(queue));
	
	return temp;
}

size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	
	return (SListSize(queue));
}

void QueueDestroy(queue_t *queue)
{
	assert(queue);
	
	SListDestroy(queue);
}

int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	
	return (SListIsEmpty(queue));
}

void QueueAppend(queue_t *dest, queue_t *src)
{
	assert(dest);	
	assert(src);
	SListAppendSList(dest, src);
}

