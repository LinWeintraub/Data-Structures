/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          30/9/22                                         ~
 * Description   BIT ARRAY                                       *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */

#include "bit_array.h"

int main(void)
{
	bit_array_t bit_arr = 121;
	char str[65] = {0};
	
	printf("%ld \n", CountOnBitArray(bit_arr));
	printf("%s \n", BitArrayToString(bit_arr, str));
	
	/*printf("%s", BitArrayToString(bit_arr, str));*/

	
	
	/*printf("%d \n", GetValBitArray(bit_arr, 3));*/
	return 0;
}

