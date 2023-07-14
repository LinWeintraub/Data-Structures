/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          19/10/22                                        ~
 * Description   Doubly Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "dll.h"

static int CountSize(void *counter, void *value);

struct dll_node
{
    void *value;
    dll_iterator_t next;
    dll_iterator_t prev;
};

struct dll
{
    dll_iterator_t head;
    dll_iterator_t tail;
};

dll_t *DListCreate(void)
{
	dll_t *list = malloc(sizeof(dll_t));
	dll_iterator_t dummy_head = malloc(sizeof(struct dll_node));
	dll_iterator_t dummy_tail = malloc(sizeof(struct dll_node));
	
	if (NULL == list || NULL == dummy_head || NULL == dummy_tail)
	{
		free(list);
		free(dummy_head);
		free(dummy_tail);
		
		return NULL;
	}
	
	list->head = dummy_head;
	list->tail = dummy_tail;
		
	dummy_head->value = list;
	dummy_head->next = list->tail;
	dummy_head->prev = NULL;
	
	dummy_tail->value = list;
	dummy_tail->next = NULL;
	dummy_tail->prev = list->head;
			
	return list;
}

void DListDestroy(dll_t *list)
{
	dll_iterator_t node = DListIteratorPrev(DListIteratorFirst(list));
	dll_iterator_t temp_node_to_free = node;
	
	assert(list);
    
	while (NULL != node) 
	{
		temp_node_to_free = node;
		node = DListIteratorNext(node);
		free(temp_node_to_free);
		temp_node_to_free = NULL;
	}
    
	free(list);
	list = NULL;
}

dll_iterator_t DListIteratorNext(dll_iterator_t position)
{
	assert(position);
	
	return (position->next);
}

dll_iterator_t DListIteratorPrev(dll_iterator_t position)
{
	assert(position);
	
	return (position->prev);
}

dll_iterator_t DListIteratorFirst(const dll_t *list)
{
	assert(list);
	
	return (list->head->next);
}

dll_iterator_t DListIteratorEnd(const dll_t *list)
{
	assert(list);
	
	return (list->tail);
}

dll_iterator_t DListInsertBefore(dll_iterator_t position, void *value)
{
	dll_iterator_t new_node = malloc(sizeof(struct dll_node));

	if (NULL == new_node)
	{
		free(new_node);
		return NULL;
	}
	
	assert(position);
	assert(value);
	
	new_node->value = value;
	new_node->next = position;
	new_node->prev = position->prev;
	
	position->prev->next = new_node;
	position->prev = new_node;
		
	return new_node;
}

dll_iterator_t DListPushFront(dll_t *list, void *value)
{
	dll_iterator_t push_front = DListInsertBefore(DListIteratorFirst(list), value);

	assert(list);
	assert(value);
		
	return push_front;
}

dll_iterator_t DListPushBack(dll_t *list, void *value)
{
	dll_iterator_t push_back = DListInsertBefore(DListIteratorEnd(list), value);

	assert(list);
	assert(value);
		
	return push_back;
}

void *DListPopFront(dll_t *list)
{
	void *temp_front = DListGetValue(DListIteratorFirst(list));
	DListRemove(DListIteratorFirst(list));

	assert(list);
		
	return temp_front;
}

void *DListPopBack(dll_t *list)
{
	void *temp_Back = DListGetValue(DListIteratorPrev(DListIteratorEnd(list)));
	DListRemove(DListIteratorPrev(DListIteratorEnd(list)));

	assert(list);
		
	return temp_Back;
}

dll_iterator_t DListRemove(dll_iterator_t position_to_remove)
{
	dll_iterator_t temp_iterator_to_free = position_to_remove->next;
	
	assert(position_to_remove);
	
	if (NULL == position_to_remove->next) /*don't remove dummy*/
	{
		return NULL;
	}
	
	position_to_remove->next->prev = position_to_remove->prev;
	position_to_remove->prev->next = position_to_remove->next;
	
	free(position_to_remove); position_to_remove = NULL;

	return (temp_iterator_to_free);
}

void *DListGetValue(dll_iterator_t position)
{
	assert(position);
	
    return (position->value);
}

void DListSetValue(dll_iterator_t position, void *value)
{
	assert(position);
	
	position->value = value;
}

int DListIsIterEqual(dll_iterator_t iterator_1, dll_iterator_t iterator_2)
{
	assert(iterator_1);
	assert(iterator_2);
	
	return (iterator_1 == iterator_2);
}

size_t DListSize(const dll_t *list)
{
	dll_iterator_t beginning = DListIteratorFirst(list);
	dll_iterator_t ending = DListIteratorEnd(list);
	size_t counter = 0;
	action_t counter_ptr_func = &CountSize;
	
	assert(list);
	
	DListForEach(beginning, ending, counter_ptr_func, &counter);
       
	return counter;
}

static int CountSize(void *counter, void *value)
{
	(void)value;
	*(int *)counter = *(int *)counter + 1;
	
	return 0;
}

int DListIsEmpty(const dll_t *list)
{
	assert(list);
	
	return (0 == DListSize(list));
}

int DListForEach(dll_iterator_t from, dll_iterator_t to, action_t action_function_ptr, void *param)
{
	int status = 0;
	
	assert(from);
	assert(to);
	assert(action_function_ptr);
	assert(param);
	
    for (; from != to; from = DListIteratorNext(from))
    {
      status = action_function_ptr(param, from->value);
    }
       
	return status;
}

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, void *param)
{
	dll_iterator_t find_value = from;
	
	assert(from);
	assert(to);
	assert(is_match_function_ptr);
	assert(param);
	
	while (find_value != to) 
	{
		if (1 == is_match_function_ptr(param, find_value->value))
		{
		    return find_value;
		}
		
		find_value = DListIteratorNext(find_value);
	}

	return to;
}

void DListSplice(dll_iterator_t from, dll_iterator_t to, dll_iterator_t position)
{
	dll_iterator_t temp_position_prev = position->prev;
	dll_iterator_t temp_prev_to = to->prev;
	
	assert(from);
	assert(to);
	assert(position);
	
	from->prev->next = to;
	to->prev = from->prev;
	
	from->prev = position->prev;
	
	temp_prev_to->next = position;
	
	position->prev = temp_prev_to;
	temp_position_prev->next = from;
}

size_t DListMultiFind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, dll_t *found_items, void *param)
{
	size_t counter = 0;
	dll_iterator_t match_node = from;
	
	assert(from);
	assert(to);
	assert(found_items);
	assert(is_match_function_ptr);
	assert(param);
	
	while (match_node != to)
	{
		match_node = DListFind(match_node, to, is_match_function_ptr, param);
		
		if (NULL == match_node)
		{
			break;
		}
		
		if (NULL == DListInsertBefore(DListIteratorFirst(found_items), DListGetValue(match_node)))
		{
			break;
		}
			
		++counter;
		match_node = DListIteratorNext(match_node);
	}
	
	return counter;
}
