/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          2/10/22                                         ~                                
 * Description   STACK                                           *                              
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */

#include "stack.h"

int main (void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;

	int *peek = 0;
	
	stack_t *stack = StackCreate(5, 4);
	
	StackPush(stack, &num1);
	StackPush(stack, &num2);
	StackPush(stack, &num3);
	StackPush(stack, &num4);
	StackPush(stack, &num5);
	
	peek = StackPeek(stack);	
	printf("peek: %d\n", *peek);
	
	StackPop(stack);	
	peek = StackPeek(stack);
	printf("peek after pop: %d\n", *peek);
	
	printf("isEmpty? %d\n", StackIsEmpty(stack));
	printf("capacity %ld\n", StackCapacity(stack));
	printf("size %ld\n", StackSize(stack));

	StackPop(stack);	
	StackPop(stack);	
	StackPop(stack);	
	StackPop(stack);	
	
	peek = StackPeek(stack);
	printf("peek after pop all: %d\n", *peek);
	
	printf("isEmpty? %d\n", StackIsEmpty(stack));
	printf("capacity %ld\n", StackCapacity(stack));
	printf("size %ld\n", StackSize(stack));
	
	return 0;
}
