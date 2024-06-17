#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

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

#endif /*__SORT_H__*/ 
