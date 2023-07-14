/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          24/10/22                                        ~
 * Description   Priority Queue                                  *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <assert.h> /* assert*/

#include "priority_queue.h"

priority_queue_t *PQCreate(cmp_func_t priority_func)
{
	priority_queue_t *priority_queue = NULL;
	
	assert(priority_func);
	
	priority_queue = SDListCreate(priority_func);
	
	return priority_queue;
}

void PQDestroy(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	
	SDListDestroy(priority_queue);
	priority_queue = NULL;
}

int PQEnqueue(priority_queue_t *priority_queue, void *value)
{
	assert(priority_queue);
	assert(value);
	
	return (NULL == SDListInsert(priority_queue, value));
}

void *PQDequeue(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	assert(0 != PQSize(priority_queue)); 
	
	return (SDListPopFront(priority_queue));
}

void *PQPeek(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	assert(0 != PQSize(priority_queue)); 
	
	return (SDListGetValue(SDListIteratorFirst(priority_queue)));
}

void PQClear(priority_queue_t *priority_queue)
{
	assert(priority_queue);
	
	while (SDListIteratorFirst(priority_queue) != SDListIteratorEnd(priority_queue)) 
	{
		PQDequeue(priority_queue);
	}
}

void *PQErase(priority_queue_t *priority_queue, is_match_t is_match_function_p, void *param)
{
	sdll_iterator_t find_value = NULL;
	void *temp = NULL;
	
	assert(priority_queue);
	assert(is_match_function_p);
	assert(param);
	
	find_value = SDListFindIf(SDListIteratorFirst(priority_queue), SDListIteratorEnd(priority_queue), is_match_function_p, param);
	temp = SDListGetValue(find_value);
	
	if (NULL != SDListIteratorNext(find_value))
	{
		SDListRemove(find_value);
	}
	
	return temp;
}

size_t PQSize(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	
	return (SDListSize(priority_queue));
}

int PQIsEmpty(const priority_queue_t *priority_queue)
{
	assert(priority_queue);
	
	return (SDListIsEmpty(priority_queue));
}

