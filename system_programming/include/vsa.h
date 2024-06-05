#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h> /* size_t */

typedef struct vsa vsa_t;

/*
VSAInit
description: Initialize the vsa.
input: a pointer to available space, the total size allocated.
return: a pointer to the vsa.
time complexity: O(1)
space complexity: O(1)
*/
vsa_t *VSAInit(void *memory, size_t total_size);

/* 
VSAAlloc
description: Allocate a block of memory of 'block_size' bytes from the VSA
input: a pointer to the vsa, size of the block to allocate.
return: a pointer to the newly allocated space or NULL if allocation failed.
time complexity: O(n)
space complexity: O(1)
*/
void *VSAAlloc(vsa_t *vsa, size_t block_size);

/*
VSAFree
description: Deallocate a previously allocated block from the VSA
input: pointer to the block to free.
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void VSAFree(void *block_ptr);

/*
LargestChunkAvailable
description: Checks for the largest block available
input: Pointer to VSA
return: The size of the largest block available
time complexity: O(n)
space complexity: O(1)
*/
size_t LargestChunkAvailable(const vsa_t *vsa);

#endif /* __VSA_H__ */

