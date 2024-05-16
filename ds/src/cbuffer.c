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
    assert(NULL != buffer);
    if (CBuffIsEmpty(buffer))
    {
        return buffer->cap;
    }
    else if (buffer->r_ofst < buffer->w_ofst)
    {
        return (buffer->cap - buffer->w_ofst + buffer->r_ofst - 1);
    }
    return buffer->w_ofst - buffer->r_ofst;
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
    
    assert(NULL != buffer);
    assert(NULL != dest);
    assert(0 < count);
    
    if (CBuffIsEmpty(buffer))
    {
        return 0;
    }
    
    if (count > buffer->cap)
    {
        count %= buffer->cap;
    }
    
    while ((0 < count) && (buffer->r_ofst != buffer->w_ofst))
    {
        *new_dest = buffer->buff_data[buffer->r_ofst];
    
        buffer->r_ofst = (buffer->r_ofst + 1) % buffer->cap;
        ++new_dest;
        --count;
    }
    
    return (num_bytes_read - count);
}

ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count)
{
    int flag = 0;
    ssize_t num_bytes_wrote = count;
    size_t end_index = count + buffer->w_ofst;
    char *new_src = (char *)src;
       
    assert(NULL != buffer);
    assert(NULL != src);
    assert(0 < count);
    
    if (buffer->w_ofst < buffer->r_ofst && end_index > buffer->r_ofst)
    {
        flag = 1;
    }
    
    while (0 < count)
    {
        buffer->buff_data[buffer->w_ofst] = *new_src;
        
        buffer->w_ofst = (buffer->w_ofst + 1) % buffer->cap;
        ++new_src;
        --count;
    }
    
    if (flag)
    {
        buffer->r_ofst = buffer->w_ofst + 1;
    }
    
    return (num_bytes_wrote - count);
}



























