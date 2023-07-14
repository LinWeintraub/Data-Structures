/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Queue                                           *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h>
#include <assert.h>

#include "queue.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

void TestQueueCreate(void);
void TestEnqueueDequeueAndPeek(void);
void TestQueueAppend(void);

int PrintInt(void *param_a, void *param_b);
int SListForEach(iterator_t from, iterator_t to, action_t action_function_ptr, void *param);

int main (void)
{
    TestQueueCreate();
	TestEnqueueDequeueAndPeek();
	TestQueueAppend();
	
	return 0;
}

void TestQueueCreate(void)
{
    queue_t *test = QueueCreate();
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("QueueCreate test1: ",test , NULL);
    QueueDestroy(test);
}

void TestEnqueueDequeueAndPeek(void)
{
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    queue_t *test = QueueCreate();
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        Enqueue(test, &test_arr[i]);
    }     
     
    TEST("size test1",QueueSize(test), 10);
    TEST("IsEmpty test1",QueueIsEmpty(test), 0);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        printf("Dequeue + QueuePeek test %d", i);
        TEST("",QueuePeek(test), &test_arr[i]);
        Dequeue(test);
    }

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("size test2 after deletion",QueueSize(test), 0);
    TEST("IsEmpty test2 after deletion",QueueIsEmpty(test), 1);
    
    QueueDestroy(test);
}

void TestQueueAppend(void)
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
	(void)param_b;
    printf("%d-->", *(int *)param_a);
    return 0;
}

