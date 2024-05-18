/*
yan meiri
15.05.2024
reviwed by _______
*/

#include <stdio.h> 
#include <stdlib.h> /* malloc free */
#include <stddef.h> /* size_t ssize_t offsetof */
#include <assert.h> /* assert */

#include "cbuffer.h"

struct cbuffer
{
    size_t w_ofst;
    size_t r_ofst;
    size_t cap;
    char buff_data[1];
};
 
cbuffer_t *CBuffCreate(size_t capacity)
{
    cbuffer_t *cbuffer = NULL;
    
    assert(0 < capacity);
    
    cbuffer = (cbuffer_t*)malloc(offsetof(cbuffer_t, buff_data) + (capacity * sizeof(char)));
    
    cbuffer->w_ofst = 0;
    cbuffer->r_ofst = 0;
    cbuffer->cap = capacity;
    
    return cbuffer;
}

void CBuffDestroy(cbuffer_t *buffer)
{
     assert(NULL != buffer);
     
     free(buffer);
}

size_t CBuffFreeSpace(const cbuffer_t *buffer)
{
	size_t cap = buffer->cap;
	
    assert(NULL != buffer);
    
    /* when they are both equal */
    if (CBuffIsEmpty(buffer))
    {
        return cap;
    }
    
    /* when read offset is smaller than write offset */
    else if ((buffer->r_ofst % cap) < (buffer->w_ofst % cap))
    {
        return (cap - (buffer->w_ofst % cap) + (buffer->r_ofst % cap));
    }
    
    /* when read offset is bigger than write offset */
    return ((buffer->r_ofst % cap) - (buffer->w_ofst % cap));
}

size_t CBuffSize(const cbuffer_t *buffer)
{
    assert(NULL != buffer);
    
    return buffer->cap;
}

int CBuffIsEmpty(const cbuffer_t *buffer)
{
    assert(NULL != buffer);
    
    return (buffer->w_ofst == buffer->r_ofst);
}

ssize_t CBuffRead(cbuffer_t *buffer, void * dest, size_t count)
{
    char *new_dest = (char *)dest;
    ssize_t num_bytes_read = count;
    size_t cap = buffer->cap;
    
    assert(NULL != buffer);
    assert(NULL != dest);
    assert(0 < count);
    
    if (CBuffIsEmpty(buffer))
    {
        return 0;
    }
    
    /* making sure to not read more than cap */
    if (count > cap)
    {
        count = count % cap + 1;
    }
    
    while ((0 < count) && (buffer->r_ofst < buffer->w_ofst))
    {
        *new_dest = buffer->buff_data[buffer->r_ofst % cap];
    
        ++buffer->r_ofst;
        ++new_dest;
        --count;
    }
    
    return (num_bytes_read - count);
}

ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count)
{
    ssize_t num_bytes_wrote = count;
    char *new_src = (char *)src;
    size_t cap = buffer->cap;
    size_t diff_w_r = 0;
    
    assert(NULL != buffer);
    assert(NULL != src);
    assert(0 < count);
    
    while (0 < count)
    {
        buffer->buff_data[buffer->w_ofst % cap] = *new_src;
        
        ++buffer->w_ofst;
        ++new_src;
        --count;
    }
    
    
    diff_w_r = buffer->w_ofst - buffer->r_ofst;
    
    /* updating the read offset only when write passes him i a full lap or more */
    if (diff_w_r > cap)
    {
    	buffer->r_ofst += ((buffer->w_ofst % cap) - buffer->r_ofst);
    }
    
    return (num_bytes_wrote - count);
}



























