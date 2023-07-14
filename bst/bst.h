#ifndef __BINARY_SEARCH_TREE__
#define __BINARY_SEARCH_TREE__

#include <stddef.h>

typedef struct bst_iter bst_iter_t;
typedef struct bst_node bst_node_t;
typedef struct bst bst_t;

typedef int (*cmp_func_t)(void *param, void *value);
typedef int (*action_t)(void *param, void *value);

struct bst_iter
{
	bst_node_t *node;
};

/*
    Params: cmp_func_p is the function with which comparison is done between different
	 values of the bst.
    Return: A bst_t type pointer if succeeds, NULL if fails.
    Complexity: O(1)
*/
bst_t *BSTCreate(cmp_func_t cmp_func_p);

/*
    Params: bst_t type pointer bst that represents the tree to destroy
    Return: No return value.
    Complexity: O(n) where n is number of vertices
*/
void BSTDestroy(bst_t *bst);

/*
    Params: bst_t type pointer bst that represents the tree to get size of
    Return: size of tree in size_t type.
    Complexity: O(n) where n is number of vertices
*/
size_t BSTSize(const bst_t *bst);

/*
    Params: bst_t type pointer bst that represents the tree to check if empty
    Return: 1 if empty, else 0.
    Complexity: O(1)
*/
int BSTIsEmpty(const bst_t *bst);

/*
    Params: bst_t type pointer bst that represents the tree to insert to, value
	 is the ptr to the value which to be stored in the tree.
    Return: bst_iter that was inserted on success, BSTEnd on failure.
    Complexity: O(log(n)) where n is number of vertices
*/
bst_iter_t BSTInsert(bst_t *bst, void *value);

/*
    Params: bst_iter_t type that represents the position to remove
    Return: None.
    Complexity: O(log(n)) where n is number of vertices
*/
void BSTRemove(bst_iter_t iter_to_remove);

/*
    Params: bst_t type pointer bst that represents the tree to find smallest value
    Return: Returns the lowest value bst_iter_t iterator if list is not empty
	 else, BSTEnd.
    Complexity: O(log(n)) where n is number of vertices
*/
bst_iter_t BSTBegin(const bst_t *bst);

/*
    Params: bst_t type pointer bst that represents the tree to find the iterator
	 after the last valid.
	 Return: Node after the last valid node.
    Complexity: O(1) where n is number of vertices
*/
bst_iter_t BSTEnd(const bst_t *bst);

/*
	Params: bst_iter_t type that represents the iterator to find the previous of
	Return: Previous iterator if exists, else: undefined behavior
	Complexity: O(log(n))
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*
	Params: bst_iter_t type that represents the iterator to find the next of
	Return: Next iterator according to sorting of the tree,
	BSTEnd if it is the last valid iterator
	Complexity: O(log(n))
*/
bst_iter_t BSTNext(bst_iter_t iter);

/*
	Params: bst_iter_t type iter_1 and iter_2 that represent the iterators to check
	if are the same
	Return: 1 if same iterator, else 0.
	Complexity: O(1).
*/
int BSTIsSameIter(bst_iter_t iter_1, bst_iter_t iter_2);

/*
	Params: bst_iter_t type that represent the iterators to get data from.
	Return: void ptr that represents that address of the value stored in iterator.
	Complexity: O(1).
*/
void *BSTGetData(bst_iter_t iter);

/*
	Params: bst_t type ptr that represent the tree to find in the data_to_match that
	was sent.
	Return: The iterator that holds data_to_match when found, else BSTEnd.
	Complexity: O(log(n)).
*/
bst_iter_t BSTFind(const bst_t *bst, void *data_to_match);

/*
	Params: from and to are bst_iter_t types that represent that range on which
	to do action_func operation with given param (not including to).
	Return: Status of action_func.
	NOTE: If action_func fails on one of the iterators, the operation will not
	proceed on next iterators.
	Complexity: O(n) where n is number of vertices in bst.
*/
int BSTForEach(bst_iter_t from, bst_iter_t to, action_t action_func, void *param);

#endif /* __BINARY_SEARCH_TREE__ */

