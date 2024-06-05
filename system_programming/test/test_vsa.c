#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h>

#include "vsa.h"

#define TESTNUM 3

static char failed_tests_print[200] = {'\0'};

static int TestVSAAlloc(void);
static int TestVSAFree(void);
static int TestLargestChunkAvailable(void);

void AddFailedTest(const char *str);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestVSAAlloc();
	printf("Tested VSAAlloc\n");
	failed_tests_num += TestVSAFree();
	printf("Tested VSAFree\n");
	failed_tests_num += TestLargestChunkAvailable();
	printf("Tested LargestChunkAvailable\n");

	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}


void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestVSAAlloc(void)
{
	void *allocated_space = NULL;
	vsa_t *memory_pool = NULL;
	size_t total_size = 1000;
	size_t *elements[20] = {NULL};
	size_t *block = NULL;
	size_t loop_count = 0;
	size_t inside_loop_count = 0;
	size_t blocks_allocated = 0;
	
	allocated_space = malloc(total_size);
	memory_pool = VSAInit(allocated_space, total_size);
	
	while(80 < LargestChunkAvailable(memory_pool))
	{
		elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
		++loop_count;
	}
	
	/* checks if VSAAlloc succeded allocating all blocks*/
	blocks_allocated = loop_count;
	loop_count = 0;
	while(loop_count < blocks_allocated)
	{
		if (!elements[loop_count])
		{
			AddFailedTest("TestVSAAlloc1\n");
			free(allocated_space);
			return 1;
		}
		++loop_count;
	}
	
	/* checks if VSAAlloc allocated different address each time*/
	loop_count = 0;
	while(loop_count < blocks_allocated)
	{
		inside_loop_count = loop_count + 1;
		while(inside_loop_count < blocks_allocated)
		{
			if (elements[loop_count] == elements[inside_loop_count])
			{
				AddFailedTest("TestVSAAlloc2\n");
				free(allocated_space);
				return 1;
			}
			++inside_loop_count;
		}
		++loop_count;
	}
	
	/* checks if VSAAlloc doesn't allocate when there is no free space*/
	block = (size_t *)VSAAlloc(memory_pool, 80);
	if (block)
	{
		AddFailedTest("TestVSAAlloc3\n");
		free(allocated_space);
		return 1;
	}
	
	/* checks if the defragmentation of the free blocks is successful*/
	VSAFree(elements[2]);
	VSAFree(elements[3]);
	
	block = (size_t *)VSAAlloc(memory_pool, 160);
	if (!block)
	{
		AddFailedTest("TestVSAAlloc4\n");
		free(allocated_space);
		return 1;
	}

	
	free(allocated_space);
	return 0;
}

static int TestVSAFree(void)
{
	void *allocated_space = NULL;
	vsa_t *memory_pool = NULL;
	size_t total_size = 1000;
	size_t *elements[20] = {NULL};
	size_t *block = NULL;
	size_t loop_count = 0;
	
	allocated_space = malloc(total_size);
	memory_pool = VSAInit(allocated_space, total_size);
	
	while(80 < LargestChunkAvailable(memory_pool))
	{
		elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
		++loop_count;
	}
	
	/* checks if VSAFree actually frees the block*/
	VSAFree(elements[0]);
	
	block = (size_t *)VSAAlloc(memory_pool, 80);
	if (!block)
	{
		AddFailedTest("TestVSAFree\n");
		free(allocated_space);
		return 1;
	}
	
	free(allocated_space);
	return 0;
}

static int TestLargestChunkAvailable(void)
{
	
	void *allocated_space = NULL;
	vsa_t *memory_pool = NULL;
	size_t total_size = 1000;
	size_t *elements[20] = {NULL};
	size_t loop_count = 0;
	size_t previous_largest_chunk = 0;
	
	allocated_space = malloc(total_size);
	memory_pool = VSAInit(allocated_space, total_size);
	
	
	/* checks if LargestChunkAvailable decreases after every alloc */
	
	previous_largest_chunk = LargestChunkAvailable(memory_pool);
	while(loop_count < 6)
	{
		elements[loop_count] = (size_t *)VSAAlloc(memory_pool, 80);
		++loop_count;
		
		if (previous_largest_chunk <= LargestChunkAvailable(memory_pool))
		{
			AddFailedTest("TestLargestChunkAvailable1\n");
			free(allocated_space);
			return 1;
		}
		previous_largest_chunk = LargestChunkAvailable(memory_pool);
	}
	
	/* checks if LargestChunkAvailable increases after every free */
	
	previous_largest_chunk = LargestChunkAvailable(memory_pool);
	--loop_count;
	while(loop_count > 0)
	{
		VSAFree(elements[loop_count]);
		--loop_count;
		
		if (previous_largest_chunk >= LargestChunkAvailable(memory_pool))
		{
			AddFailedTest("TestLargestChunkAvailable2\n");
			free(allocated_space);
			return 1;
		}
		previous_largest_chunk = LargestChunkAvailable(memory_pool);
	}
	
	free(allocated_space);

	return 0;
}

