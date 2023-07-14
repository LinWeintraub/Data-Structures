/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          19/10/22                                        ~
 * Description   Doubly Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdio.h>

#include "dll.h"

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
void TestDListSplice(void);
void TestDListMultiFind(void);

int IsMatch(void *param_a, void *param_b);
int PrintInt(void *param_a, void *param_b);

int main(void)
{

    TestSListCreate();
    TestInsertRemoveCountGet();
    TestNextEndFirstSetFindForeach();
	TestDListSplice();
	TestDListMultiFind();
	
	return 0;
}

void TestSListCreate(void)
{
    dll_t *test = DListCreate();
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("DListCreate test1: ",test , NULL);
	DListDestroy(test);
}

void TestInsertRemoveCountGet(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    dll_t *test_list = DListCreate();
    dll_iterator_t my_iter;
    dll_iterator_t my_iter2 = DListIteratorFirst(test_list);
    int to_set = 33;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        my_iter = DListInsertBefore(DListIteratorFirst(test_list), &test_arr[i]);
        printf("Insert + GetValue test %d", i);
        TEST("",DListGetValue(my_iter), &test_arr[i]);
    }
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("IsEqual test",DListIsIterEqual(my_iter, my_iter2), 0);
    TEST("Count test1",DListSize(test_list), 10);
    TEST("IsEmpty test1",DListIsEmpty(test_list), 0);
    
    DListPushFront(test_list, &test_arr[3]);
	TEST("Push Front", DListGetValue(DListIteratorFirst(test_list)), &test_arr[3]);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    DListPushBack(test_list, &test_arr[3]);
	TEST("Push Back", DListGetValue(DListIteratorPrev(DListIteratorEnd(test_list))), &test_arr[3]);
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
	TEST("Pop Front", *(int *)(DListPopFront(test_list)), test_arr[3]);
	TEST("Pop Front", DListGetValue((DListIteratorFirst(test_list))), &test_arr[9]);
	
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    DListPopBack(test_list);
	TEST("Pop Back", DListGetValue(DListIteratorPrev(DListIteratorEnd(test_list))), &test_arr[0]);
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 9; i >= 0; i--)
    {
        printf("Remove + GetValue test %d", i);
        TEST("",DListGetValue(my_iter), &test_arr[i]);
        my_iter = DListRemove(DListIteratorFirst(test_list));
    }
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
	TEST("Count test2 after deletion",DListSize(test_list), 0);
    TEST("IsEmpty test2 after deletion",DListIsEmpty(test_list), 1);
    
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    DListSetValue(my_iter, &to_set);
    TEST("set test", DListGetValue(my_iter), &to_set);

	DListDestroy(test_list);

}

void TestNextEndFirstSetFindForeach(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    dll_t *test_list = DListCreate();
    dll_iterator_t my_iter;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        DListInsertBefore(DListIteratorFirst(test_list), &test_arr[i]);
    }
    my_iter = DListIteratorFirst(test_list);
    for(i = 9; i >= 0; i--)
    {
        TEST("test Next",DListGetValue(my_iter), &test_arr[i]);
        my_iter = DListIteratorNext(my_iter);
    }

    TEST("test Next NULL",DListGetValue(my_iter), test_list);

    TEST("End test",DListGetValue(DListIteratorEnd(test_list)), test_list);
      
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    my_iter = DListFind(DListIteratorFirst(test_list), DListIteratorEnd(test_list), &IsMatch, &test_arr[3]);

    TEST("find test", DListGetValue(my_iter), &test_arr[3]);
	
	printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("foreach test",DListForEach(DListIteratorFirst(test_list), DListIteratorEnd(test_list), &PrintInt, (void *) 1), 0);
    
	DListDestroy(test_list);
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

void TestDListSplice(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    
	dll_t *test_list = DListCreate();
	dll_t *test_list_2 = DListCreate();
    dll_iterator_t from = DListIteratorFirst(test_list);
    dll_iterator_t to = DListIteratorEnd(test_list);
    dll_iterator_t position = DListIteratorFirst(test_list_2);
    	
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; i++)
    {
        DListInsertBefore(DListIteratorFirst(test_list), &test_arr[i]);
    }

    printf("test_list:\n");
	DListForEach(DListIteratorFirst(test_list), DListIteratorEnd(test_list), &PrintInt, (void *) 1);
    
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 5; i++)
    {
        DListInsertBefore(DListIteratorFirst(test_list_2), &test_arr[i]);
    }

    printf("test_list_2:\n");
	DListForEach(DListIteratorFirst(test_list_2), DListIteratorEnd(test_list_2), &PrintInt, (void *) 1);
	
	printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    from = DListIteratorFirst(test_list_2);
    to = DListIteratorPrev(DListIteratorPrev(DListIteratorEnd(test_list_2)));
    position = DListIteratorFirst(test_list);
    DListSplice(from, to, position);
    
    DListForEach(DListIteratorFirst(test_list), DListIteratorEnd(test_list), &PrintInt, (void *) 1);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    DListForEach(DListIteratorFirst(test_list_2), DListIteratorEnd(test_list_2), &PrintInt, (void *) 1);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("Count test_list", DListSize(test_list), 13);
    TEST("IsEmpty test_list", DListIsEmpty(test_list), 0);
    TEST("Count test_list_2", DListSize(test_list_2), 2);
    TEST("IsEmpty test_list_2", DListIsEmpty(test_list_2), 0);
    
	DListDestroy(test_list);
	DListDestroy(test_list_2);
}

void TestDListMultiFind(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 3, 7, 8, 3};
    int find = 3;
    int i = 0;
    dll_t *test_list = DListCreate();
    dll_t *test_list_2 = DListCreate();
    dll_iterator_t from;
    dll_iterator_t to;
    size_t counter = 0;


    for(i = 0; i < 10; i++)
    {
        DListInsertBefore(DListIteratorFirst(test_list), &test_arr[i]);
    }
   
    from = DListIteratorFirst(test_list);
    to = DListIteratorEnd(test_list);
    
	counter = DListMultiFind(from, to, &IsMatch, test_list_2, &find);
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    DListForEach(DListIteratorFirst(test_list_2), DListIteratorEnd(test_list_2), &PrintInt, (void *) 1);

    TEST("find test", counter, 3);

	DListDestroy(test_list);
	DListDestroy(test_list_2);
}
