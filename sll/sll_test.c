/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Single Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h>

#include "sll.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

void TestSListCreate(void);
void TestInsertRemoveCountGet(void);
void TestNextEndFirstSetFindForeach(void);
void TestSListAppendSList(void);
void PrintList(iterator_t list);

int IsMatch(void *param_a, void *param_b);
int PrintInt(void *param_a, void *param_b);

int main (void)
{

    TestSListCreate();
    TestInsertRemoveCountGet();
    TestNextEndFirstSetFindForeach();
    TestSListAppendSList();

	return 0;
}

void TestSListCreate(void)
{
    sll_t *test = SListCreate();
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("SListCreate test1: ",test , NULL);
	SListDestroy(test);

}

void TestInsertRemoveCountGet(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    sll_t *test_list = SListCreate();
    iterator_t my_iter;
    iterator_t my_iter2 = SListIteratorFirst(test_list);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        my_iter = SListInsert(SListIteratorFirst(test_list), &test_arr[i]);
        printf("Insert + GetValue test %d", i);
        TEST("",SListGetValue(my_iter), &test_arr[i]);
    }
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("IsEqual test",IsItrEqual(my_iter, my_iter2), 1);
    TEST("Count test1",SListSize(test_list), 10);
    TEST("IsEmpty test1",SListIsEmpty(test_list), 0);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 9; i >= 0; i--)
    {
        printf("Remove + GetValue test %d", i);
        TEST("",SListGetValue(my_iter), &test_arr[i]);
        my_iter = SListRemove(SListIteratorFirst(test_list));
    }

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("Count test2 after deletion",SListSize(test_list), 0);
    TEST("IsEmpty test2 after deletion",SListIsEmpty(test_list), 1);
    
	SListDestroy(test_list);
}

void TestNextEndFirstSetFindForeach(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int to_set = 33;
    int i = 0;
    sll_t *test_list = SListCreate();
    iterator_t my_iter;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        SListInsert(SListIteratorFirst(test_list), &test_arr[i]);
    }
    my_iter = SListIteratorFirst(test_list);
    for(i = 9; i >= 0; i--)
    {
        TEST("test Next",SListGetValue(my_iter), &test_arr[i]);
        my_iter = SListIteratorNext(my_iter);
    }

    TEST("test Next NULL",SListGetValue(my_iter), test_list);

    TEST("End test",SListGetValue(SListIteratorEnd(test_list)), test_list);
    
    printf("\n %d \n", *(int *)(SListGetValue(SListIteratorEnd(test_list))));
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    my_iter = SListFind(SListIteratorFirst(test_list), SListIteratorEnd(test_list), &IsMatch, &test_arr[3]);

    TEST("find test", SListGetValue(my_iter), &test_arr[3]);

    SListSetValue(my_iter, &to_set);

    TEST("set test", SListGetValue(my_iter), &to_set);
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("foreach test",SListForEach(SListIteratorFirst(test_list), SListIteratorEnd(test_list), &PrintInt, (void *) 1), 0);
    
	SListDestroy(test_list);
}

void TestSListAppendSList(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    
	sll_t *test_list = SListCreate();
	sll_t *test_list_2 = SListCreate();
    
	
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        SListInsert(SListIteratorFirst(test_list), &test_arr[i]);
    }

    printf("test_list:\n");
	SListForEach(SListIteratorFirst(test_list), SListIteratorEnd(test_list), &PrintInt, (void *) 1);
    
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 5; i++)
    {
        SListInsert(SListIteratorFirst(test_list_2), &test_arr[i]);
    }

    printf("test_list_2:\n");
	SListForEach(SListIteratorFirst(test_list_2), SListIteratorEnd(test_list_2), &PrintInt, (void *) 1);
	
	printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    SListAppendSList(test_list, test_list_2);
    
    SListForEach(SListIteratorFirst(test_list), SListIteratorEnd(test_list), &PrintInt, (void *) 1);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    SListForEach(SListIteratorFirst(test_list_2), SListIteratorEnd(test_list_2), &PrintInt, (void *) 1);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("Count test_list",SListSize(test_list), 15);
    TEST("IsEmpty test_list",SListIsEmpty(test_list), 0);
    TEST("Count test_list_2",SListSize(test_list_2), 0);
    TEST("IsEmpty test_list_2",SListIsEmpty(test_list_2), 1);
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

