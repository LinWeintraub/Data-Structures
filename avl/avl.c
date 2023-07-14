/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          24/10/22                                        ~
 * Description   AVL                                             *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */
#ifndef NDEBUG
#include <stdio.h> /* printf */
#endif
#include "avl.h"

/*----------------------------------------------------------------------------*/
typedef enum 
{   
    LEFT = 0, 
    RIGHT = 1,
    NUM_CHILDREN = 2
} avl_direction_t;

typedef struct avl_node
{
	void *data;
	struct avl_node *children[NUM_CHILDREN];
	size_t height;
} avl_node_t;

struct avl
{
	avl_node_t *root;
	cmp_func_t cmp_func_p;
};

/*---------------------------Function Declarations----------------------------*/
static avl_node_t *CreateNode(void *data);
static avl_node_t *RecursiveInsert(avl_t *tree,
									avl_node_t *curr, 
									avl_node_t *new_node);
static void RecursiveDestroy(avl_node_t *node);
static size_t RecursiveSize(avl_node_t *node);
static void UpdateHeight(avl_node_t *node);
static avl_node_t *RecursiveRemove(avl_t *tree, 
									avl_node_t *node, 
									void *data);
static avl_node_t *Rotate(avl_node_t *node, avl_direction_t rotation_side);
static avl_node_t *BalanceSubTree(avl_node_t *node);
static avl_node_t *RecursiveFind(avl_t *tree,
									avl_node_t *node,
									void *data);
static int GetBalanceFactor(avl_node_t *node);
static void *GetPrevData(avl_node_t *node);
static status_t AVLForEachInOrder(avl_node_t *node, 
									action_t action_func,
									void *param);
static status_t AVLForEachPreOrder(avl_node_t *node,
									action_t action_func,
									void *param);
static status_t AVLForEachPostOrder(avl_node_t *node,
									action_t action_func,
									void *param);

/*---------------------------------API-Functions------------------------------*/
avl_t *AVLCreate(cmp_func_t cmp_func_p)
{
	avl_t *tree = malloc(sizeof(avl_t));	
	if (NULL == tree)
	{
		free(tree); tree = NULL;
		return NULL;
	}
	
	assert(cmp_func_p);
		
	tree->root = NULL;
	tree->cmp_func_p = cmp_func_p;
			
	return tree;
}

void AVLDestroy(avl_t *tree)
{
	assert(tree);

    if (NULL != tree->root)
    {
        RecursiveDestroy(tree->root);
    }
    
    free(tree);
}

status_t AVLRemove(avl_t *tree, const void *value)
{
	avl_node_t *result = NULL;

    assert(tree);

    if (NULL == tree->root)
    {
        return FAILURE;
    }

    result = RecursiveRemove(tree, tree->root, (void *)value);

    if (NULL != result)
    {
        tree->root = result;
        return SUCCESS;
    }

    return FAILURE;
}

status_t AVLInsert(avl_t *tree, void *value)
{
	avl_node_t *new_node = CreateNode(value);

    assert(tree);

    if (NULL == new_node)
    {
        return FAILURE;
    }

    if (NULL == tree->root)
    {
        tree->root = new_node;
        return FAILURE;
    }

    tree->root = RecursiveInsert(tree, tree->root, new_node);

    return SUCCESS;
}

size_t AVLHeight(const avl_t *tree)
{
    assert(tree);

    return (tree->root->height);
}

size_t AVLSize(const avl_t *tree)
{
    assert(tree);

    if (NULL == tree->root)
    {
        return 0;
    }

    return (RecursiveSize(tree->root));
}

int AVLIsEmpty(const avl_t *tree)
{
    assert(tree);

    return (NULL == tree->root);
}

void *AVLFind(const avl_t *tree, void *data_to_match)
{
	avl_node_t *result = NULL;

    assert(tree);

    if (NULL == tree->root)
    {
        return NULL;
    }

	result = RecursiveFind((avl_t *)tree, tree->root, data_to_match);

    return(result ? result->data : NULL);
}

int AVLForEach(avl_t *tree, action_t action_func_p, void *param, order_t order)
{
	status_t status = SUCCESS;
    
    assert(tree);
    assert(action_func_p);


    if (NULL == tree->root)
    {
        return status;
    }

    if (IN_ORDER == order)
    {
        AVLForEachInOrder(tree->root, action_func_p, param);
    }

    else if (PRE_ORDER == order)
    {
        AVLForEachPreOrder(tree->root, action_func_p, param);
    }

    else
    {
        AVLForEachPostOrder(tree->root, action_func_p, param);
    }

    return status;
}

/*------------------------------Static-Functions------------------------------*/
static avl_node_t *CreateNode(void *data)
{
	avl_node_t *new_node = malloc(sizeof(avl_node_t));
		
	if (NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->children[LEFT] = NULL;
	new_node->children[RIGHT] = NULL;
	new_node->height = 1;
	
	return new_node;
}

static avl_node_t *RecursiveInsert(avl_t *tree,
									avl_node_t *curr, 
									avl_node_t *new_node)
{
	int cmp_status = 0;
	avl_direction_t side = LEFT;

    assert(tree);
    assert(curr);
    assert(new_node);
	
	cmp_status = tree->cmp_func_p(new_node->data, curr->data);

	if (cmp_status > 0)
	{
		side = RIGHT;
	}
	
	else
	{
		side = LEFT;
	}

    if (NULL == curr->children[side])
    {
        curr->children[side] = new_node;
        UpdateHeight(curr);

        return curr;
    }

    curr->children[side] = RecursiveInsert(tree, curr->children[side], new_node);
    UpdateHeight(curr);
    curr = BalanceSubTree(curr);
    UpdateHeight(curr);

    return curr;
}

static avl_node_t *BalanceSubTree(avl_node_t *node)
{
    int balance_factor = 0;

    assert(node);

	balance_factor = GetBalanceFactor(node);

    if (balance_factor > 1 && GetBalanceFactor(node->children[LEFT]) >= 0)
    {
        return (Rotate(node, RIGHT));
    }

    if (balance_factor > 1 && GetBalanceFactor(node->children[LEFT]) < 0)
    {
        node->children[LEFT] = Rotate(node->children[LEFT], LEFT);
        return (Rotate(node, RIGHT));
    }

    if (balance_factor < -1 && GetBalanceFactor(node->children[RIGHT]) <= 0)
    {
      return (Rotate(node, LEFT));
    }

    if (balance_factor < -1 && GetBalanceFactor(node->children[RIGHT]) > 0)
    {
        node->children[RIGHT] = Rotate(node->children[RIGHT], RIGHT);
        return (Rotate(node, LEFT));
    }

    return node;
}

static avl_node_t *Rotate(avl_node_t *node, avl_direction_t rotation_side)
{
    avl_node_t *pivot = NULL;

	assert(node);

	pivot = node->children[!rotation_side];

    node->children[!rotation_side] = pivot->children[rotation_side];
    pivot->children[rotation_side] = node;
    node = pivot;

    UpdateHeight(node->children[rotation_side]);
    UpdateHeight(node);

    return node;
}

static void UpdateHeight(avl_node_t *node)
{
	size_t height_right = 0;
    size_t height_left = 0;
    size_t node_height = 0;
    
	assert(node);

    if (NULL != node->children[LEFT])
    {
        height_left = node->children[LEFT]->height;
    }

    if (NULL != node->children[RIGHT])
    {
        height_right = node->children[RIGHT]->height;
    }
     
    node_height = (height_left > height_right ? height_left : height_right) + 1;
    node->height = node_height;
}

static int GetBalanceFactor(avl_node_t *node)
{
    int left_height = 0;
    int right_height = 0;

	assert(node);

    if (NULL != node->children[LEFT])
    {
        left_height = node->children[LEFT]->height;
    }

    if (NULL != node->children[RIGHT])
    {
        right_height = node->children[RIGHT]->height;
    }

    return(left_height - right_height);
}

static void RecursiveDestroy(avl_node_t *node)
{
	if (NULL == node)
    {
        return;
    }

    RecursiveDestroy(node->children[LEFT]);
    RecursiveDestroy(node->children[RIGHT]);

    free(node);
}

static size_t RecursiveSize(avl_node_t *node)
{
	if (NULL == node)
	{
		return 0;
	}
    
    return (RecursiveSize(node->children[LEFT]) + 1 + 
			RecursiveSize(node->children[RIGHT])); 
}

static avl_node_t *RecursiveRemove(avl_t *tree, 
									avl_node_t *node,
									void *data)
{
	int cmp_status = 0;
	avl_direction_t side = LEFT;
	avl_node_t *save_child = NULL;

	assert(tree);

    cmp_status = tree->cmp_func_p(data, node->data);	

	if (cmp_status > 0)
	{
		side = RIGHT;
	}
	
	else if (cmp_status < 0)
	{
		side = LEFT;
	}

	if (cmp_status != 0)
	{
		node->children[side] = RecursiveRemove(tree, node->children[side], data);
	}

	else 
	{
		if (NULL == node->children[LEFT] && NULL == node->children[RIGHT])
		{
			free (node);
			return NULL;
		}

		else if (NULL == node->children[LEFT])
		{
			save_child = node->children[RIGHT];
			free(node);
			return save_child;
		}

		else if (NULL == node->children[RIGHT])
		{
			save_child = node->children[LEFT];
			free(node);
			return save_child;
		}

		else
		{
			node->data = GetPrevData(node->children[LEFT]);
			node->children[LEFT] = RecursiveRemove(tree, node->children[LEFT], node->data);
		}
	}
    
    UpdateHeight(node);
    node = BalanceSubTree(node);
    UpdateHeight(node);

    return (node);
}

static void *GetPrevData(avl_node_t *node)
{
    if (NULL == node->children[RIGHT])
    {
        return (node->data);
    }

    return (GetPrevData(node->children[RIGHT]));
}

static avl_node_t *RecursiveFind(avl_t *tree,
								avl_node_t *node,
								void *data)
{
	int cmp_status = 0;
	avl_direction_t side = LEFT;

	assert(tree);
	assert(node);
 	
	cmp_status = tree->cmp_func_p(data, node->data);

	if (NULL == node)
    {
        return NULL;
    }

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
		return node;
	} 

    return (RecursiveFind(tree, node->children[side], data));
}

static status_t AVLForEachInOrder(avl_node_t *node, 
									action_t action_func,
									void *param)
{
	status_t status = SUCCESS;

	assert(action_func);

	if (NULL == node)
    {
        return FAILURE;
    }

    AVLForEachInOrder(node->children[LEFT], action_func, param);

	status = action_func(param, node->data);
    if (SUCCESS != status)
    {
        return FAILURE;
    }

    AVLForEachInOrder(node->children[RIGHT], action_func, param);

	return SUCCESS;
}

static status_t AVLForEachPreOrder(avl_node_t *node,
									action_t action_func,
									void *param)
{
	status_t status = 0;

	assert(action_func);

	if (NULL == node)
    {
        return FAILURE;
    } 

	status = action_func(param, node->data);
    if (SUCCESS != status)
    {
        return FAILURE;
    }

    AVLForEachPreOrder(node->children[LEFT], action_func, param);
    AVLForEachPreOrder(node->children[RIGHT], action_func, param);

	return SUCCESS;
}

static status_t AVLForEachPostOrder(avl_node_t *node,
									action_t action_func,
									void *param)
{
	status_t status = 0;

	assert(action_func);

	if (NULL == node)
    {
        return FAILURE;
    }

    AVLForEachPostOrder(node->children[LEFT], action_func, param);
    AVLForEachPostOrder(node->children[RIGHT], action_func, param);

	status = action_func(param, node->data);
    if (SUCCESS != status)
    {
        return FAILURE;
    }

	return SUCCESS;
}

#ifndef NDBUG
void Print2DTree(avl_node_t *tree, int space)
{
    int i = 0;
    if (tree == NULL || tree->data == NULL)
    {
        return;
    }

    space += 10;

    Print2DTree(tree->children[RIGHT], space);
    printf("\n");

    for (i = 10; i < space; i++)
    {
        printf(" ");
    }

	if(tree->data != NULL)
	{
		printf("%d|h%ld|B%d\n", *(int *)tree->data, tree->height, GetBalanceFactor(tree));
	}

    Print2DTree(tree->children[LEFT], space);
}

int AVLPrintNode(void *param, void *data)
{
    (void)param;
    printf("%d, ", *(int*)(data));

    return 0;
}

avl_node_t *GetRoot(avl_t * tree)
{
    return (tree->root);
}
#endif
