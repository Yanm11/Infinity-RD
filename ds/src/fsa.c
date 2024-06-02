#include "fsa.h"
#include "stack.h"

struct fsa
{
	size_t block_size;
	size_t block_num;
	size_t free_blocks;
	size_t *head;
	char *memory_pool;
}

#define WORD_SIZE sizeof(size_t)

size_t FSASuggestSize(size_t block_size, size_t block_num)
{
	assert(0 < block_size);
	assert(0 < block_num);
	
	return (sizeof(fsa_t) + ((block_size + WORD_SIZE) * block_num));
}

fsa_t *FSAInit(void *memory, size_t total_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t i = 0;
		
	assert(memory);
	assert(0 < total_size);
	assert(0 < block_size);
	
	fsa = (fsa_t*)memory;
	
	fsa->block_size = block_size + WORD_SIZE;
	fsa->block_num = (total_size / fsa->block_size);
	fsa->free_blocks = fsa->block_num;
	fsa->head = (size_t*)fsa->memory_pool;
	
	for (;i < (fsa->block_num - 1); ++i)
	{
		(fsa->memory_pool + (i * (block_size + WORD_SIZE))) = (
								fsa->memory_pool + ((i+1) * (fsa->block_size)))
	}
	
	(fsa->memory_pool + (i * (block_size + WORD_SIZE))) = NULL;
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	void *alloc = NULL;

	assert(fsa);
	
	alloc = fsa->head + WORD_SIZE;
	
	fsa->head = fsa->head
	return fsa->head;
	
	
}
