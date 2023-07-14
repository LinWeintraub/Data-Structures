/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          30/9/22                                         ~
 * Description   BIT ARRAY                                       *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdio.h> /* printf */
#include <limits.h> /* CHAR_BIT */
#include <stddef.h> /* SIZE_T */

static unsigned char BitsSetTable[256] = {0};
static unsigned char MirrorBitsTable[256] = {0};

/*----------COUNT_ON----------*/
size_t CountOnBitArray(unsigned char bit_arr)
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

void InitLUTBitsOn(void)
{
	size_t i = 0;
	for (i = 0; i < 256; ++i)
	{
		BitsSetTable[i] = CountOnBitArray(i);
	}
}

size_t CountOnBitLUT(size_t bit_arr)
{
	size_t total_bits_on = 0;
	
	total_bits_on = BitsSetTable[bit_arr & 0xff] + BitsSetTable[(bit_arr >> 8) & 0xff] + BitsSetTable[(bit_arr >> 16) & 0xff] + BitsSetTable[(bit_arr >> 24) & 0xff] +
	BitsSetTable[(bit_arr >> 32) & 0xff] + BitsSetTable[(bit_arr >> 40) & 0xff] + BitsSetTable[(bit_arr >> 48) & 0xff] +  BitsSetTable[(bit_arr >> 56)]; 
    
    return total_bits_on;
}

/*----------MIRROR----------*/
unsigned int MirrorBitArray(unsigned char bit_arr)
{
	unsigned int rev = bit_arr;
	int end = sizeof(bit_arr) * CHAR_BIT - 1;

	for (bit_arr >>= 1; bit_arr; bit_arr >>= 1)
	{   
	  rev <<= 1;
	  rev |= bit_arr & 1;
	  end--;
	}
	rev <<= end; /* shift when bit_arr's highest bits are zero */

    return rev;
}

void InitLUTMirror(void)
{
	unsigned int i = 0;
	for (i = 0; i < 256; ++i)
	{
		MirrorBitsTable[i] = MirrorBitArray(i);
	}
}

unsigned int MirrorBitsLUT(unsigned int bit_array)
{
    unsigned int mirror_bits = 0; 
    
    mirror_bits = (MirrorBitsTable[bit_array & 0xff] << 24) | (MirrorBitsTable[(bit_array >> 8) & 0xff] << 16) | (MirrorBitsTable[(bit_array >> 16) & 0xff] << 8) |
    (MirrorBitsTable[(bit_array >> 24) & 0xff]);
        
    return mirror_bits;
}

int main(void)
{	
	size_t bit_arr = 121;
	unsigned int bit_array = 121;
	
	InitLUTBitsOn();
	InitLUTMirror();
	


	printf("%ld \n", CountOnBitLUT(bit_arr));
	printf("%d \n", MirrorBitsLUT(bit_array));

	return 0;
}
