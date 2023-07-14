/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          15/11/22                                        ~
 * Description   Binary Search Tree                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert */

#ifndef NDBUG
#include <stdio.h> /* printf */ 
#endif

#include "bst.h"

typedef enum 
{   
    LEFT = 0, 
    RIGHT = 1,
    NUM_CHILDREN = 2
} bst_direction_t;

struct bst_node
{
	bst_node_t *parent;
	bst_node_t *children[NUM_CHILDREN];
	void *value;
};

struct bst
{
	bst_node_t root;
	cmp_func_t cmp_func_p;
};

static bst_node_t *CreateNode(void *value);
static bst_node_t *BSTGetParent(bst_node_t *node);
static bst_node_t *BSTGetLeftChild(bst_node_t *node);
static bst_node_t *BSTGetRightChild(bst_node_t *node);
static int BSTIsSameNode(bst_node_t *node_1, bst_node_t *node_2);
static bst_node_t *BSTGetParentLeftChild(bst_node_t *node);
static int BSTGetNodeSide(bst_node_t *node);

bst_t *BSTCreate(cmp_func_t cmp_func_p)
{
	bst_node_t root;
	
	bst_t *tree = malloc(sizeof(bst_t));
	if (NULL == tree)
	{
		return NULL;
	}
	
	assert(cmp_func_p);
	
	root.parent = NULL;
	root.children[LEFT] = NULL;
	root.children[RIGHT] = NULL;
	root.value = NULL;
	
	tree->root = root;
	tree->cmp_func_p = cmp_func_p;
			
	return tree;
}

void BSTDestroy(bst_t *bst)
{
	assert(bst);
	
	while (!(BSTIsEmpty(bst)))
	{
		BSTRemove(BSTBegin(bst));
	}
	
	free(bst); bst = NULL;
}

size_t BSTSize(const bst_t *bst)
{
	bst_iter_t start = BSTBegin((bst_t *)bst);
	bst_iter_t end = BSTEnd((bst_t *)bst);
	size_t counter = 0;
	
	assert(bst);
		
	while (!BSTIsSameIter(start, end))
	{
		start = BSTNext(start);
		++counter;
	}
	
	return counter;
}

int BSTIsEmpty(const bst_t *bst)
{
	assert(bst);

	return (bst->root.children[LEFT] == NULL);
}

bst_iter_t BSTInsert(bst_t *bst, void *value)
{
	int cmp_status = 0;
	
	bst_node_t *parent = NULL;
	bst_node_t *curr = NULL;
	bst_node_t *new_node = CreateNode(value);
	int child = LEFT;
	bst_iter_t bst_itr = {0};
	
	assert(bst);
	
	bst_itr.node = &bst->root;
	parent = &bst->root;
	curr = bst->root.children[LEFT];
		
	if (NULL == new_node)
	{
		return bst_itr;
	}
	
	while (NULL != curr)
	{
		parent = curr;
		cmp_status = bst->cmp_func_p(value, curr->value);
		
		if (cmp_status > 0)
		{
			child = RIGHT;
		}
		
		else
		{
			child = LEFT;
		}
		
		curr = curr->children[child];
	}
	
	parent->children[child] = new_node;
	new_node->parent = parent;
	
	bst_itr.node = new_node;
		
	return bst_itr;
}

void BSTRemove(bst_iter_t iter_to_remove)
{
	bst_node_t *curr = NULL;
	bst_iter_t curr_prev = {0};
	bst_node_t *child = NULL;
	bst_node_t *parent = NULL;
	int side = RIGHT;
	
	assert(iter_to_remove.node);
	
	curr = iter_to_remove.node;
	curr_prev = iter_to_remove;
	side = BSTGetNodeSide(curr);
		
	if (NULL == BSTGetLeftChild(curr) && NULL == BSTGetRightChild(curr))
	{
		curr->parent->children[side] = NULL;
		
		free(curr); curr = NULL;
	}
	
	else if (NULL == BSTGetLeftChild(curr) && NULL != BSTGetRightChild(curr))
	{
		child = BSTGetRightChild(curr);
		parent = BSTGetParent(curr);
		
		parent->children[side] =  child;
		child->parent = parent;
		
		free(curr); curr = NULL;
	}
	
	else if (NULL == BSTGetRightChild(curr) && NULL != BSTGetLeftChild(curr))
	{
		child = BSTGetLeftChild(curr);
		parent = BSTGetParent(curr);
		
		parent->children[side] =  child;
		child->parent = parent;
		
		free(curr); curr = NULL;
	}
	
	else                           
	{
		parent = BSTGetParent(curr);
		parent->children[side] = BSTGetLeftChild(curr);
		curr->children[LEFT]->parent = parent;
		
		curr_prev = BSTPrev(iter_to_remove);
		curr_prev.node->children[RIGHT] = BSTGetRightChild(curr);
		curr->children[RIGHT]->parent = curr_prev.node;
		
		free(curr); curr = NULL;
	}
}

bst_iter_t BSTBegin(const bst_t *bst)
{
	bst_node_t *curr = NULL;
	bst_iter_t bst_itr = {0};
		
	assert(bst);

	curr = &((bst_t *)bst)->root;
	
	while (NULL != BSTGetLeftChild(curr))
	{
		curr = BSTGetLeftChild(curr);
	}
	
	bst_itr.node = curr;
	
	return bst_itr;
}

bst_iter_t BSTEnd(const bst_t *bst)
{
	bst_iter_t bst_itr = {0};
		
	assert(bst);
		
	bst_itr.node = &((bst_t *)bst)->root;
	
	return bst_itr;
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
	bst_node_t *curr = NULL;
	
	assert(iter.node);
	
	curr = iter.node;
	
	if (NULL != BSTGetLeftChild(curr))
	{
		curr = BSTGetLeftChild(curr);
		
		while (NULL != BSTGetRightChild(curr))
		{
			curr = BSTGetRightChild(curr);
		}
	}
	
	else
	{
		while (BSTIsSameNode(BSTGetParentLeftChild(curr), curr))
		{
			curr = BSTGetParent(curr);
		}

		curr = BSTGetParent(curr);
	}
	
	iter.node = curr;
	
	return iter;	
}
   
bst_iter_t BSTNext(bst_iter_t iter)
{
	bst_node_t *curr = NULL;
	
	assert(iter.node);
	
	curr = iter.node;
	
	if (NULL != BSTGetRightChild(curr))
	{
		curr = BSTGetRightChild(curr);
		
		while (NULL != BSTGetLeftChild(curr))
		{
			curr = BSTGetLeftChild(curr);
		}
	}
	
	else
	{
		while (!BSTIsSameNode(BSTGetParentLeftChild(curr), curr))
		{
			curr = BSTGetParent(curr);
		}

		curr = BSTGetParent(curr);
	}
	
	iter.node = curr;
	
	return iter;	
}

int BSTIsSameIter(bst_iter_t iter_1, bst_iter_t iter_2)
{
	assert(iter_1.node);
	assert(iter_2.node);

	return (iter_1.node == iter_2.node); 
}

void *BSTGetData(bst_iter_t iter)
{
	assert(iter.node);

	return (iter.node->value);
}

bst_iter_t BSTFind(const bst_t *bst, void *data_to_match)
{
	bst_node_t *runner = NULL;
	bst_iter_t find_value = {0}; 
	int side = LEFT;
	int cmp_status = -1;
	
	assert(bst);
	
	runner = bst->root.children[LEFT];
	find_value.node = &((bst_t *)bst)->root; 
		
	while (NULL != runner && (0 != cmp_status))
	{
		cmp_status = bst->cmp_func_p(data_to_match, runner->value);
		
		if (cmp_status > 0)
		{
			side = RIGHT;
		}
		
		else if (cmp_status < 0)
		{
			side = LEFT;
		}
		
		else
		{
			break;
		}
		runner = runner->children[side];
	}
	
	if (NULL != runner)
	{
		find_value.node = runner;
	}
	
	return find_value;
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_t action_func, void *param)
{
	int status = 0;
	
	assert(from.node);
	assert(to.node);
	assert(action_func);
	
    while (!BSTIsSameIter(from, to) && 1 != status)
    {
      status = action_func(param, BSTGetData(from));
      from = BSTNext(from);
    }
	
	return status;
}

/*-------------------------StaticFunctions-------------------------*/
static bst_node_t *CreateNode(void *value)
{
	bst_node_t *new_node = malloc(sizeof(bst_node_t));
		
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->value = value;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	
	return new_node;
}

static bst_node_t *BSTGetParent(bst_node_t *node)
{
    assert(node);
    
	return node->parent;
}

static bst_node_t *BSTGetLeftChild(bst_node_t *node)
{
    assert(node);
    
	return node->children[LEFT];
}

static bst_node_t *BSTGetRightChild(bst_node_t *node)
{
    assert(node);
    
	return node->children[RIGHT];
}

static int BSTIsSameNode(bst_node_t *node_1, bst_node_t *node_2)
{
	return (node_1 == node_2); 
}

static bst_node_t *BSTGetParentLeftChild(bst_node_t *node)
{    
    assert(node);
    
    return node->parent->children[LEFT];
}

static int BSTGetNodeSide(bst_node_t *node)
{
	int side = RIGHT;
	
    assert(node);
    assert(node->parent);
    
	if (BSTIsSameNode(BSTGetParentLeftChild(node), node))
	{
			side = LEFT;
	}
	
	return side;
}

#ifndef NDBUG
void Print2DTree(bst_node_t *node, int space)
{
    int i = 0;
    if (node == NULL || node->value == NULL)
    {
        return;
    }

    space += 10;

    Print2DTree(node->children[RIGHT], space);
    

    printf("\n");
    for (i = 10; i < space; i++)
    {
    	printf(" ");
    }


	if(node->value != NULL)
    printf("%d\n", *(int *)node->value);
    
    Print2DTree(node->children[LEFT], space);
}

void Print2DTreeWraper(bst_iter_t itr, int space)
{
	Print2DTree(itr.node, space);
}

#endif
