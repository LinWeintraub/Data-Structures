/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       1.0.0                                           *
 ~ Date          1/12/22                                         ~
 * Description   Heap                                            *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */

#include "heap.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)

static void TestHeapCreate(void);
static void TestHeapSize(void);
static void TestHeapIsEmpty(void);
static void TestHeapPush(void);
static void TestHeapPop(void);
static void TestHeapRemove(void);

static int CmpFunc(const void *data1, const void *data2);
static int IsMatch(const void *param, const void *value);
void PrintHeap(heap_t *heap);

int main(void)
{
    TestHeapCreate();
    TestHeapPush();
    TestHeapSize();
    TestHeapIsEmpty();
    TestHeapRemove();
    TestHeapPop();

    return 0;
}

static void TestHeapCreate(void)
{
	heap_t *heap = HeapCreate(CmpFunc);

  printf("----------Create & Destroy test:----------\n");
	TEST("TestHeapCreate", (NULL != heap), 1);

  HeapDestroy(heap);
}

static void TestHeapSize(void)
{
	heap_t *heap = HeapCreate(CmpFunc);
  int data = 5;

  printf("----------Size test:----------\n");
  TEST("TestHeapSize1", HeapSize(heap), 0);
  HeapPush(heap, &data);
  TEST("TestHeapSize2", HeapSize(heap), 1);

  HeapDestroy(heap);
}

static void TestHeapIsEmpty(void)
{
	heap_t *heap = HeapCreate(CmpFunc);
  int data = 5;

  printf("----------IsEmpty test:----------\n");
  TEST("TestHeapIsEmpty1", HeapIsEmpty(heap), 1);
  HeapPush(heap, &data);
  TEST("TestHeapIsEmpty2", HeapIsEmpty(heap), 0);

  HeapDestroy(heap);
}

static void TestHeapPush(void)
{
	heap_t *heap = HeapCreate(CmpFunc);

  int data1 = 5;
  int data2 = 9;
  int data3 = -3;
  int data4 = 13;
  int data5 = -40;

  printf("----------Push test:----------\n");
  HeapPush(heap, &data1);
  HeapPush(heap, &data2);
  HeapPush(heap, &data3);
  HeapPush(heap, &data4);
  HeapPush(heap, &data5);

  TEST("TestHeapSizeInsert", HeapSize(heap), 5);

  PrintHeap(heap);

  HeapDestroy(heap);
}

static void TestHeapPop(void)
{
	heap_t *heap = HeapCreate(CmpFunc);
  int *item = NULL;

  int data1 = 5;
  int data2 = 9;
  int data3 = -3;
  int data4 = 13;
  int data5 = -40;

  printf("----------Pop test:----------\n");
  HeapPush(heap, &data1);
  HeapPush(heap, &data2);
  HeapPush(heap, &data3);
  HeapPush(heap, &data4);
  HeapPush(heap, &data5);

  PrintHeap(heap);

  item = HeapPop(heap);

  PrintHeap(heap);

  TEST("TestHeapPopSize", HeapSize(heap), 4);
  TEST("TestHeapPop", *(int *)item, data4);

  item = HeapPop(heap);

  PrintHeap(heap);

  TEST("TestHeapPopSize", HeapSize(heap), 3);
  TEST("TestHeapPop", *(int *)item, data2);

  HeapDestroy(heap);
}

static void TestHeapRemove(void)
{
	heap_t *heap = HeapCreate(CmpFunc);

  int data1 = 5;
  int data2 = 9;
  int data3 = -103;
  int data4 = 13;
  int data5 = -40;

  int *item = NULL;

  printf("----------Remove test:----------\n");
  HeapPush(heap, &data1);
  HeapPush(heap, &data2);
  HeapPush(heap, &data3);
  HeapPush(heap, &data4);
  HeapPush(heap, &data5);

  PrintHeap(heap);

  item = HeapRemove(heap, IsMatch, &data3);
  TEST("TestHeapRemove", *(int *)item, data3);

  PrintHeap(heap);

  item = HeapRemove(heap, IsMatch, &data4);
  TEST("TestHeapRemove", *(int *)item, data4);

  PrintHeap(heap);

  item = HeapRemove(heap, IsMatch, &data1);
  TEST("TestHeapRemove", *(int *)item, data1);

  PrintHeap(heap);

  HeapDestroy(heap);
}

static int CmpFunc(const void *data_1, const void *data_2)
{
  return (*(int *)data_1 - *(int *)data_2);
}

static int IsMatch(const void *param_a, const void *param_b)
{
	if (*(int *)param_a == *(int *)param_b)
	{
		return 1;
	}
	
	return 0;
}
