/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Single Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "sll.h"

struct sll_node
{
    void *value;
    iterator_t next;
};

struct sll
{
    iterator_t head;
    iterator_t tail;
};

static int CountSize(void *value, void *counter);

sll_t *SListCreate(void)
{
	sll_t *list = malloc(sizeof(sll_t));
	iterator_t dummy = malloc(sizeof(struct sll_node));
	
	if (NULL == list || NULL == dummy)
	{
		return NULL;
	}
	
	dummy->value = list;
	dummy->next = NULL;
	
	list->head = dummy;
	list->tail = dummy;
	
	return list;
}

void *SListGetValue(iterator_t position)
{
	assert(position);
	
    return (position->value);
}

iterator_t SListInsert(iterator_t position, void *value) 
{
	iterator_t new_node = malloc(sizeof(struct sll_node));
	sll_t *list = NULL;
	if (NULL == new_node)
	{
		return NULL;
	}
	
	assert(position);
	assert(value);
	
	if (position->next == NULL)
	{
		list = position->value;
		list->tail = new_node;
	}
	
	new_node->next = position->next;
	new_node->value = position->value;
	position->value = value;
	position->next = new_node;
		
	return position;
}

iterator_t SListRemove(iterator_t position_to_remove)
{
	iterator_t temp_iterator_to_free = position_to_remove->next;
	sll_t *list = NULL;
	assert(position_to_remove);
	
	if (NULL == position_to_remove->next) /*don't remove dummy*/
	{
		return NULL;
	}
	
	else if (NULL == position_to_remove->next->next)
	{
		list = position_to_remove->next->value;
		list->tail = position_to_remove;
	}
	
	position_to_remove->value = position_to_remove->next->value;
	position_to_remove->next = position_to_remove->next->next;
	
	free(temp_iterator_to_free);

	return (position_to_remove);
}
 
iterator_t SListIteratorNext(iterator_t position)
{
	assert(position);
	
	return (position->next);
}

iterator_t SListIteratorEnd(const sll_t *list)
{
	assert(list);
	
	return (list->tail);
}


iterator_t SListIteratorFirst(const sll_t *list)
{
	assert(list);
	
	return (list->head);
}
        
void SListSetValue(iterator_t position, void *value)
{
	assert(position);
	
	position->value = value;
}

int SListForEach(iterator_t from, iterator_t to, action_t action_function_ptr, void *param)
{
	int status = 0;
	
	assert(from);
	assert(to);
	assert(action_function_ptr);
	assert(param);
	
    for (; from != to; from = SListIteratorNext(from))
    {
      status = action_function_ptr(param, from->value);
    }
       
	return status;
}

int IsItrEqual(iterator_t iterator1, iterator_t iterator2)
{
	assert(iterator1);
	assert(iterator2);
	
	return (iterator1 == iterator2);
}

size_t SListSize(const sll_t *list)
{
	iterator_t beginning = SListIteratorFirst(list);
	iterator_t ending = SListIteratorEnd(list);
	size_t counter = 0;
	action_t counter_ptr_func = &CountSize;
	
	assert(list);
	
	SListForEach(beginning, ending, counter_ptr_func, &counter);
       
	return counter;
}

void SListDestroy(sll_t *list)
{
	iterator_t node = SListIteratorFirst(list);
	iterator_t temp_node_to_free = node;
	
	assert(list);
    
	while (NULL != node) 
	{
		temp_node_to_free = node;
		node = SListIteratorNext(node);
		free(temp_node_to_free);
	}
    
	free(list);
}

int SListIsEmpty(const sll_t *list)
{
	assert(list);
	
	return (0 == SListSize(list));
}

iterator_t SListFind(iterator_t from, iterator_t to, is_match_t is_match_function_ptr, void *param)
{
	iterator_t find_value = from;
	
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
		
		find_value = SListIteratorNext(find_value);
	}

	return NULL;
}

static int CountSize(void *counter, void *value)
{
	(void)value;
	*(int *)counter = *(int *)counter + 1;
	
	return 0;
}

void SListAppendSList(sll_t *dest, sll_t *src)
{
	iterator_t dest_tail = SListIteratorEnd(dest);
	iterator_t dummy = malloc(sizeof(struct sll_node));
	
	dummy->value = NULL;
	dummy->next = NULL;	
	
	dest->tail->next = src->head;
	SListRemove(dest_tail);

	dest->tail = src->tail;
	
	src->head = dummy; 
	src->tail = dummy; 
}
