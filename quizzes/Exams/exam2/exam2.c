#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

int WhichNumberIsMissing(int arr[]);

int main(void)
{
	int arr[1023] = {0};
	size_t i = 0;
	
	for (; i < 1024; ++i)
	{
		arr[i] = i;
	}
	arr[1023] = 1024;
	printf("missing %d\n", WhichNumberIsMissing(arr));
	
	return 0;
	
}

int WhichNumberIsMissing(int arr[])
{
	size_t sum_0_1024 = 0;
	size_t sum_arr = 0;
	size_t i = 0;
	
	assert(arr);
	
	for(; i < 1024; ++i)
	{
		sum_0_1024 += i;
		sum_arr += arr[i];
	}
	
	sum_0_1024 += 1024;
	sum_0_1024 -= sum_arr;
	
	return sum_0_1024;
}
