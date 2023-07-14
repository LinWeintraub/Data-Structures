/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          24/10/22                                        ~
 * Description   AVL                                             *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdio.h> /* printf */

#include "avl.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

typedef struct avl_node avl_node_t;

void TestAVLCreate(void);
void TestAVLInsert(void);
void TestAVLRemove(void);

int CmpFunction(void *param, void *value);
int AVLPrintNode(void *data, void *param);
avl_node_t *GetRoot(avl_t * tree);
void Print2DTree(avl_node_t *tree, int space);


int main(void)
{
    TestAVLCreate();
    TestAVLInsert();
    TestAVLRemove();

	return 0;
}

void TestAVLCreate(void)
{
    avl_t *tree = AVLCreate(&CmpFunction);

	printf("----------Create & IsEmpty test:----------\n");

    TEST("AVLCreate", (tree != NULL), 1);
    TEST("AVLIsEmpty", AVLIsEmpty(tree), 1);

    AVLDestroy(tree);
}

void TestAVLInsert(void)
{
    int int_arr[10] = {4, 5 , 3, 1, 0, -5, 50 , 8, 9, 2};
    int i = 0;
    avl_t *tree = AVLCreate(&CmpFunction);

	printf("----------Insert & Size & Height & Find Test:----------\n");

    TEST("Size Empty Test", AVLSize(tree), 0);

    for (i = 0; i < 10; i++)
    {
        AVLInsert(tree, &int_arr[i]);
    }

    TEST("Size 10 Test", AVLSize(tree), 10);
    TEST("AVLHeight", AVLHeight(tree), 4);
    TEST("AVLIsEmpty", AVLIsEmpty(tree), 0);
    TEST("AVLFind test",AVLFind(tree, &int_arr[9]), &int_arr[9]);

    AVLDestroy(tree);
}


void TestAVLRemove(void)
{
    int int_arr[10] = {4, 5 , 3, 1, 0, -5, 50 , 8, 9, 2};
    int to_remove_minus5 = -5;
    int to_remove_1 = 1;
    int to_remove_2 = 2;
    int to_remove_4 = 4;

    int i = 0;
    avl_t *tree = AVLCreate(&CmpFunction);

	printf("----------Insert & Remove & ForEach Test:----------\n");

    for (i = 0; i < 10; i++)
    {
        AVLInsert(tree, &int_arr[i]);
    }

    printf("Print test:\n");
    Print2DTree(GetRoot(tree), 5);
    printf("\n");

    printf("ForEachTest In Order Print test:\n");
    AVLForEach(tree, AVLPrintNode, &int_arr[0], IN_ORDER);

    printf("\nForEachTest Post Order Print test:\n");
    AVLForEach(tree, AVLPrintNode, &int_arr[0], POST_ORDER);

    printf("\nForEachTest Pre Order Print test:\n");
    AVLForEach(tree, AVLPrintNode, &int_arr[0], PRE_ORDER);


    AVLRemove(tree, &to_remove_minus5);
    printf("\n----------Removed -5 Test:----------\n");
    Print2DTree(GetRoot(tree), 5);

    AVLRemove(tree, &to_remove_1);
    printf("----------Removed 1 Test:----------\n");
    Print2DTree(GetRoot(tree), 5);

    AVLRemove(tree, &to_remove_2);
    printf("----------Removed 2 Test:----------\n");
    Print2DTree(GetRoot(tree), 5);

    AVLRemove(tree, &to_remove_4);
    printf("----------Removed 4 (was root) Test:----------\n");
    Print2DTree(GetRoot(tree), 5);

    AVLDestroy(tree);
}

int CmpFunction(void *param, void *value)
{
	return (*(int *)param - *(int *)value);
}

