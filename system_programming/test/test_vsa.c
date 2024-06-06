#include <stdlib.h> /* size_t malloc free*/
#include <stdio.h> /* printf */

#include "vsa.h"

static void TestFlow1(void);
static void TestFlow2(void);

static size_t checker = 0;

int main(void)
{
	
	TestFlow1();
	TestFlow2();
	
	if(0 == checker)
	{
		printf("\nAll tests passed\n");
	}
	
	return 0;
}



static void TestFlow1(void)
{
	int *b1 = NULL;
	int *b2 = NULL;
	int *b3 = NULL;
	int *b4 = NULL;
	int *b5 = NULL;
	
	int *ptr = (int *)malloc(300);
	vsa_t *vsa = VSAInit(ptr, 300);
	if(264 != LargestChunkAvailable(vsa))
	{
		printf("VSAInit failed\n");
		++checker;
		return;
	}
	
	
	b1 = (int *)VSAAlloc(vsa, 39);
	if(208 != LargestChunkAvailable(vsa) || b1 != (int *)vsa + 4)
	{
		printf("VSAAlloc 1 failed\n");
		++checker;
		return;
	}
	
	
	b2 = (int *)VSAAlloc(vsa, 80);
	if(112 != LargestChunkAvailable(vsa) || b2 != (int *)vsa + 18)
	{
		printf("VSAAlloc 2 failed\n");
		++checker;
		return;
	}
	

	*b1 = 45;
	VSAFree(b1);
	b3 = (int *)VSAAlloc(vsa, 12);
	if(112 != LargestChunkAvailable(vsa) || b3 != (int *)vsa + 4 || *b3 != 45)
	{
		printf("VSAAlloc 3 failed\n");
		printf("LargestChunkAvailable 3 failed\n");
		printf("VSAFree 3 failed\n");
		++checker;
		return;
	}
	
	b4 = (int *)VSAAlloc(vsa, 112);
	if(8 != LargestChunkAvailable(vsa) || b4 != (int *)vsa + 42)
	{
		printf("VSAAlloc 4 failed\n");
		printf("LargestChunkAvailable 4 failed\n");
		++checker;
		return;
	}
	

	b5 = (int *)VSAAlloc(vsa, 8);
	if(0 != LargestChunkAvailable(vsa) || b5 != (int *)vsa + 12)
	{
		printf("VSAAlloc 5 failed\n");
		printf("LargestChunkAvailable 5 failed\n");
		++checker;
		return;
	}
	

	VSAFree(b2);
	if(80 != LargestChunkAvailable(vsa))
	{
		printf("LargestChunkAvailable 6 failed\n");
		++checker;
		return;
	}
	
	VSAFree(b5);
	if(104 != LargestChunkAvailable(vsa))
	{
		printf("LargestChunkAvailable 7 failed\n");
		++checker;
		return;
	}
	
	b5 = (int *)VSAAlloc(vsa, 148);
	if(104 != LargestChunkAvailable(vsa) || b5 != NULL)
	{
		printf("VSAAlloc 8 failed\n");
		++checker;
		return;
	}
	
	VSAFree(b3);
	if(136 != LargestChunkAvailable(vsa))
	{
		printf("VSAFree 9 failed\n");
		++checker;
		return;
	}
	
	VSAFree(b4);

	if(264 != LargestChunkAvailable(vsa))
	{
		printf("LargestChunkAvailable 10 failed\n");
		++checker;
		return;
	}
	
	
	printf("TestFlow1 passed\n");
	free(ptr);
}
	
	
	
static void TestFlow2(void)
{
	int *b1 = NULL;
	int *b2 = NULL;
	int *b3 = NULL;
	
	int *ptr = (int *)malloc(250);
	vsa_t *vsa = VSAInit(ptr, 250);
	if(216 != LargestChunkAvailable(vsa))
	{
		printf("VSAInit failed\n");
		++checker;
		return;
	}
	
	b1 = (int *)VSAAlloc(vsa, 40);
	b2 = (int *)VSAAlloc(vsa, 80);
	b3 = (int *)VSAAlloc(vsa, 48);
	
	VSAFree(b1);
	VSAFree(b2);
	b2 = (int *)VSAAlloc(vsa, 104);
	if(b2 != (int *)vsa + 4)
	{
		printf("VSAAlloc 2 - 1 failed\n");
		++checker;
		return;
	}
	
	(void)b3;
	printf("TestFlow2 passed\n");
	free(ptr);
}
	
	

