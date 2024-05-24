/********************************** 
   Code by: Yan Meiri	
   Project: Circular buffer data structure
   Date: 15/05/24
   Review by: Amit
   Review Date: 18/05/24
   Approved by: Amit
   Approval Date: 18/05/24
**********************************/

#include <stdlib.h> /* malloc free */
#include <stddef.h> /* offsetof */
#include <assert.h> /* assert */

#include "cbuffer.h"

struct cbuffer
{
    size_t write_offset;
    size_t read_offset;
    size_t capacity;
    char buff_data[1];
};
 
cbuffer_t *CBuffCreate(size_t capacity)
{
    cbuffer_t *cbuffer = NULL;
    
    assert(0 < capacity);
    
    cbuffer = (cbuffer_t*)malloc(offsetof(cbuffer_t, buff_data) +
    							 (capacity * sizeof(char)));
    
    cbuffer->write_offset = 0;
    cbuffer->read_offset = 0;
    cbuffer->capacity = capacity;
    
    return cbuffer;
}

void CBuffDestroy(cbuffer_t *buffer)
{
     assert(buffer);
     
     free(buffer);
}

size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	size_t capacity = buffer->capacity;
	
    assert(buffer);
    
    /* when they are both equal */
    if (CBuffIsEmpty(buffer))
    {
        return capacity;
    }
    
    /* when read offset is smaller than write offset */
    else if ((buffer->read_offset % capacity)<(buffer->write_offset % capacity))
    {
        return (capacity - (buffer->write_offset % capacity) +
        				   (buffer->read_offset % capacity));
    }
    
    /* when read offset is bigger than write offset */
    return ((buffer->read_offset % capacity)-(buffer->write_offset % capacity));
}

size_t CBuffSize(const cbuffer_t *buffer)
{
    assert(buffer);
    
    return buffer->capacity;
}

int CBuffIsEmpty(const cbuffer_t *buffer)
{
    assert(buffer);
    
    return (buffer->write_offset == buffer->read_offset);
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
    	/* updating the offsets to reduce their size */
    	buffer->read_offset = buffer->read_offset % buffer->capacity;
    	buffer->write_offset = buffer->write_offset % buffer->capacity;
    	
        return 0;
    }
    
	if(count > (capacity - CBuffFreeSpace(buffer)))
	{
		count = (capacity - CBuffFreeSpace(buffer));
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
    size_t diff_write_read = 0;
    
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
    
    diff_write_read = buffer->write_offset - buffer->read_offset;
    
    /* updating the read offset only when write passes him by a lap or more */
    if (diff_write_read > capacity)
    {
    	buffer->read_offset = (buffer->write_offset % capacity);
    }
    
    return (num_bytes_wrote - count);
}



























