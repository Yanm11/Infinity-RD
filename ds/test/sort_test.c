#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free qsort */
#include <time.h> /* clock_t clockbCLOCK_PER_SECONDS */

#include "sort.h"

void TestBubbleSort();
void TestSelectionSort();
void TestInsertionSort();
void TestCountingSort();

static int compare(const void *a, const void *b) 
{
    return (*(int *)a - *(int *)b);
}

int main() 
{
	TestBubbleSort();
	TestSelectionSort();
	TestInsertionSort();
	TestCountingSort();
    return 0;
}


void TestBubbleSort()
{
	int n = 5000;
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
	int n = 5000;
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
	int n = 5000;
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
    int n = 5000;
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
    printf("Insertion sort time: %f seconds\n", sort_time);
    printf("qsort time: %f seconds\n", qsort_time);
	printf("----------------------------------------------------\n\n");
	
    free(arr);
    free(arr_copy);
}


