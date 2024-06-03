/********************************** 
   Code by: Yan Meiri	
   Project: fixed size allocator
   Date: 2/06/24
   Review by: or
   Review Date: 03/06/24
   Approved by: or
   Approval Date: 03/06/24
**********************************/


#include <sys/types.h> /* ssize_t */
#include <assert.h> /* assert */

#include "fsa.h"

struct fsa
{
	ssize_t head;
	char *memory_pool;
};

#define WORD_SIZE sizeof(size_t)

static size_t aligned_block_size(size_t block_size)
{
	if (0 != block_size % WORD_SIZE)
	{
		block_size += (WORD_SIZE - (block_size % WORD_SIZE));
	}
	
	return block_size;
}

size_t FSASuggestSize(size_t block_size, size_t block_num)
{
	assert(0 < block_size);
	assert(0 < block_num);
	
	block_size = aligned_block_size(block_size);
	
	return (sizeof(fsa_t) + ((block_size + WORD_SIZE) * block_num));
}

fsa_t *FSAInit(void *memory, size_t total_size, size_t block_size)
{
	fsa_t *fsa = NULL;
	size_t i = 0;
	size_t struct_size = sizeof(fsa_t);
	size_t actual_block_size = 0;
	size_t number_of_blocks = 0;
	
	assert(memory);
	assert(0 < total_size);
	assert(0 < block_size);
	
	block_size = aligned_block_size(block_size);

	actual_block_size = block_size + WORD_SIZE;
	total_size -= struct_size;
	number_of_blocks = total_size / actual_block_size;
	
	fsa = (fsa_t*)memory;
	fsa->head = 0;
	fsa->memory_pool = (char*)memory + struct_size ;
	
	for (;i < (number_of_blocks - 1); ++i)
	{
		*(size_t*)(fsa->memory_pool + (i * actual_block_size)) = 
													((i+1) * (actual_block_size));
	}
	
	*(ssize_t*)(fsa->memory_pool + (i * actual_block_size)) = -1;
	
	return fsa;
}

void *FSAAlloc(fsa_t *fsa)
{
	void *alloc = NULL;

	assert(fsa);
	
	if (-1 == fsa->head)
	{
		return NULL;
	} 
	
	alloc = fsa->memory_pool + fsa->head + WORD_SIZE;
	
	fsa->head = *(ssize_t*)(fsa->memory_pool + fsa->head);

	return alloc;
}

void FSAFree(fsa_t *memory_pool, void *block_ptr)
{
	assert(memory_pool);
	assert(block_ptr);
	
	*(size_t*)((char*)block_ptr - (char)WORD_SIZE) = memory_pool->head;
	
	memory_pool->head = ((char*)block_ptr - (char)WORD_SIZE - 
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
		
		tmp_head = *(ssize_t*)(fsa->memory_pool + tmp_head);
	}
	
	return counter;
}










