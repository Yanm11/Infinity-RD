#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

void SortArrayOf0And1(int arr[], size_t size);

int main(void)
{
	int arr[] = {0,1,0,1,1,1,1,1,1,1,1,1,1,1,0};
	size_t size = sizeof(arr)/4;
	size_t i = 0;
	
	SortArrayOf0And1(arr, size);
	
	printf("[");
	for (; i < size; ++i)
	{
		printf("%d,", arr[i]);
	}
	printf("]\n");
	
	
	return 0;
}

void SortArrayOf0And1(int arr[], size_t size)
{
	size_t i = 0;
	size_t j = 1;
	
	assert(arr);
	
	for (; j < size; ++j)
	{
		if (arr[i] > arr[j])
		{
			arr[i] = arr[i] ^ arr[j];
			arr[j] = arr[i] ^ arr[j];
			arr[i] = arr[i] ^ arr[j];
			
			++i;
		}
		else if (0 == arr[i])
		{
			++i;
		}
	}
}
