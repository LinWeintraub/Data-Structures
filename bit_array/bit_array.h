#ifndef __BIT_ARRAY__
#define __BIT_ARRAY__

#include <stddef.h>

typedef size_t bit_array_t;

	
bit_array_t SetAllBitArray(void);

bit_array_t ResetAllBitArray(void);

bit_array_t SetOnBitArray(bit_array_t bit_arr, size_t n_bit);

bit_array_t SetOffBitArray(bit_array_t bit_arr, size_t n_bit);

bit_array_t SetBitBitArray(bit_array_t bit_arr, size_t n_bit, unsigned int value);

unsigned int GetValBitArray(bit_array_t bit_arr, size_t n_bit);

bit_array_t FlipBitArray(bit_array_t bit_arr, size_t n_bit);

bit_array_t MirrorBitArray(bit_array_t bit_arr);

bit_array_t RotateRightBitArray(bit_array_t bit_arr, unsigned int n);

bit_array_t RotateLeftBitArray(bit_array_t bit_arr, unsigned int n);

size_t CountOnBitArray(bit_array_t bit_arr);

size_t CountOffBitArray(bit_array_t bit_arr);

char *BitArrayToString(bit_array_t bit_arr, char *str);

#endif /* __BIT_ARRAY__ */


