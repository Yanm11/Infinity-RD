#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free size_t */

typedef struct result
{
	size_t start;
	size_t end;
	int sum;
} result_t;

void MaxSubArray(int arr[], size_t size, result_t *result);

int main(void)
{
	int arr[9] = {-2,-1,30,-4,-10,12,-3,5,1};
	result_t *result = (result_t*)malloc(sizeof(result_t));
	MaxSubArray(arr, sizeof(arr)/sizeof(int), result);
	printf("max sum is: %d\nstart at; %ld\nend at: %ld\n",result->sum,result->start,result->end);
	
	free(result);
	
	return 0;
}


void MaxSubArray(int arr[], size_t size, result_t *result)
{
	size_t current_start = 0;
	size_t current_end = 0;
	int current_sum = 0;
	size_t max_start = 0;
	size_t max_end = 0;
	int max_sum = 0;
	
	for (; current_end < size; ++current_end, ++arr)
	{
		if (current_sum + *arr >= 0)
		{
			current_sum += *arr;
		}
		else
		{
			current_sum = 0;
			current_start = current_end + 1;
		}
		
		if (current_sum >= max_sum)
		{
			max_sum = current_sum;
			max_start = current_start;
			max_end = current_end;
		}
	}
	
	result->start = max_start;
	result->end = max_end;
	result->sum = max_sum;
}

