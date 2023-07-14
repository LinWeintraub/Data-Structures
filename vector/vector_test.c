/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          3/10/22                                         ~
 * Description   Dynamic Vector                                  *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */

#include "vector.h"

int main (void)
{
	int num1 = 1;
	int num2 = 2;
	int num3 = 3;
	int num4 = 4;
	int num5 = 5;
	int num6 = 6;
	
	int *ptr_index = 0;
	
	vector_t *vector = VectorCreate(5, 4);
	
	VectorAppend(vector, &num1);
	VectorAppend(vector, &num2);
	VectorAppend(vector, &num3);
	VectorAppend(vector, &num4);
	VectorAppend(vector, &num5);
	
	printf("size %ld\n", VectorSize(vector));
	printf("capacity (5) %ld\n", VectorCapacity(vector));
	printf("index 3 (4) %d\n", *(ptr_index = VectorGetAccessToElement(vector, 3)));
	
	VectorAppend(vector, &num6);
	
	printf("size (6) %ld\n", VectorSize(vector));
	printf("capacity (10) %ld\n", VectorCapacity(vector));
	
	VectorRemoveLast(vector);	

	printf("size (5) %ld\n", VectorSize(vector));
	printf("isEmpty? (0) %d\n", VectorIsEmpty(vector));
	printf("capacity (10) %ld\n", VectorCapacity(vector));

	VectorReserve(vector, 4);
	
	printf("size (5) %ld\n", VectorSize(vector));
	printf("capacity (14) %ld\n", VectorCapacity(vector));
	
	VectorShrink(vector);
	printf("capacity (10) %ld\n", VectorCapacity(vector));	
	printf("isEmpty? %d\n", VectorIsEmpty(vector));
	printf("size (5) %ld\n", VectorSize(vector));
	VectorDestroy(vector);
	

	return 0;
}
