#include <stdio.h>
#include <stdlib.h>
#include "fsa.h"

static int checker = 0;

void TestFSASuggestSize()
{
    size_t suggested_size = 0;
    
    suggested_size = FSASuggestSize(32, 10);
    if (suggested_size != (320 + 16 + 10*8 ))
    {
        printf("TestFSASuggestSize failed for 32, 10\n");
        ++checker;
    }
    else
    {
        printf("TestFSASuggestSize passed for 32, 10\n");
    }

    suggested_size = FSASuggestSize(1, 1);
    if (suggested_size != (8*1 + 16 + 1*8 ))
    {
        printf("TestFSASuggestSize failed for 1, 1\n");
        ++checker;
    }
    else
    {
        printf("TestFSASuggestSize passed for 1, 1\n");
    }
}

void TestFSAInit()
{
    size_t total_size = FSASuggestSize(10, 10);
    void *memory = malloc(total_size);
    fsa_t *fsa = FSAInit(memory, total_size, 10);
    if (fsa == NULL)
    {
        printf("TestFSAInit failed for %lu, 10\n", total_size);
        ++checker;
    }
    else
    {
        printf("TestFSAInit passed for %lu, 10\n", total_size);
    }
    free(memory);
}

void TestFSAAllocFree()
{
    size_t total_size = FSASuggestSize(10, 10);
    void *memory = malloc(total_size);
    fsa_t *fsa = FSAInit(memory, total_size, 10);
    void *block1 = NULL;
    void *block2 = NULL;
    void *block3 = NULL;
	size_t free_blocks = 0;
	
    if (fsa == NULL)
    {
        printf("TestFSAAllocFree failed to initialize FSA\n");
        ++checker;
        free(memory);
        return;
    }

    block1 = FSAAlloc(fsa);
    if (block1 == NULL)
    {
        printf("TestFSAAlloc failed\n");
        ++checker;
    }
    else
    {
        printf("TestFSAAlloc passed\n");
    }
    
	block2 = FSAAlloc(fsa);
	if (block2 == NULL)
    {
        printf("TestFSAAlloc failed\n");
        ++checker;
    }
    else
    {
        printf("TestFSAAlloc passed\n");
    }
    
	block3 = FSAAlloc(fsa);
	if (block3 == NULL)
    {
        printf("TestFSAAlloc failed\n");
        ++checker;
    }
    else
    {
        printf("TestFSAAlloc passed\n");
    }
	
	
	free_blocks = FSACountFree(fsa);
    if (free_blocks != 7)
    {
        printf("TestFSACountFree failed: expected 7, got %lu\n", free_blocks);
        ++checker;
    }
    else
    {
        printf("TestFSACountFree passed: expected 7, got %lu\n", free_blocks);
    }
    
    FSAFree(fsa, block1);
    FSAFree(fsa, block2);
    FSAFree(fsa, block3);
    
  	free_blocks = FSACountFree(fsa);
    if (free_blocks != 10)
    {
        printf("TestFSACountFree failed: expected 10, got %lu\n", free_blocks);
        ++checker;
    }
    else
    {
        printf("TestFSACountFree passed: expected 10, got %lu\n", free_blocks);
    }
    printf("TestFSAFree passed\n");

    free(memory);
}

void TestFSACountFree()
{
    size_t total_size = FSASuggestSize(10, 10);
    void *memory = malloc(total_size);
    fsa_t *fsa = FSAInit(memory, total_size, 10);
    size_t free_blocks = 0;

    if (fsa == NULL)
    {
        printf("TestFSACountFree failed to initialize FSA\n");
        ++checker;
        free(memory);
        return;
    }

    free_blocks = FSACountFree(fsa);
    if (free_blocks != 10)
    {
        printf("TestFSACountFree failed: expected 10, got %lu\n", free_blocks);
        ++checker;
    }
    else
    {
        printf("TestFSACountFree passed: expected 10, got %lu\n", free_blocks);
    }

    FSAAlloc(fsa);
    free_blocks = FSACountFree(fsa);
    if (free_blocks != 9)
    {
        printf("TestFSACountFree failed: expected 9, got %lu\n", free_blocks);
        ++checker;
    }
    else
    {
        printf("TestFSACountFree passed: expected 9, got %lu\n", free_blocks);
    }

    free(memory);
}

int main()
{
    TestFSASuggestSize();
    TestFSAInit();
    TestFSAAllocFree();
    TestFSACountFree();
	
	if (!checker)
	{
	    printf("ALL TEST PASSED!\n");
	}
	
	else
	{
		printf("failed in %d tests\n", checker);
	}
	
    return 0;
}
