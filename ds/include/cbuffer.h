#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <sys/types.h> /*size_t ssize_t*/

typedef struct cbuffer cbuffer_t;

/*
CBuffCreate
Desc: Creates a new circular buffer
Recieves: The desired capacity
Returns: A pointer to the new circular buffer
Time Complexity: O(1)
Space Complexity: O(1)
*/
cbuffer_t *CBuffCreate(size_t capacity);

/*
CBuffDestroy
Desc: Destroys a circular buffer
Recieves: A pointer to a circular buffer
Returns: nothing
Time Complexity: O(1)
Space Complexity: O(1)
*/
void CBuffDestroy(cbuffer_t *buffer);

/*
CBuffFreeSpace
Desc: gives the number of free bytes to write
Recieves: A pointer to a constant circular buffer
Returns: The number of free bytes to write
Time Complexity:O(1)
Space Complexity:O(1)
*/
size_t CBuffFreeSpace(cbuffer_t *buffer);

/*
CBuffSize
Desc: gives the capacity of the buffer
Recieves: A pointer to a constant circular buffer
Returns: the capacity of the buffer
Time Complexity:O(1)
Space Complexity:O(1)
*/
size_t CBuffSize(const cbuffer_t *buffer);

/*
CBuffRead
Desc: read from the buffer to a certain destenation
Recieves: pointer to a buffer, pointer to the dest and the number of byte to read.
Returns: -1 if failed, 0 if nothing was read, and then the actual number that we read.
Time Complexity: O(n)
Space Complexity: O(1)
*/
ssize_t CBuffRead(cbuffer_t *buffer, void *dest, size_t count);

/*
CBuffWrite
Desc: writes data from source to the buffer
Recieves: A pointer to a circular buffer, a constant pointer to the source, and the number of bytes to read.
Returns: the number of bytes written
Time Complexity: O(n)
Space Complexity: O(n)
*/
ssize_t CBuffWrite(cbuffer_t *buffer, const void *src, size_t count);

/*
CBuffIsEmpty
Desc: Checks if buffer is empty or not
Recieves: const pointer to buffer
Returns: 1 if empty, 0 if not
Time Complexity: O(1)
Space Complexity: O(1)
*/
int CBuffIsEmpty(cbuffer_t *buffer);


#endif /*__CIRCULAR_BUFFER_H__*/
