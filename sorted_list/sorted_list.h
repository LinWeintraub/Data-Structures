#ifndef __SORTED_LIST__
#define __SORTED_LIST__

#include "dll.h"

typedef struct sdll sdll_t;

typedef dll_iterator_t sdll_iterator_t;

typedef int (*cmp_func_t)(void *param, void *value);

sdll_t *SDListCreate(cmp_func_t cmp_func_p);

void SDListDestroy(sdll_t *slist);

sdll_iterator_t SDListIteratorNext(sdll_iterator_t position);

sdll_iterator_t SDListIteratorPrev(sdll_iterator_t position);

sdll_iterator_t SDListIteratorFirst(const sdll_t *slist);

sdll_iterator_t SDListIteratorEnd(const sdll_t *slist);

sdll_iterator_t SDListInsert(sdll_t *slist, void *value); 

void *SDListPopFront(sdll_t *slist);

void *SDListPopBack(sdll_t *slist);

sdll_iterator_t SDListRemove(sdll_iterator_t position_to_remove);

void *SDListGetValue(sdll_iterator_t position);

int SDListIsIterEqual(sdll_iterator_t iterator_1, sdll_iterator_t iterator_2);

size_t SDListSize(const sdll_t *slist);

int SDListIsEmpty(const sdll_t *slist);

int SDListForEach(sdll_iterator_t from, sdll_iterator_t to, action_t action_function_ptr, void *param);

sdll_iterator_t SDListFindIf(sdll_iterator_t from, sdll_iterator_t to, is_match_t is_match_function_ptr, void *param);

void SDListSMerge(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist);

sdll_iterator_t SDListFind(sdll_iterator_t from, sdll_iterator_t to, sdll_t *slist, void *param);

#endif /* __SORTED_LIST__ */
