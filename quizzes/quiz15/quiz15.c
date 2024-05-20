#include <stdio.h>
#include <stddef.h>

int FindNumber(int arr[], int num, size_t size);

int main(void)
{
	int arr[] = {1,2,3,4,5,6,7,-8,9,0};
	int num = -8;
	size_t size = sizeof(arr) / sizeof(int);
	
	if (FindNumber(arr, num, size))
	{
		printf("num is in arr\n");
	}
	else
	{
		printf("num is not in arr\n");
	}
	
	return 0;
}


int FindNumber(int arr[], int num, size_t size)
{
	size_t i = 0;
	int if_found_zero = 1;
	
	for (; i < size; ++i)
	{
		if_found_zero = if_found_zero * (arr[i] - num);
	}
	
	return (if_found_zero == 0);
}
