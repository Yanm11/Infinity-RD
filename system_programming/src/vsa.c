/********************************** 
   Code by: Yan Meiri	
   Project: variable size allocator
   Date: 4/06/24
   Review by: avshalom
   Review Date: 07/06/2024
   Approved by: 
   Approval Date: 
**********************************/


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
#define MAGIC_NUMBER 11

static void *AlignedStart(char *memory);
static size_t AlignedEnd(size_t total_size);
static size_t AlignedBlockSize(size_t block_size);
static void CreateBlock(void *address, long size);
static void DeFrag(vsa_t *address);
static long Abs(long size);
static vsa_t *NextBlock(vsa_t *address);


/******** API Functions *********/


vsa_t *VSAInit(void *memory, size_t total_size)
{
		long size = 0;
		void *end_memory = NULL;
		void *allign_memory = NULL;
		
		assert(memory);
		assert((MIN_BLOCK_SIZE + STRUCT_SIZE) < total_size);
		
		/* allign memory and total size */
		allign_memory = AlignedStart(memory);
		total_size -= ((size_t)allign_memory - (size_t)memory);
		total_size = AlignedEnd(total_size);
		
		/* creating the first block */
		size = (long)(total_size - (2 * STRUCT_SIZE));
		CreateBlock(allign_memory, size);
		
		/* creating the last block */
		end_memory = (char*)allign_memory + STRUCT_SIZE + size;
		CreateBlock(end_memory, 0);
				
		return (vsa_t *)allign_memory;
}

void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
	void *return_address = NULL;
	vsa_t *runner = NULL;
	long curr_size = 0; 
	
	assert(vsa);
	
	/* allign the block size*/
	block_size = AlignedBlockSize(block_size);
	
	runner = vsa;
	
	while (0 != runner->size)
	{
		DeFrag(runner);
		
		curr_size = Abs(runner->size);
		
		/* check if block size is enogh and if its free */
		if ((curr_size >= (long)block_size) && (IS_FREE(runner->size)))
		{
			long remain_size = curr_size - (long)block_size;
			
			return_address = (void*)((char*)runner + STRUCT_SIZE);
			
			/* check if the size that remain is big enogh for another block */
			if (remain_size < (long)MIN_BLOCK_SIZE)
			{
				block_size = curr_size;
			}
			else
			{
				void *new_block_address = (char*)return_address + block_size;
				long new_block_size = remain_size - STRUCT_SIZE;
				CreateBlock(new_block_address, new_block_size);				
			}
			
			runner->size = CONVERT_FROM_EMPTY(block_size);
			
			return return_address;
		}
		else
		{
			runner = NextBlock(runner); 
		}
	}
	
	return NULL;
}

void VSAFree(void *block_ptr)
{
	assert(block_ptr);
	assert(MAGIC_NUMBER == *(long*)((char*)block_ptr - WORD_SIZE));
	
	block_ptr =	(void*)((char*)block_ptr - STRUCT_SIZE);
	((vsa_t*)block_ptr)->size = CONVERT_TO_EMPTY(*(long*)block_ptr);
}

size_t LargestChunkAvailable(const vsa_t *vsa)
{	
	vsa_t *runner = NULL;
	long max_block = 0;
	long curr_size = 0;
	
	assert(vsa);

	runner = (vsa_t*)vsa;
	
	while (0 != runner->size)
	{
		DeFrag(runner);
		
		curr_size = Abs(runner->size);
		
		if (curr_size > max_block && IS_FREE(runner->size))
		{
			max_block = curr_size;
		}
		
		runner = NextBlock(runner);
	}
	
	return max_block;
}


/******** Help Functions *********/


static void DeFrag(vsa_t *address)
{
	vsa_t *next = NULL;
	
	assert(address);
	
	next = NextBlock(address);
	
	while (IS_FREE(address->size) && IS_FREE(next->size))
	{
		address->size += (next->size + STRUCT_SIZE);
		next = NextBlock(next);
	} 
	
}

static void *AlignedStart(char *memory)
{
	assert(memory);
	if (0 != ((size_t)memory % WORD_SIZE))
	{
		memory += (WORD_SIZE - ((size_t)memory % WORD_SIZE)); 
	} 
	
	return memory;
}

static size_t AlignedEnd(size_t total_size)
{
	if (0 != total_size % WORD_SIZE)
	{
		total_size -= (total_size % WORD_SIZE);
	}
	
	return total_size;
}

static size_t AlignedBlockSize(size_t block_size)
{
	if (0 != block_size % WORD_SIZE)
	{
		block_size += (WORD_SIZE - (block_size % WORD_SIZE)); 
	} 
	
	return block_size;
}

static void CreateBlock(void *address, long size)
{
	vsa_t block = {0};

	assert(address);
	
	block.size = size;
	#ifndef NDEBUG
		block.magic = MAGIC_NUMBER;
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

static vsa_t *NextBlock(vsa_t *address)
{
	assert(address);
	
	return ((vsa_t*)((char*)address + Abs(address->size) + STRUCT_SIZE));
}

