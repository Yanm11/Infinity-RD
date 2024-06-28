#include <assert.h> /* assert */
#include <stdlib.h> /* calloc free */
#include <sys/types.h> /* ssize_t */
#include <string.h> /* memcpy */

#include "sort.h"

typedef int (*compar_func)(const void *, const void *);

static void Swap(int *a, int *b);
static int FindMax(int arr[], size_t size);
static int FindMin(int arr[], size_t size);
static size_t FindMaxNumberOfDigits(int arr[], size_t size);
static void CountingSortRadix(int arr[], size_t size, int exp);
static int Merge(int *arr_c, int *arr_a, int *arr_b,
				 size_t size_a, size_t size_b);
static size_t FindPivot(void *base, size_t index_start, size_t index_middle, 
				 		size_t index_end, size_t size, compar_func cmp_func);

static size_t Max(void *base, size_t a, size_t b,
				  size_t size, compar_func cmp_func);
static size_t Min(void *base, size_t a, size_t b,
				  size_t size, compar_func cmp_func);
static void SwapQuick(void *a, void *b, size_t size);
static void QSortLomuto(void *base, size_t start, size_t end, size_t size, compar_func cmp_func);
static size_t PartitionLomuto(void *base, size_t start, size_t end, size_t size, compar_func cmp_func);

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
	if (NULL == lookup_occurrences  || NULL == output_arr  ) 
	 {
        return;
    }
    
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
		int digit = arr[j] - min_number;
		output_arr[lookup_occurrences[digit] - 1] = arr[j];
		--lookup_occurrences[digit];
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
	size_t exp = 1;
	
	assert(arr);
	
	max_num_digit = FindMaxNumberOfDigits(arr, size);
	
	while (0 < max_num_digit)
	{
		CountingSortRadix(arr, size, exp);
		exp *= 10;
		--max_num_digit;
	}
	
}

ssize_t BinarySearchIter(int *arr, size_t size, int element)
{
	size_t start_size = 0;
	size_t end_size = size; 
	size_t remained_size = end_size - start_size;
	ssize_t middle =  remained_size / 2;
	
	assert(arr);
	
	while (1 < remained_size && element != arr[middle])
	{
		if (arr[middle] > element)
		{
				end_size = middle; 
				remained_size = end_size - start_size;
				middle -=  (remained_size / 2) + 0.5;
		}
		else
		{
			start_size = middle;
			remained_size = end_size - start_size;
			middle +=  (remained_size / 2);
		}
	}
	
	if (arr[middle] == element)
	{
		return middle;
	}
	
	return -1;
}

ssize_t BinarySearchRecursion(int *arr, size_t size, int element)
{
	ssize_t middle =  size / 2;
	
	if (arr[middle] == element)
	{
		return middle;
	}
	else if (1 >= size)
	{
		return -1;
	}
	
	arr = (arr[middle] < element) ? arr + middle : arr;
	
	return BinarySearchRecursion(arr, size - middle, element);
}

int MergeSort(int *arr_to_sort, size_t num_elements)
{
	size_t left_size = num_elements / 2;
	size_t right_size = num_elements - left_size;
	size_t i = 0;
	int *arr_to_sort_start = arr_to_sort;
	int *arr_a_start = NULL;
	int *arr_b_start = NULL;
	
	int *arr_a = (int*)malloc(left_size * sizeof(int));
	int *arr_b = (int*)malloc(right_size * sizeof(int));
	if(NULL == arr_a || NULL == arr_b)
	{	
		free(arr_a);
		free(arr_b);
			
		return -1;
	}

	assert(arr_to_sort);

	arr_a_start = arr_a;
	arr_b_start = arr_b;
	
	if (1 == num_elements)
	{	
		free(arr_a);
		free(arr_b);
		
		return 0;
	}
	
	for(i = 0; i < left_size; ++i)
	{
		*arr_a = *arr_to_sort;
		
		++arr_a;
		++arr_to_sort;
	}
	
	for(i = 0; i < right_size; ++i)
	{
		*arr_b = *arr_to_sort;
		
		++arr_b;
		++arr_to_sort;
	}
	
	MergeSort(arr_a_start, left_size);
	MergeSort(arr_b_start, right_size);
	
	Merge(arr_to_sort_start,
				 arr_a_start,
				 arr_b_start,
				 left_size, 
				 right_size);
				 
	free(arr_a_start);
	free(arr_b_start);

	return 0;
}

void QSort(void *base, size_t nmemb, size_t size, compar_func cmp_func)
{
    if (nmemb < 2)
    {
        return;
    }

    assert(base);
    assert(cmp_func);

    QSortLomuto(base, 0, nmemb - 1, size, cmp_func);
}


/********************* HELP FUNCTIONS ************************/

static void QSortLomuto(void *base, size_t start, size_t end, size_t size, compar_func cmp_func)
{
    if (start < end)
    {
        size_t pivot = PartitionLomuto(base, start, end, size, cmp_func);
        if (pivot > 0)
        {
            QSortLomuto(base, start, pivot - 1, size, cmp_func);
        }
        QSortLomuto(base, pivot + 1, end, size, cmp_func);
    }
}

static size_t PartitionLomuto(void *base, size_t start, size_t end,
							  size_t size, compar_func cmp_func)
{
    char *char_base = (char *)base;
    char *pivot = char_base + end * size;
    size_t i = start;
    size_t j = start;

    for (; j < end; ++j)
    {
        if (cmp_func(char_base + j * size, pivot) < 0)
        {
            SwapQuick(char_base + i * size, char_base + j * size, size);
            i++;
        }
    }
    SwapQuick(char_base + i * size, char_base + end * size, size);
    return i;
}

static void SwapQuick(void *a, void *b, size_t size)
{
    char tmp[256];  /* For small sizes */
    char *buffer = (size <= sizeof(tmp)) ? tmp : (char*)malloc(size);
    
    memcpy(buffer, a, size);
    memcpy(a, b, size);
    memcpy(b, buffer, size);
    
    if (buffer != tmp)
    {
        free(buffer);
    }
}

static int Merge(int *arr_c, int *arr_a, int *arr_b,
				 size_t size_a, size_t size_b)
{	
	assert(arr_a);
	assert(arr_b);
	
	while (0 < size_a && 0 < size_b)
	{
		/* when b is samller update c with b */
		if (*arr_a >= *arr_b)
		{
			*arr_c = *arr_b;
			
			++arr_b;
			++arr_c;
			--size_b;
		}
		/* when a is samller update c with a */
		else
		{
			*arr_c = *arr_a;
			
			++arr_a;
			++arr_c;
			--size_a;
		}
	}
	
	/* add the rest of a or b */
	while (0 < size_a)
	{
		*arr_c = *arr_a;
		
		++arr_a;
		++arr_c;
		--size_a;
	}
	
	while (0 < size_b)
	{
		*arr_c = *arr_b;
		
		++arr_b;
		++arr_c;
		--size_b;		
	}
	
	return 0;
}

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

static void CountingSortRadix(int arr[], size_t size, int exp)
{
	size_t i = 0;
	ssize_t j = 0;
	size_t max_number = 9;
	int *output_arr = NULL;
	int *lookup_occurrences = NULL;
	
	assert(arr);
	
	lookup_occurrences = (int*)calloc((max_number + 1), sizeof(int));
	output_arr = (int*)calloc(size, sizeof(int));
	
	 if (NULL == lookup_occurrences  || NULL == output_arr  ) 
	 {
        return;
    }
    
	for (; i < size; ++i)
	{
		++*(lookup_occurrences + ((arr[i] / exp ) % 10)); 
	}
	
	for (i = 0; i < max_number ; ++i)
	{
		lookup_occurrences[i + 1] +=  lookup_occurrences[i];
	}
	
	for (j = (size - 1); j >= 0; --j)
	{
		int digit = (arr[j] / exp) % 10;
		output_arr[lookup_occurrences[digit] - 1] = arr[j];
		--lookup_occurrences[digit];
	}
	
	for (i = 0; i < size; ++i)
	{
		arr[i] = output_arr[i]; 
	}
	
	free(output_arr);
	free(lookup_occurrences);
}


