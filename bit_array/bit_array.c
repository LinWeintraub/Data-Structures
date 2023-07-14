/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          30/9/22                                         ~
 * Description   BIT ARRAY                                       *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <limits.h> /* CHAR_BIT */

#include "bit_array.h"
	
bit_array_t SetAllBitArray(void)
{
	return (0 - 1);
}

bit_array_t ResetAllBitArray(void)
{
	return 0;
}

bit_array_t SetOnBitArray(bit_array_t bit_arr, size_t n_bit)
{	
	size_t bit = 1;
	bit_arr |= bit << n_bit;

	
	return bit_arr; 
}

bit_array_t SetOffBitArray(bit_array_t bit_arr, size_t n_bit)
{
	size_t bit = 1;
	bit_arr &= ~(bit << n_bit);
	
	return bit_arr; 
}

bit_array_t SetBitBitArray(bit_array_t bit_arr, size_t n_bit, unsigned int value)
{
	return value ? SetOnBitArray(bit_arr, n_bit) : SetOffBitArray(bit_arr, n_bit);
}

unsigned int GetValBitArray(bit_array_t bit_arr, size_t n_bit)
{
	size_t bit = 1;
	return ((bit_arr >> n_bit) & bit);
}

bit_array_t FlipBitArray(bit_array_t bit_arr, size_t n_bit)
{
	size_t bit = 1;
	bit_arr = (bit_arr ^ (bit << n_bit));
	return bit_arr;
}

bit_array_t MirrorBitArray(bit_array_t bit_arr)
{
    size_t rev = 0;
    size_t size_t_bits = sizeof(bit_arr) * CHAR_BIT;
    size_t i = 0;
    size_t bit = 1;

    while (size_t_bits > i) 
    {
        rev = rev << bit;
        if ((bit_arr & bit) == bit)
        {
            rev = rev ^ bit;      
        }
        i++; 
        bit_arr = bit_arr >> bit;
        
    }
    return rev;
}

bit_array_t RotateRightBitArray(bit_array_t bit_arr, unsigned int n)
{
	return (bit_arr >> n)|(bit_arr << ((sizeof(bit_arr) * CHAR_BIT) - n));
}
/*
1100
n=2
0011
0000
0011
*/
bit_array_t RotateLeftBitArray(bit_array_t bit_arr, unsigned int n)
{
	return (bit_arr << n)|(bit_arr >> ((sizeof(bit_arr) * CHAR_BIT)  - n));
}
/*
1010
n=3
0000
0101
0101
*/
size_t CountOnBitArray(bit_array_t bit_arr)
{
	size_t counter = 0;
	size_t bit = 1;
	
    while (bit_arr) 
    {
        bit_arr &= (bit_arr - bit);
        counter++;
    }
    
    return counter;
}

size_t CountOffBitArray(bit_array_t bit_arr)
{
	return ((sizeof(bit_arr) * CHAR_BIT)  - CountOnBitArray(bit_arr));
}

char *BitArrayToString(bit_array_t bit_arr, char *str)
{
	size_t i = 0;
		
	char *ptr_str = str;
	for (i = 0; i < (sizeof(bit_arr) * CHAR_BIT); ++i)
	{	
		*ptr_str = (GetValBitArray(bit_arr, i) + '0');
		++ptr_str;
	}
	
	*ptr_str = '\0';
	return str;
}

