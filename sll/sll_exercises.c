/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          9/10/22                                         ~
 * Description   Single Linked List                              *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#include <stddef.h> /* NULL */

#include "sll_exercises.h"
 
node_t *Flip(node_t *head)
{
  node_t *current = head;
  node_t *prev = NULL;
  node_t *temp = NULL;	
  
  while(NULL != current)
  {
	temp = current->next; 
	current->next = prev; 
	prev = current; 
	current = temp;
  }
  head = prev;

  return head;
}

int HasLoop(const node_t *head)
{
	const node_t *inner = head;
	const node_t *outer = head->next;
    int status = 0;

	while (NULL != outer && NULL != inner) 
	{
		if (outer == inner)
		{
			status = 1;
			return status;
		}
		
		outer = outer->next->next;
		inner = inner->next;
	}
	
	return status;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
    node_t *runner_1 = head_1;
    node_t *runner_2 = head_2;
    int null_counter = 0;
    
   	if (head_1 == head_2)
   	{
   		return NULL;
   	}
   	
    if (NULL == runner_1 || NULL == runner_2)
    {
        return NULL;
    }
	
    while (runner_1 != runner_2) 
    {
        if (NULL == runner_1->next)
        {
            runner_1 = head_2;
            ++null_counter;
        }
        
        if (NULL == runner_2->next)
        {
            runner_2 = head_1;
            ++null_counter;
        }
        
        if (2 < null_counter)
        {
        	return NULL;
        }

        runner_1 = runner_1->next;
        runner_2 = runner_2->next;
    }
    
    return runner_1;
}


