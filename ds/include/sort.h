#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

/*
Description: typedef to pointer function that compares two arguments
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching:
    positive if first argument is larger,
    zero if they equal
    negative if the second argument is larger.
*/
typedef int (*sort_compare_func_t)(const void*, const void*);

/*
BubbleSort
description: sort an array in place usuing bubble sort algorithm
input: compare function and an array of ints and it size
return: nothing
time complexity: O(n^2)
space complexity: O(n^2)
*/
void BubbleSort(int arr[], size_t size, sort_compare_func_t cmp_func);   

/*
SelectionSort
description: sort an array in place using selection sort algorithm
input: compare function and an array of ints and it size
return: nothing
time complexity: O(n^2)
space complexity: O(n^2)
*/
void SelectionSort(int arr[], size_t size, sort_compare_func_t cmp_func); 

/*
InsertionSort
description: sort an array in place using Insertion sort algorithm
input: compare function and an array of ints and it size
return: nothing
time complexity: O(n^2)
space complexity: O(n^2)
*/
void InsertionSort(int arr[], size_t size, sort_compare_func_t cmp_func); 

/*
CountingSort
description: sort an array in place using count sort algorithm
input: an array of ints and it size
return: nothing
time complexity: O(n^2)
space complexity: O(n^2)
*/
void CountingSort(int arr[], size_t size); 

/*
RadixSort
description: sort an array in place using count sort algorithm
input: an array of ints and it size
return: nothing
time complexity: O(n^2)
space complexity: O(n^2)
*/
void RadixSort(int arr[], size_t size); 

/*
BinarySearchIter
description: searches the array for an element
input: an array of ints and it size and element to search for
return: the index if found -1 if not
time complexity: O(log n)
space complexity: O(1)
*/
ssize_t BinarySearchIter(int *arr, size_t size, int element);

/*
BinarySearchRecursion
description: searches the array for an element
input: an array of ints and it size and element to search for
return: the index if found -1 if not
time complexity: O(log n)
space complexity: O(1)
*/
ssize_t BinarySearchRecursion(int *arr, size_t size, int element);

/*
BinarySearchRecursion
description: sorting the array with merge sort algorithm
input: an array of ints and it size 
return: 0 if suuccesful or -1 if failed because of malloc issues
time complexity: O(n log n)
space complexity: O(1)
*/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*
QSort
description: searches the array for an element
input: an array of ints and it size and element to search for
return: the index if found -1 if not
time complexity: O(n log n)
space complexity: O(1)
*/
void QSort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));
                  
#endif /*__SORT_H__*/ 
