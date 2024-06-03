#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h> /* size_t */

typedef struct fsa fsa_t;


/*
FSASuggestSize
description: Suggests size to allocate according to demands
input: size per block, number of blocks
return: suggested size to allocate
time complexity: O(1)
space complexity: O(1)
*/
size_t FSASuggestSize(size_t block_size, size_t block_num);

/*
FSAInit
description: Initiates an instance of fsa.
input: a pointer to available space, the total size allocated and size per block.
return: a pointer to the fsa.
time complexity: O(1)
space complexity: O(1)
*/
fsa_t *FSAInit(void *memory, size_t total_size, size_t block_size);

/*
FSAAlloc
description: Allocte a block from the FSA
input: a pointer to the fsa.
return: a pointer to the newly allocated space
time complexity: O(1)
space complexity: O(1)
*/
void *FSAAlloc(fsa_t *fsa);

/*
FSAFree
description: Deallocte a block from the FSA
input: a pointer to the fsa, pointer to the block to free.
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void FSAFree(fsa_t *memory_pool, void *block_ptr);

/*
FSACountFree
description: Checks for free blocks in the FSA
input: Pointer to FSA
return: The number of free blocks
time complexity: O(1)
space complexity: O(1)
*/
size_t FSACountFree(const fsa_t *fsa);




#endif /* __FSA_H__ */
