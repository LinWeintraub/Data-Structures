#ifndef __SINGLY_LINKED_LIST__
#define __SINGLY_LINKED_LIST__

#include <stddef.h>

typedef struct sll sll_t;
typedef struct sll_node *iterator_t;
typedef int (*is_match_t)(void *param, void *value);
typedef int (*action_t)(void *param, void *value);

sll_t *SListCreate(void);

void *SListGetValue(iterator_t position);

iterator_t SListRemove(iterator_t position_to_remove);

iterator_t SListIteratorNext(iterator_t position);

iterator_t SListIteratorEnd(const sll_t *list);

iterator_t SListIteratorFirst(const sll_t *list);

iterator_t SListInsert(iterator_t position, void *value);
        
void SListSetValue(iterator_t position, void *value);

int SListForEach(iterator_t from, iterator_t to, action_t action_function_ptr, void *param);

int IsItrEqual(iterator_t iterator1, iterator_t iterator2);

size_t SListSize(const sll_t *list);

void SListDestroy(sll_t *list);

int SListIsEmpty(const sll_t *list);

iterator_t SListFind(iterator_t from, iterator_t to, is_match_t is_match_function_ptr, void *param);

void SListAppendSList(sll_t *dest, sll_t *src);

#endif /* __Singly_Linked_List__ */
