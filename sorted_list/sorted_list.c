/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          20/10/22                                        ~
 * Description   Sorted Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#ifndef NDEBUG
#include <stdio.h> /* printf */
#endif

#include "sorted_list.h"

static sdll_iterator_t SDListFindPosition(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist, void *param);

struct sdll 
{
    dll_t *list;
    cmp_func_t cmp_func_p;
};

sdll_t *SDListCreate(cmp_func_t cmp_func_p)
{
	sdll_t *sorted_list = malloc(sizeof(sdll_t));
	if (NULL == sorted_list)
	{
		free(sorted_list);
		return NULL;
	}
	
	sorted_list->list = DListCreate();
	if (NULL == sorted_list->list)
	{
		free(sorted_list);
		return NULL;
	}
	
	sorted_list-> cmp_func_p = cmp_func_p;
	
	return sorted_list;
}

void SDListDestroy(sdll_t *slist)
{
	assert(slist);
	
	DListDestroy(slist->list);
	free(slist);
	slist = NULL;
}

sdll_iterator_t SDListIteratorNext(sdll_iterator_t position)
{
	assert(position);
	
	return DListIteratorNext(position);
}

sdll_iterator_t SDListIteratorPrev(sdll_iterator_t position)
{
	assert(position);
	
	return DListIteratorPrev(position);
}

sdll_iterator_t SDListIteratorFirst(const sdll_t *slist)
{
	assert(slist);
	
	return DListIteratorFirst(slist->list);
}

sdll_iterator_t SDListIteratorEnd(const sdll_t *slist)
{
	assert(slist);
	
	return DListIteratorEnd(slist->list);
}

sdll_iterator_t SDListInsert(sdll_t *slist, void *value)
{
	dll_iterator_t position = DListIteratorFirst(slist->list);
	dll_iterator_t end = DListIteratorEnd(slist->list);
	int status = 0;
	
	assert(slist);
	assert(value);
	
	for (; !SDListIsIterEqual(position, end); position = DListIteratorNext(position))
    {
		status = slist->cmp_func_p(value, DListGetValue(position));

		if (status <= 0)
		{
			break;
		}
    }
    
	position = DListInsertBefore(position, value);
		
	return position;
}

void *SDListPopFront(sdll_t *slist)
{
	assert(slist);
	
	return (DListPopFront(slist->list));
}

void *SDListPopBack(sdll_t *slist)
{
	assert(slist);
	
	return (DListPopBack(slist->list));
}

sdll_iterator_t SDListRemove(sdll_iterator_t position_to_remove)
{
	assert(position_to_remove);
	
	return (DListRemove(position_to_remove));
}

void *SDListGetValue(sdll_iterator_t position)
{
	assert(position);
	
	return (DListGetValue(position));
}

int SDListIsIterEqual(sdll_iterator_t iterator_1, sdll_iterator_t iterator_2)
{
	assert(iterator_1);
	assert(iterator_2);
	
	return (DListIsIterEqual(iterator_1, iterator_2));
}

size_t SDListSize(const sdll_t *slist)
{
	assert(slist);
	
	return (DListSize(slist->list));
}

int SDListIsEmpty(const sdll_t *slist)
{
	assert(slist);
	
	return (DListIsEmpty(slist->list));
}

int SDListForEach(sdll_iterator_t from, sdll_iterator_t to, action_t action_function_ptr, void *param)
{
	#ifndef NDEBUG
	sdll_iterator_t runner_1 = from;
	sdll_iterator_t runner_2 = to;
	
	assert(from);
	assert(to);
	assert(action_function_ptr);
	assert(param);
	
	while (DListIteratorNext(runner_1) != NULL)
	{
		runner_1 = SDListIteratorNext(runner_1);
	}
	
	while (DListIteratorNext(runner_1) != NULL)
	{
		runner_2 = SDListIteratorNext(runner_2);
	}
	
	if (SDListGetValue(runner_1) == SDListGetValue(runner_2))
	{
		printf("'from' and 'to' are from the same list");
	}	
	#endif
	
	return (DListForEach(from, to, action_function_ptr, param));
}

sdll_iterator_t SDListFindIf(sdll_iterator_t from, sdll_iterator_t to, is_match_t is_match_function_ptr, void *param)
{
	assert(from);
	assert(to);
	assert(is_match_function_ptr);
	assert(param);
	
	return (DListFind(from, to, is_match_function_ptr, param));
}

void SDListSMerge(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist)
{
	sdll_iterator_t merge_pos_dest = NULL;
	sdll_iterator_t to_src = NULL;
	
	assert(from);
	assert(to);
	assert(slist);
	
	merge_pos_dest = SDListIteratorFirst(slist);
	
	while (!SDListIsIterEqual(from, to))
	{
		if (NULL == SDListIteratorNext(merge_pos_dest))
		{
			DListSplice(from, to, merge_pos_dest);
			break;
		}

		else if (0 >= slist->cmp_func_p(SDListGetValue(from), SDListGetValue(merge_pos_dest)))
		{
			to_src = SDListFindPosition(from, to, slist, SDListGetValue(merge_pos_dest));
			DListSplice(from, to_src, merge_pos_dest);
			from = to_src;	
		}

		merge_pos_dest = DListIteratorNext(merge_pos_dest);
	}
}


sdll_iterator_t SDListFind(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist, void *param)
{
	dll_iterator_t find_value = NULL;
	
	assert(from);
	assert(to);
	assert(slist);
	assert(param);
	
	find_value = from;
		
	while (!SDListIsIterEqual(find_value, to))
	{
		if (0 == slist->cmp_func_p(param, SDListGetValue(find_value)))
		{
		    return find_value;
		}
		
		find_value = DListIteratorNext(find_value);
	}

	return to;
}

static sdll_iterator_t SDListFindPosition(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist, void *param)
{
	dll_iterator_t find_value = NULL;
	
	assert(from);
	assert(to);
	assert(slist);
	assert(param);
	
	find_value = from;
	
	while (!SDListIsIterEqual(find_value, to))
	{
		if (0 >= slist->cmp_func_p(param, SDListGetValue(find_value)))
		{
		    return find_value;
		}
		
		find_value = DListIteratorNext(find_value);
	}

	return to;
}
