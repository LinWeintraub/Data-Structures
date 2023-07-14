#ifndef __PRIORITY_QUEUE__
#define __PRIORITY_QUEUE__

#include "sorted_list.h"

#include <stddef.h> /* size_t */

typedef sdll_t priority_queue_t;

priority_queue_t *PQCreate(cmp_func_t priority_func);
/*
Description: The function creates a new priority queue.
Return: The function returns a pointer to the new priority queue.
Errors: Returns NULL if malloc fails.
*/

void PQDestroy(priority_queue_t *priority_queue);
/*
Description: The function frees the queue.
*/

int PQEnqueue(priority_queue_t *priority_queue, void *value);
/*
Description: The functions inserts a new element to the queue.
Params: The function gets a pointer to the queue and the data to be inserted.
Return: Returns 0 on SUCCESS and 1 in FAILURE.
Errors: Returns NULL if malloc fails.
*/

void *PQDequeue(priority_queue_t *priority_queue);
/*
Description: The function removes an element from the front of the priority queue.
*/

void *PQPeek(const priority_queue_t *priority_queue);
/*
Description: The function gets a pointer to the priority queue and returns the data at the 
head of the priority queue.
Return: The function return the data at the front of the priority queue.
*/

void PQClear(priority_queue_t *priority_queue);
/*
Description: The function clear all the elements.
*/

void *PQErase(priority_queue_t *priority_queue, is_match_t is_match_function_p, void *param);
/*
Description: The function remove the first element that match
the condition that returned by the function is_match.
Return: Returns 0 on SUCCESS and 1 in FAILURE.
*/

size_t PQSize(const priority_queue_t *priority_queue);
/*
Description: The function returns the number of items stored in the priority queue.
Return: The function returns the number of items in the priority queue.
*/

int PQIsEmpty(const priority_queue_t *priority_queue);
/*
Description: The function checks if pq is empty. 
Return: Returns 1 for TRUE, 0 for FALSE.
*/

#endif /* __PRIORITY_QUEUE__ */
