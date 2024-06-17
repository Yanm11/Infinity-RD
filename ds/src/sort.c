#include <assert.h> /* assert */
#include <stdlib.h> /* calloc free */
#include <sys/types.h> /* ssize_t */

#include "sort.h"

static void Swap(int *a, int *b);
static int FindMax(int arr[], size_t size);
static int FindMin(int arr[], size_t size);
static size_t FindMaxNumberOfDigits(int arr[], size_t size);

/********************* API FUNCTIONS ************************/

void BubbleSort(int arr[], size_t size, sort_compare_func_t cmp_func)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(arr);
	assert(cmp_func);
	
	for (; i < size; ++i)
	{
		for (j = 0; j < (size - 1 - i); ++j)
		{
			if (0 < cmp_func((arr + j), (arr + j + 1)))
			{
				Swap((arr + j), (arr + j + 1));
			}
		}
	}
}

void SelectionSort(int arr[], size_t size, sort_compare_func_t cmp_func)
{
	size_t i = 0;
	size_t j = 0;
	
	assert(arr);
	assert(cmp_func);
	
	for (; i < size; ++i)
	{
		int curr_min_index = i;

		for (j = (i + 1); j < size; ++j)
		{
			if (0 < cmp_func((arr + curr_min_index), (arr + j)))
			{
				curr_min_index = j;
			}
		}
		
		Swap((arr + i), (arr + curr_min_index));
	}
}

void InsertionSort(int arr[], size_t size, sort_compare_func_t cmp_func)
{
	size_t i = 1;
	ssize_t j = 0;
	
	assert(arr);
	assert(cmp_func);
	
	for (; i < size; ++i)
	{
		int tmp_index = i;
		
		for (j = (i - 1); j >= 0; --j)
		{
			if (0 > cmp_func((arr + tmp_index), (arr + j)))
			{
				Swap((arr + tmp_index), (arr + j));
				tmp_index = j;
			}
		}
	}
}

void CountingSort(int arr[], size_t size)
{
	size_t i = 0;
	ssize_t j = 0;
	size_t max_number = 0;
	size_t min_number = 0;
	int *output_arr = NULL;
	int *lookup_occurrences = NULL;
	
	assert(arr);
	
	min_number = FindMin(arr, size);
	max_number = FindMax(arr, size);
	
	lookup_occurrences = (int*)calloc((max_number - min_number + 1), sizeof(int));
	output_arr = (int*)calloc(size, sizeof(int));
	
	for (; i < size; ++i)
	{
		++*(lookup_occurrences + arr[i] - min_number); 
	}
	
	for (i = 0; i < (max_number - min_number) ; ++i)
	{
		lookup_occurrences[i + 1] +=  lookup_occurrences[i];
	}
	
	for (j = (size - 1); j >= 0; --j)
	{
		output_arr[lookup_occurrences[arr[j] - min_number] - 1] = arr[j];
		--lookup_occurrences[arr[j] - min_number];
	}
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = output_arr[i]; 
	}
	
	free(output_arr);
	free(lookup_occurrences);
}

void RadixSort(int arr[], size_t size)
{
	size_t max_num_digit = 0;
	
	assert(arr);
	
	max_num_digit = FindMaxNumberOfDigits(arr, size);
	
}

/********************* HELP FUNCTIONS ************************/

static void Swap(int *a, int *b)
{	
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

static int FindMax(int arr[], size_t size)
{
	int max = 0;
	size_t i = 0;
	
	assert(arr);
	
	for (; i < size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	
	return max;	
}

static int FindMin(int arr[], size_t size)
{
	int min = 0;
	size_t i = 0;
	
	assert(arr);
	
	min = arr[0];
	
	for (; i < size; ++i)
	{
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}
	
	return min;	
}

static size_t FindMaxNumberOfDigits(int arr[], size_t size)
{
	size_t max = 0;
	size_t i = 0;
	
	assert(arr);
	
	for (; i < size; ++i)
	{
		int num = arr[i];
		size_t count = 0;
		 
		while (0 != num)
		{
			num /= 10;
			++count;
		}
		
		if (count > max)
		{
			max = count;
		}
	}
	
	return max;
}
