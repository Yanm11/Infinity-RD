/*
yan meiri
15.05.2024
reviwed by amit
*/

#include <stdio.h> 
#include <stdlib.h> /* malloc free */
#include <stddef.h> /* size_t ssize_t offsetof */
#include <assert.h> /* assert */

#include "cbuffer.h"

struct cbuffer
{
    size_t write_offset;
    size_t read_offset;
    size_t capacity;
    char buff_data[1];
};
 
cbuffer_t *CBuffCreate(size_t capacityacity)
{
    cbuffer_t *cbuffer = NULL;
    
    assert(0 < capacityacity);
    
    cbuffer = (cbuffer_t*)malloc(offsetof(cbuffer_t, buff_data) + (capacityacity * sizeof(char)));
    
    cbuffer->write_offset = 0;
    cbuffer->read_offset = 0;
    cbuffer->capacity = capacityacity;
    
    return cbuffer;
}

void CBuffDestroy(cbuffer_t *buffer)
{
     assert(buffer);
     
     free(buffer);
}

size_t CBuffFreeSpace(cbuffer_t *buffer)
{
	size_t capacity = buffer->capacity;
	
    assert(buffer);
    
    /* when they are both equal */
    if (CBuffIsEmpty(buffer))
    {
        return capacity;
    }
    
    /* when read offset is smaller than write offset */
    else if ((buffer->read_offset % capacity) < (buffer->write_offset % capacity))
    {
        return (capacity - (buffer->write_offset % capacity) + (buffer->read_offset % capacity));
    }
    
    /* when read offset is bigger than write offset */
    return ((buffer->read_offset % capacity) - (buffer->write_offset % capacity));
}

size_t CBuffSize(const cbuffer_t *buffer)
{
    assert(buffer);
    
    return buffer->capacity;
}

int CBuffIsEmpty(cbuffer_t *buffer)
{
    assert(buffer);
    
    if (buffer->write_offset == buffer->read_offset)
    {
    	buffer->read_offset = buffer->read_offset % buffer->capacity;
    	buffer->write_offset = buffer->write_offset % buffer->capacity;
    	
    	return 1;
    }
    
    return 0;
}

ssize_t CBuffRead(cbuffer_t *buffer, void * dest, size_t count)
{
    char *new_dest = (char *)dest;
    ssize_t num_bytes_read = count;
    size_t capacity = buffer->capacity;
    
    assert(buffer);
    assert(dest);
    assert(0 < count);
    
    if (CBuffIsEmpty(buffer))
    {
        return 0;
    }
    
    /* making sure to not read more than capacity */
    if (count > capacity)
    {
        count = count % capacity + 1;
    }
    
    while ((0 < count) && (buffer->read_offset < buffer->write_offset))
    {
        *new_dest = buffer->buff_data[buffer->read_offset % capacity];
    
        ++buffer->read_offset;
        ++new_dest;
        --count;
    }
    
    return (num_bytes_read - count);
}

ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count)
{
    ssize_t num_bytes_wrote = count;
    char *new_src = (char *)src;
    size_t capacity = buffer->capacity;
    size_t diff_w_r = 0;
    
    assert(buffer);
    assert(src);
    assert(0 < count);
    
    while (0 < count)
    {
        buffer->buff_data[buffer->write_offset % capacity] = *new_src;
        
        ++buffer->write_offset;
        ++new_src;
        --count;
    }
    
    
    diff_w_r = buffer->write_offset - buffer->read_offset;
    
    /* updating the read offset only when write passes him i a full lap or more */
    if (diff_w_r > capacity)
    {
    	buffer->read_offset = (buffer->write_offset % capacity);
    }
    
    return (num_bytes_wrote - count);
}



























