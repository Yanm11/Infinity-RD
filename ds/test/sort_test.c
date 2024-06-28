#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free qsort */
#include <time.h> /* clock_t clockbCLOCK_PER_SECONDS */
#include <sys/types.h> /* ssize_t */

#include "sort.h"

#define n 5000

void TestBubbleSort();
void TestSelectionSort();
void TestInsertionSort();
void TestCountingSort();
void TestRadixSort();
void TestBinarySearch();
void TestBinarySearchRec();
void TestMergeSort();
void TestQuickSort();

/*static void PrintArr(int arr[],size_t num_elements);*/

static int compare(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}


int main(void) 
{
	TestBubbleSort();
	TestSelectionSort();
	TestInsertionSort();
	TestCountingSort();
	TestRadixSort();
	TestBinarySearch();
	TestBinarySearchRec();
	TestMergeSort();
	TestQuickSort();
	
    return 0;
}


void TestBubbleSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;

	 printf("------------------checking BUBBLE SORT --------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    start = clock();
    
    BubbleSort(arr, n, &compare);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Bubble sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

void TestSelectionSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;

	 printf("------------------checking SELECTION SORT -------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    start = clock();
    
    SelectionSort(arr, n, &compare);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Selection sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

void TestInsertionSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;

	 printf("------------------checking INSERTION SORT -------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    start = clock();
    
    InsertionSort(arr, n, &compare);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Insertion sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

void TestCountingSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;
	int lower_bound = 1;
    int upper_bound = 100;
	
	 printf("------------------checking COUNTING SORT -------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        arr_copy[i] = arr[i];
    }
    
    start = clock();
    CountingSort(arr, n);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Counting sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

void TestRadixSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;
	int lower_bound = 1000000;
    int upper_bound = 9999999;
	
	 printf("------------------checking RADIX SORT -------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        arr_copy[i] = arr[i];
    }
    
    start = clock();
    RadixSort(arr, n);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Radix sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
	
}

void TestBinarySearch()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	ssize_t index = 0;
	
	 printf("------------------checking BINARY SEARCH ITER -------------------\n");
	 
	index = BinarySearchIter(arr, sizeof(arr)/sizeof(int), 17);
	
	if (-1 == index)
	{
		printf("element does NOT exist in arr\n");
		return;
	}
	
	printf("element EXIST in arr\n");
	printf("----------------------------------------------------\n\n");
}

void TestBinarySearchRec()
{
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	ssize_t index = 0;
	
	 printf("---------------checking BINARY SEARCH RECURSION ------------\n");
	 
	index = BinarySearchRecursion(arr, sizeof(arr)/sizeof(int), 17);
	
	if (-1 == index)
	{
		printf("element does NOT exist in arr\n");
		return;
	}
	
	printf("element EXIST in arr\n");
	printf("----------------------------------------------------\n\n");
}


void TestMergeSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;

	 printf("------------------checking MERGE SORT -------------------\n");
	 
	/* randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    start = clock();
    
    MergeSort(arr, n);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	
    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Merge sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

void TestQuickSort()
{
    int *arr = (int *)malloc(n * sizeof(int));
    int *arr_copy = (int *)malloc(n * sizeof(int));
    int i;
    clock_t start, end;
    double sort_time, qsort_time;
	
	 printf("------------------checking QUICK SORT -------------------\n");
	 
/*	 randomise an array and its copy */
    srand(time(NULL));
    for (i = 0; i < n; i++) 
    {
        arr[i] = rand() % 10000;
        arr_copy[i] = arr[i];
    }

    start = clock();
    
    QSort(arr, n, sizeof(int), compare);
    end = clock();
    sort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
    start = clock();
    qsort(arr_copy, n, sizeof(int), compare);
    end = clock();
    qsort_time = ((double)(end - start)) / CLOCKS_PER_SEC;
	
	
    for (i = 0; i < n; i++) 
    {
        if (arr[i] != arr_copy[i]) 
        {
            printf("The array is not sorted properly.\n");
            free(arr);
            free(arr_copy);
            
            return;
        }
    }

    printf("The array is sorted properly.\n");
    printf("Quick sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}

/*static void PrintArr(int arr[],size_t num_elements)*/
/*{*/
/*	size_t i = 0;*/
/*	printf("[");*/
/*	for (;i < num_elements; ++i)*/
/*	{*/
/*		printf("%d,",arr[i]);*/
/*	}*/
/*	*/
/*	printf("]\n");*/
/*}*/

