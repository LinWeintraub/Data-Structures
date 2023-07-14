#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

#include <sys/types.h>
#include <stddef.h>

typedef struct circular_buffer circular_buffer_t;

circular_buffer_t *BufferCreate(size_t capacity); 

ssize_t BufferWrite(circular_buffer_t *buffer, size_t count, const void *src_buffer);

ssize_t BufferRead(void *dest_buffer, circular_buffer_t *buffer, size_t count);

size_t BufferSize(const circular_buffer_t *buffer);

int BufferIsEmpty(const circular_buffer_t *buffer);

size_t BufferFreeSpace(const circular_buffer_t *buffer);

void BufferDestroy(circular_buffer_t *buffer);

#endif /* __ILRD_OL133_CIRCULAR_BUFFER__*/
