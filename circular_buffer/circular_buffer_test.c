/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          3/10/22                                         ~
 * Description   Circular Buffer                                 *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stdio.h>
#include <assert.h>

#include "circular_buffer.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
    
void TestBufferCreate(void);
void TestBufferWriteAndRead(void);


int main(void)
{
	TestBufferCreate();
	TestBufferWriteAndRead();
	return 0;
}

void TestBufferCreate(void)
{
    circular_buffer_t *test = BufferCreate(10);
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    TESTNOT("BufferCreate test1: ",test , NULL);
    BufferDestroy(test);
}

void TestBufferWriteAndRead(void)
{
    circular_buffer_t *test = BufferCreate(10);
    int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int dest_arr[10] = {0};
	ssize_t byte_read = 0;
    ssize_t byte_write = 0;

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    byte_write = BufferWrite(test, 10, test_arr);
    
    TEST("BufferWrite test1", byte_write, 10);
    TEST("size test1", BufferSize(test), 10);
    TEST("IsEmpty test1", BufferIsEmpty(test), 0);
    TEST("BufferFreeSpace test1", BufferFreeSpace(test), 0);
    

    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    byte_read = BufferRead(dest_arr, test, 4);
    
    TEST("BufferRead test1", byte_read, 4);
    TEST("size test2", BufferSize(test), 6);
    TEST("IsEmpty test2", BufferIsEmpty(test), 0);
    TEST("BufferFreeSpace test2", BufferFreeSpace(test), 4);
    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    
    byte_write = BufferWrite(test, 2, test_arr);
    
    TEST("BufferWrite test1", byte_write, 2);
    TEST("size test1", BufferSize(test), 8);
    TEST("IsEmpty test1", BufferIsEmpty(test), 0);
    TEST("BufferFreeSpace test1", BufferFreeSpace(test), 2);


    BufferDestroy(test);
}


