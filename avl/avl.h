#ifndef __AVL__
#define __AVL__

#include "dll.h"

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

typedef int (*cmp_func_t)(void *param, void *value);

typedef enum 
{
	SUCCESS = 0,
	FAILURE = 1
} status_t;   

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} order_t;

/*----------------------------------------------------------------------------*/
/*
    Params: cmp_func_p is the function with which comparison is done between 
    different values of the avl.
    Return: A avl_t type pointer to the tree if succeeds, NULL if fails.
    Complexity: O(1)
*/
avl_t *AVLCreate(cmp_func_t cmp_func_p);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer to the tree to destroy.
    Return: No return value.
    Complexity: O(n) where n is number of vertices
*/
void AVLDestroy(avl_t *tree);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer to the tree and the value to search and remove 
    from the tree.
    Return: success or failure status that describes if the node was found and 
    removed succsessfully.
    Complexity: O(log n)
*/
status_t AVLRemove(avl_t *tree, const void *value);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer to the tree to insert to, value is the ptr to 
    the value which is to be stored in the tree.
    Return: success or failure status 
    Complexity: O(log n)
*/
status_t AVLInsert(avl_t *tree, void *value);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer to the tree to insert to, value is the ptr to 
    the value which is to be stored in the tree.
    Return: success or failure status.
    Complexity: O(1).
*/
size_t AVLHeight(const avl_t *tree);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer avl that represents the tree to get size of
    Return: size of tree.
    Complexity: O(n)
*/
size_t AVLSize(const avl_t *tree);


/*----------------------------------------------------------------------------*/
/*
    Params: avl_t type pointer avl that represents the tree to check if empty.
    Return: 1 if empty, else 0.
    Complexity: O(1)
*/
int AVLIsEmpty(const avl_t *tree);


/*----------------------------------------------------------------------------*/
/*
	Params: avl_t type ptr to the tree to find the data_to_match that
	was sent.
	Return: The node that holds data_to_match when found, else AVLEnd.
	Complexity: O(log(n)).
*/
void *AVLFind(const avl_t *tree, void *data_to_match);


/*----------------------------------------------------------------------------*/
/*
	Params: avl_t type ptr to the tree, function pointer to the action to 
    perform and void pointer to the parameter to use in the action.
	Return: success or failure status of the action_func_p function;
	Complexity: O(n).
*/
int AVLForEach(avl_t *tree, action_t action_func_p, void *param, order_t order);



/*-------------------------------Advanced-------------------------------------*/
/*
	Params: avl_t type ptr that represent the tree to find the multiple elements 
	according to cmp_func_ptr, param to compare, array items to fill.
	Return: success or failure that represents the failure of allocation for the 
	found_items list.
	Note: To check how many nodes were found, use the size func of the d_list on 
	the found_items list. 
	Complexity: O(n).
*/
status_t AVLMultiFindIf(avl_t *tree, 
                        int (*is_match_func)(void *value, void *param),
                        void *param, 
					 	dll_t *found_items);

#endif /* __AVL__ */

