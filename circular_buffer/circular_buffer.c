/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *
 ~ Author        Lin Weintraub                                   ~
 * Version       0.0.1                                           *
 ~ Date          3/10/22                                         ~
 * Description   Circular Buffer                                 *
 * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */
 
#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "circular_buffer.h"
 
struct circular_buffer
{
	size_t magic_number;
	size_t capacity;
	size_t front;
	size_t size;
	char buffer_array[1];
};

circular_buffer_t *BufferCreate(size_t capacity)
{
	circular_buffer_t *circular_buffer =malloc(sizeof(circular_buffer_t) + (sizeof(char) * capacity));

	if (NULL == circular_buffer)
	{
		return NULL;
	}
	
	circular_buffer->magic_number = 0xDEADBEEF;
	circular_buffer->capacity = capacity;
	circular_buffer->front = 0;
	circular_buffer->size = 0;

	return circular_buffer;
}

ssize_t BufferWrite(circular_buffer_t *buffer, size_t count, const void *src_buffer)
{
	ssize_t byte_write = 0;
	size_t rear = buffer->front + buffer->size % buffer->capacity;
	
	assert(buffer);
	assert(src_buffer);
	
	if (buffer->magic_number != 0xDEADBEEF)
	{
		return -1;
	}
	
	while (count > 0 && (BufferFreeSpace(buffer) > 0))
	{
		buffer->buffer_array[rear] = *(char *)src_buffer;
		++buffer->size;
		--count;
		src_buffer = (char *)src_buffer + 1;
		++byte_write;
	}
	
	return byte_write;
}

ssize_t BufferRead(void *dest_buffer, circular_buffer_t *buffer, size_t count)
{
	ssize_t byte_write = 0;
	buffer->front = buffer->front % buffer->capacity;
	
	assert(buffer);
	assert(dest_buffer);
	
	if (buffer->magic_number != 0xDEADBEEF)
	{
		return -1;
	}
	
	while (count > 0 && (BufferIsEmpty(buffer) == 0))
	{
		*(char *)dest_buffer = buffer->buffer_array[buffer->front];
		++buffer->front;
		--count;
		--buffer->size;
		dest_buffer = (char *)dest_buffer + 1;
		++byte_write;
	}
	
	return byte_write;
}

size_t BufferSize(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->size);
}

int BufferIsEmpty(const circular_buffer_t *buffer)
{
	assert(buffer);

	return (0 == BufferSize(buffer));
}

size_t BufferFreeSpace(const circular_buffer_t *buffer)
{
	assert(buffer);
	
	return (buffer->capacity - BufferSize(buffer));
}

void BufferDestroy(circular_buffer_t *buffer)
{
	assert(buffer);

	free(buffer);
}

