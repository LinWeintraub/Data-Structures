/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Single Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc, free */

#include "sll_exercises.h"

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define CYAN "\033[1;36m"
#define WHITE "\033[0m"

#define TEST(name, actual, expected) \
    printf("%s: %s\n" , name, actual == expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)
#define TESTNOT(name, actual, expected) \
    printf("%s: %s\n" , name, actual != expected ? GREEN"PASS"WHITE : RED"FAIL"WHITE)


int Add_Front(node_t **head, void *data);
void CreateLoop(node_t *head, int position);
void PrintList(node_t *list);
void FreeList(node_t *list);
void TestFlipAndLoop(void);
void TestFindIntersection(void);

int main (void)
{
	TestFlipAndLoop();
	
	TestFindIntersection();
	
	return 0;
}



int Add_Front(node_t **head, void *data) 
{
	node_t *new_node = malloc(sizeof(node_t));
	if (NULL == new_node)
	{
		return 1;
	}
	
	assert(head);
	assert(data);
	
	new_node->data = data;
	new_node->next = *head;
	*head = new_node;
		
	return 0;
}

void PrintList(node_t *list)
{
	node_t *temp = list;
	for (temp = list; NULL != temp; temp = temp->next)
	{
		printf("%d-->", *(int *) temp->data);
	}
}

void CreateLoop(node_t *head, int position) 
{
    node_t *runner = head;
    node_t *temp = head;
    int current = 0;
    
    while(temp->next != NULL) 
    {
        if(current != position) 
        {
            ++current;
            runner = runner->next;
        } 
        temp = temp->next;
    }
    
    temp->next = runner;
}

void FreeList(node_t *list)
{
	node_t *temp;
    while (NULL != list->next)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
}

void TestFlipAndLoop(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    int x = 0;

    node_t list;
    node_t *test_list = &list;
	node_t *test_list_flip = &list;
	
    test_list->data = &x;
	test_list->next = NULL;
	  
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        Add_Front(&test_list, &test_arr[i]);
    }

    PrintList(test_list);

    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");

	test_list_flip = Flip(test_list);
	PrintList(test_list_flip);

    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");

    TEST("HasLoop test - no loop", HasLoop(test_list_flip), 0);
    CreateLoop(test_list, 3);
    TEST("HasLoop test - with loop", HasLoop(test_list), 1);
    /*FreeList(test_list);*/
}

void TestFindIntersection(void)
{
	int test_arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    int x = 0;
    node_t *y;
    
    node_t list;
    node_t list_2;
    node_t list_3;
    
    node_t *test_list = &list;
    node_t *test_list_2 = &list_2;
    node_t *test_list_3 = &list_3;
	
    test_list->data = &x;
	test_list->next = NULL;
	    
    printf("~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    for(i = 0; i < 10; ++i)
    {
        Add_Front(&test_list, &test_arr[i]);
    }

    PrintList(test_list);
    
    printf("\n~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#~#\n");
    test_list_2->data = &x;
	test_list_2->next = test_list->next->next;
	
	y = FindIntersection(test_list, test_list_2);
    TEST("FindIntersection test - with intersection", *(int *)y->data, *(int *)test_list->next->next->data);
    
    y = FindIntersection(test_list, test_list);
    TEST("FindIntersection test - same list", y, NULL);
    
    test_list_3->data = &x;
	test_list_3->next = NULL;
    Add_Front(&test_list_3, &x);

	
    y = FindIntersection(test_list, test_list_3);
    TEST("FindIntersection test - no intersection", y, NULL);
}
