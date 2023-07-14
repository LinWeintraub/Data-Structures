/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          20/10/22                                        ~
 * Description   Sorted Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdio.h>

#include "sorted_list.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

void TestSDListCreate(void);
void TestInsertRemoveCountGet(void);
void TestNextEndFirstSetFindForeach(void);
void TestMerge(void);

int CmpFunction(void *param_a, void *param_b);
int PrintInt(void *param_a, void *param_b);

int main(void)
{

    TestSDListCreate();
    TestInsertRemoveCountGet();
    TestNextEndFirstSetFindForeach();
    TestMerge();
	
	return 0;
}

void TestSDListCreate(void)
{
    sdll_t *test = SDListCreate(&CmpFunction);
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("SDListCreate test1: ",test , NULL);
    
	SDListDestroy(test);
}    
    
int CmpFunction(void *param_a, void *param_b)
{
	return (*(int *)param_a - *(int *)param_b);
}

int PrintInt(void *param_a, void *param_b)
{
	(void)param_a;
    printf("%d-->", *(int *)param_b);
    
    return 0;
}

int IsMatch(void *param_a, void *param_b)
{
	if (*(int *)param_a != *(int *)param_b)
	{
		return 0;
	}
	
	return 1;
}

void TestInsertRemoveCountGet(void)
{
    int test_arr[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int i = 0;
    sdll_t *test_list = SDListCreate(&CmpFunction);
    sdll_iterator_t my_iter;
    sdll_iterator_t my_iter2 = SDListIteratorFirst(test_list);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for (i = 0; i < 10; i++)
    {
        my_iter = SDListInsert(test_list, &test_arr[i]);
        printf("Insert + GetValue test %d", i);
        TEST("",SDListGetValue(my_iter), &test_arr[i]);
    }
    SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("IsEqual test", SDListIsIterEqual(my_iter, my_iter2), 0);
    TEST("Count test1", SDListSize(test_list), 10);
    TEST("IsEmpty test1", SDListIsEmpty(test_list), 0);
        
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
	TEST("Pop Front", *(int *)(SDListPopFront(test_list)), 0);

    SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1);
    printf("\n");
	TEST("Pop Front", SDListGetValue((SDListIteratorFirst(test_list))), &test_arr[5]);
	
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    SDListPopBack(test_list);
	TEST("Pop Back", SDListGetValue(SDListIteratorPrev(SDListIteratorEnd(test_list))), &test_arr[4]);
    SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1);
	
	printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#");
    for (i = 0; i < 9; i++)
    {
        printf("\nRemove + GetValue test %d \n", i);
		SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1);
        my_iter = SDListRemove(SDListIteratorFirst(test_list));
    }
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
	TEST("Count test2 after deletion", SDListSize(test_list), 0);
    TEST("IsEmpty test2 after deletion", SDListIsEmpty(test_list), 1);
    
	SDListDestroy(test_list);
}

void TestNextEndFirstSetFindForeach(void)
{
    int test_arr[] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
    int test_arr_sorted[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    sdll_t *test_list = SDListCreate(&CmpFunction);
    sdll_iterator_t my_iter;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for (i = 0; i < 10; i++)
    {
        SDListInsert(test_list, &test_arr[i]);
    }

    my_iter = SDListIteratorFirst(test_list);
    
    for (i = 0; i < 10; i++)
    {
		TEST("test Next", *(int *)SDListGetValue(my_iter), test_arr_sorted[i]);  
        my_iter = SDListIteratorNext(my_iter);
    }

    TEST("test Next NULL", SDListIteratorNext(my_iter), NULL);
 
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    my_iter = SDListFindIf(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &IsMatch, &test_arr[3]);

    TEST("find test", SDListGetValue(my_iter), &test_arr[3]);
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("foreach test", SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1), 0);
    
	SDListDestroy(test_list);
}

void TestMerge(void)
{
    int test_arr[] = {1, 2, 5, 6, 8};
    int test_arr_sorted[] = {3, 4, 9};
    int i = 0;
    sdll_t *test_list = SDListCreate(&CmpFunction);
    sdll_t *test_list_2 = SDListCreate(&CmpFunction);
    sdll_iterator_t from = NULL;
    sdll_iterator_t to = NULL;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for (i = 0; i < 5; i++)
    {
        SDListInsert(test_list, &test_arr[i]);
    }
    
    for (i = 0; i < 3; i++)
    {
        SDListInsert(test_list_2, &test_arr_sorted[i]);
    }
   
    from = SDListIteratorFirst(test_list_2);
    to = SDListIteratorEnd(test_list_2);
     
    SDListSMerge(from, to, test_list);
    
    SDListForEach(SDListIteratorFirst(test_list), SDListIteratorEnd(test_list), &PrintInt, (void *) 1);
    SDListForEach(SDListIteratorFirst(test_list_2), SDListIteratorEnd(test_list_2), &PrintInt, (void *) 1);
}
