/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          24/10/22                                        ~
 * Description   Priority Queue                                  *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h>

#include "priority_queue.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

void TestPQCreate(void);
void TestPQEnqueueDequeuePeekIsEmptySize(void);
void TestPQEraseClear(void);

int CmpFunction(void *param_a, void *param_b);
int IsMatch(void *param_a, void *param_b);

int main(void)
{
	TestPQCreate();	
	TestPQEnqueueDequeuePeekIsEmptySize();
	TestPQEraseClear();
	
	return 0;
}

void TestPQCreate(void)
{
    priority_queue_t *test = PQCreate(&CmpFunction);
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("PQCreate test1: ",test , NULL);
    
    PQDestroy(test);
}    

void TestPQEnqueueDequeuePeekIsEmptySize(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    priority_queue_t *test = PQCreate(&CmpFunction);
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        PQEnqueue(test, &test_arr[i]);
    }     
     
    TEST("size test1", PQSize(test), 10);
    TEST("IsEmpty test1", PQIsEmpty(test), 0);

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        printf("PQDequeue + PQueuePeek test %d", i);
        TEST("", PQPeek(test), &test_arr[i]);
        PQDequeue(test);
    }

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TEST("size test2 after deletion", PQSize(test), 0);
    TEST("IsEmpty test2 after deletion", PQIsEmpty(test), 1);
    
    PQDestroy(test);
}

void TestPQEraseClear(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    priority_queue_t *test = PQCreate(&CmpFunction);
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        PQEnqueue(test, &test_arr[i]);
    } 
    
    PQErase(test, &IsMatch, &test_arr[3]);
    TEST("size test after erase", PQSize(test), 9);    
    
    PQErase(test, &IsMatch, &test_arr[3]);
    TEST("size test after erase fail", PQSize(test), 9);  
    
    PQClear(test);
    TEST("size test after clear", PQSize(test), 0);    
    PQDestroy(test);
}

int CmpFunction(void *param_a, void *param_b)
{
	return (*(int *)param_a - *(int *)param_b);
}

int IsMatch(void *param_a, void *param_b)
{
	if (*(int *)param_a != *(int *)param_b)
	{
		return 0;
	}
	
	return 1;
}
