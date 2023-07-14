#ifndef __DOUBLY_LINKED_LIST__
#define __DOUBLY_LINKED_LIST__

#include <stddef.h>

typedef struct dll dll_t;
typedef struct dll_node *dll_iterator_t;
typedef int (*is_match_t)(void *param, void *value);
typedef int (*action_t)(void *param, void *value);

dll_t *DListCreate(void);

void DListDestroy(dll_t *list);

dll_iterator_t DListIteratorNext(dll_iterator_t position);

dll_iterator_t DListIteratorPrev(dll_iterator_t position);

dll_iterator_t DListIteratorFirst(const dll_t *list);

dll_iterator_t DListIteratorEnd(const dll_t *list);

dll_iterator_t DListInsertBefore(dll_iterator_t position, void *value);

dll_iterator_t DListPushFront(dll_t *list, void *value);

dll_iterator_t DListPushBack(dll_t *list, void *value);

void *DListPopFront(dll_t *list);

void *DListPopBack(dll_t *list);

dll_iterator_t DListRemove(dll_iterator_t position_to_remove);

void *DListGetValue(dll_iterator_t position);

void DListSetValue(dll_iterator_t position, void *value);

int DListIsIterEqual(dll_iterator_t iterator_1, dll_iterator_t iterator_2);

size_t DListSize(const dll_t *list);

int DListIsEmpty(const dll_t *list);

int DListForEach(dll_iterator_t from, dll_iterator_t to, action_t action_function_ptr, void *param);

dll_iterator_t DListFind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, void *param);

void DListSplice(dll_iterator_t from, dll_iterator_t to, dll_iterator_t position);

size_t DListMultiFind(dll_iterator_t from, dll_iterator_t to, is_match_t is_match_function_ptr, dll_t *found_items, void *param);

#endif /* __DOUBLY_LINKED_LIST__ */

