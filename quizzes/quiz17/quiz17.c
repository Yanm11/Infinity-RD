#include <stdio.h> /*printf */
#include <stddef.h> /* size_t */

long *SumIntPairsToLongs(int ints[], size_t numOfElements);

#define  NUM (6)

int main(void)
{
	int arr[NUM] = {1, 6, 456, -3, 8, 12};
	size_t i = 0;
	long *arr2 = NULL;
	
	arr2 = SumIntPairsToLongs(arr, NUM);
	
	printf("[");
	for (; i < NUM/2; ++i )
	{
		printf("%ld,", arr2[i]);
	}
	printf("]\n");
	
	return 0;
}

long *SumIntPairsToLongs(int ints[], size_t numOfElements)
{
	size_t i = 0;
	long *arr = (long *)ints;
	
	for (; i < numOfElements; i += 2)
	{
		arr[i/2] = (long)(ints[i] + ints[i+1]);
	}	

	return (long *)ints;
}
