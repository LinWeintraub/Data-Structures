/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          15/11/22                                        ~
 * Description   Binary Search Tree                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */

#include "bst.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
    
void TestBSTCreate(void);
void TestInsertForEachSizeIsEmpty(void);
void TestBSTNextBSTPrev(void);
void TestBSTBeginBSTEnd(void);
void TestBSTInsertBSTRemove(void);

void Print2DTreeWraper(bst_iter_t itr, int space);
int CmpFunction(void *param_a, void *param_b);
int PrintInt(void *param_a, void *param_b);

int main(void)
{
	TestBSTCreate();
	TestBSTInsertBSTRemove();
	TestInsertForEachSizeIsEmpty();
	TestBSTNextBSTPrev();
	TestBSTBeginBSTEnd();
	
	return 0;
}

int CmpFunction(void *param_a, void *param_b)
{
	return (*(int *)param_a - *(int *)param_b);
}

void TestBSTCreate(void)
{
    bst_t *test = BSTCreate(&CmpFunction);
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("BSTCreate test1: ",test , NULL);
    
	BSTDestroy(test);
}

int PrintInt(void *param_a, void *param_b)
{
	(void)param_a;
    printf("%d-->", *(int *)param_b);
    
    return 0;
}

void TestBSTInsertBSTRemove(void)
{
	int a = 7;
	int b = 5;
	int c = 100;
	int d = 6;
	int e = 101;
	int f = 8;
	
	bst_t *test_tree = BSTCreate(&CmpFunction);
	bst_iter_t my_iter1 = BSTInsert(test_tree, &a);
	bst_iter_t my_iter2 = {0};
	bst_iter_t my_iter3 = {0};
	bst_iter_t my_iter4 = {0};
	
	my_iter4 = BSTInsert(test_tree, &b);
	
	my_iter2 = BSTInsert(test_tree, &c);
	
	BSTInsert(test_tree, &d);
	BSTInsert(test_tree, &e);
	
	my_iter3 = BSTInsert(test_tree, &f);

	
	printf("----------Insert & Remove:----------\n");
	
	Print2DTreeWraper(my_iter1, 5);
	printf("\n\n---------------------\n\n");
	
	BSTRemove(my_iter2);
	
	Print2DTreeWraper(my_iter1, 5);
	printf("\n\n---------------------\n\n");
	
	BSTRemove(my_iter3);
	
	Print2DTreeWraper(my_iter1, 5);
	printf("\n\n---------------------\n\n");
	
	BSTRemove(my_iter1);
	
	Print2DTreeWraper(my_iter4, 5);
	
	BSTDestroy(test_tree); 
}

void TestInsertForEachSizeIsEmpty(void)
{
	int a = 7;
	int b = 5;
	int c = 100;
	int d = 6;
	int e = 101;
	int f = 8;
	
	bst_t *test_tree = BSTCreate(&CmpFunction);
	bst_iter_t my_iter1 = BSTInsert(test_tree, &a);
	bst_iter_t my_iter2 = {0};
	
	BSTInsert(test_tree, &b);
	BSTInsert(test_tree, &c);
	BSTInsert(test_tree, &d);
	BSTInsert(test_tree, &e);
	BSTInsert(test_tree, &f);

	printf("----------Foreach Test:----------\n");
    BSTForEach(BSTBegin(test_tree), BSTEnd(test_tree), &PrintInt, (void *) 1);
    
	printf("\n----------Size & IsEmpty & Find Test:----------\n");

    TEST("Size test1", BSTSize(test_tree), 6);
    TEST("IsEmpty test1", BSTIsEmpty(test_tree), 0);
    
    my_iter2 = BSTFind(test_tree, &c);
	TEST("Find Test", BSTGetData(my_iter2) ,&c);

	BSTDestroy(test_tree);
}

void TestBSTNextBSTPrev(void)
{
	int a = 7;
	int b = 5;
	int c = 100;
	int d = 6;
	int e = 101;
	int f = 8;
	
	bst_t *test_tree = BSTCreate(&CmpFunction);
	bst_iter_t my_iter1 = BSTInsert(test_tree, &a);
	bst_iter_t my_iter2 = {0};
	
	BSTInsert(test_tree, &b);
	BSTInsert(test_tree, &c);
	BSTInsert(test_tree, &d);
	my_iter2 = BSTInsert(test_tree, &e);
	BSTInsert(test_tree, &f);

	printf("----------NEXT & Prev & Is SameIter Test:----------\n");

	my_iter1 = BSTNext(my_iter1);
	TEST("Next1", BSTGetData(my_iter1), &f);

	my_iter1 = BSTNext(my_iter1);	
	TEST("Next2", BSTGetData(my_iter1), &c);

	my_iter1 = BSTNext(my_iter1);
	TEST("Next3", BSTGetData(my_iter1), &e);
	
	my_iter1 = BSTNext(my_iter1);
	TEST("Next4", BSTGetData(my_iter1), NULL);

	my_iter2 = BSTPrev(my_iter2);
	TEST("Prev1", BSTGetData(my_iter2), &c);

	my_iter2 = BSTPrev(my_iter2);
	TEST("Prev2", BSTGetData(my_iter2), &f);

	my_iter2 = BSTPrev(my_iter2);
	TEST("Prev3", BSTGetData(my_iter2), &a);

	my_iter2 = BSTPrev(my_iter2);
	TEST("Prev4", BSTGetData(my_iter2), &d);

	my_iter2 = BSTPrev(my_iter2);
	TEST("Prev5", BSTGetData(my_iter2), &b);

	TEST("BSTIsSameIter", BSTIsSameIter(my_iter1, my_iter1), 1);

	BSTDestroy(test_tree);
}

void TestBSTBeginBSTEnd(void)
{
	int a = 7;
	int b = 5;
	int c = 100;
	int d = 6;
	int e = 101;
	int f = 8;
	int g = 1;
	
	bst_t *test_tree = BSTCreate(&CmpFunction);
	bst_iter_t my_iter1 = BSTInsert(test_tree, &a);
	BSTInsert(test_tree, &b);
	BSTInsert(test_tree, &c);
	BSTInsert(test_tree, &d);
	BSTInsert(test_tree, &e);
	BSTInsert(test_tree, &f);
	BSTInsert(test_tree, &g);
	
	printf("----------Begin & End Test----------\n");

	my_iter1 = BSTEnd(test_tree);
	TEST("End Test", BSTGetData(my_iter1), NULL);

	my_iter1 = BSTBegin(test_tree);
	TEST("Begin Test", BSTGetData(my_iter1), &g);

	BSTDestroy(test_tree);

	return;
}
