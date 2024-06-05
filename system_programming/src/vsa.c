#include <assert.h> /* assert*/

#include "vsa.h"

struct vsa
{
	long size;
	#ifndef NDEBUG
		size_t magic;
	#endif
};

#define IS_FREE(size) (size > 0)
#define STRUCT_SIZE sizeof(vsa_t) 
#define MIN_BLOCK_SIZE (STRUCT_SIZE + sizeof(size_t))
#define WORD_SIZE sizeof(size_t)
#define CONVERT_FROM_EMPTY(size) (size * -1)
#define CONVERT_TO_EMPTY(size) (size * -1)

static void *Aligned_start(char *memory);
static size_t Aligned_end(size_t total_size);
static void CreateBlock(void *address, long size);
static void DeFrag(vsa_t *address);
static long Abs(long size);

vsa_t *VSAInit(void *memory, size_t total_size)
{
		long size = 0;
		void *end_memory = NULL;
		
		assert(memory);
		
		/* allign memory */
		memory = Aligned_start(memory);
		total_size = Aligned_end(total_size);
		
		/* creating the first block */
		size = (long)(total_size - (2 * STRUCT_SIZE));
		CreateBlock(memory, size);
		
		/* creating the last block */
		end_memory = (char*)memory + STRUCT_SIZE + size;
		CreateBlock(end_memory, 0);
				
		return (vsa_t *)memory;
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	void *return_address = NULL;
	vsa_t *runner = NULL;
	int flag = 1;
	
	assert(vsa);

	if (0 != block_size % WORD_SIZE)
	{
		block_size += (WORD_SIZE - (block_size % WORD_SIZE)); 
	} 
	
	runner = vsa;
	
	while (0 != runner->size && flag)
	{
		DeFrag(runner);
		
		if ((runner->size >= (long)block_size) && (IS_FREE(runner->size)))
		{
			long remain_size = runner->size - (long)block_size;
			
			return_address = (void*)((char*)runner + STRUCT_SIZE);

			if (remain_size < (long)MIN_BLOCK_SIZE)
			{
				block_size = runner->size;
				runner = (vsa_t*)((char*)runner + block_size + STRUCT_SIZE);
			}
			else
			{
				void *new_block_address = (char*)return_address + block_size;
				long new_block_size = remain_size - STRUCT_SIZE;
				CreateBlock(new_block_address, new_block_size);
				
				runner->size = CONVERT_FROM_EMPTY(block_size);
			}
			
			flag = 0;
		}
		else
		{
			runner = (vsa_t*)((char*)runner + Abs(runner->size) + STRUCT_SIZE); 
		}
	}
	
	if (1 == flag)
	{
		return NULL;
	}
	
	return return_address;
}

void VSAFree(void *block_ptr)
{
	assert(block_ptr);
	assert(11 == *((char*)block_ptr - WORD_SIZE));
	
	block_ptr =	(void*)((char*)block_ptr - STRUCT_SIZE);
	((vsa_t*)block_ptr)->size = CONVERT_TO_EMPTY(*(long*)block_ptr);
}

size_t LargestChunkAvailable(const vsa_t *vsa)
{	
	vsa_t *runner = NULL;
	long max_block = 0;
	
	assert(vsa);

	runner = (vsa_t*)vsa;
	
	while (0 != runner->size)
	{
		DeFrag(runner);
		
		if (Abs(runner->size) > max_block && IS_FREE(runner->size))
		{
			max_block = runner->size;
		}
		
		runner = (vsa_t*)((char*)runner + Abs(runner->size) + STRUCT_SIZE);
	}
	
	return max_block;
	
}

static void DeFrag(vsa_t *address)
{
	vsa_t *runner = (vsa_t*)address;
	vsa_t *next = (vsa_t*)((char*)runner + runner->size + STRUCT_SIZE);
	
	if (IS_FREE(runner->size) && IS_FREE(next->size))
	{
		runner->size += (next->size + STRUCT_SIZE);
	} 
	
}

static void *Aligned_start(char *memory)
{
	if (0 != ((size_t)memory % WORD_SIZE))
	{
		memory += (WORD_SIZE - ((size_t)memory % WORD_SIZE)); 
	} 
	
	return memory;
}

static size_t Aligned_end(size_t total_size)
{
	if (0 != total_size % WORD_SIZE)
	{
		total_size -= (total_size % WORD_SIZE);
	}
	
	return total_size;
}

static void CreateBlock(void *address, long size)
{
	vsa_t block = {0};
	block.size = size;
	#ifndef NDEBUG
		block.magic = 11;
	#endif
	
	*(vsa_t *)address = block;
}

static long Abs(long size)
{
	if (0 > size)
	{
		return (size * -1);
	}
	
	return size;
}

