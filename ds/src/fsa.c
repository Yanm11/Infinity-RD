#include <sys/types.h> /* ssize_t */
#include <assert.h> /* assert */
#include "fsa.h"

struct fsa
{
	ssize_t head;
	size_t *memory_pool;
};

#define WORD_SIZE sizeof(size_t)


size_t FSASuggestSize(size_t block_size, size_t block_num)
{
	assert(0 < block_size);
	assert(0 < block_num);
	
	while (block_size % WORD_SIZE != 0)
	{
		++block_size;
	}
	
	return (sizeof(fsa_t) + ((block_size + WORD_SIZE) * block_num));
}

fsa_t *FSAInit(void *memory, size_t total_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t i = 0;
	size_t size_struct_no_pool = sizeof(fsa_t) - sizeof(size_t);
	size_t actual_block_size = 0;
	
	
	assert(memory);
	assert(0 < total_size);
	assert(0 < block_size);
	
	/* algining the block_size */
	while (block_size % WORD_SIZE != 0)
	{
		++block_size;
	}

	fsa = (fsa_t*)memory;
	actual_block_size = block_size + WORD_SIZE;
	total_size -= size_struct_no_pool;
	
	fsa->head = 0;
	fsa->memory_pool = (size_t*)memory + size_struct_no_pool;
	
	for (;i < ((total_size / actual_block_size)- 1); ++i)
	{
		*(fsa->memory_pool + (i * actual_block_size)) = 
													((i+1) * (actual_block_size));
	}
	
	*(fsa->memory_pool + (i * (block_size + WORD_SIZE))) = -1;
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	void *alloc = NULL;

	assert(fsa);
	
	alloc = fsa->memory_pool + fsa->head + WORD_SIZE;
	
	fsa->head = *(fsa->memory_pool + fsa->head);

	return alloc;
}

void FSAFree(fsa_t *memory_pool, void *block_ptr)
{
	assert(memory_pool);
	assert(block_ptr);
	
	*((size_t*)block_ptr - WORD_SIZE) = memory_pool->head;
	
	memory_pool->head = ((size_t*)block_ptr - WORD_SIZE - 
													memory_pool->memory_pool);
}

size_t FSACountFree(const fsa_t *fsa)
{
	size_t counter = 0;
	ssize_t tmp_head = 0;
	
	assert(fsa);
	
	tmp_head = fsa->head;
	
	while ( -1 != tmp_head) 
	{
		++counter;
		
		tmp_head = *(fsa->memory_pool + tmp_head);
	}
	
	return counter;
}










