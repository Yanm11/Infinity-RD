#include <stdio.h> /* printf */
#include <assert.h> /* assert*/ 
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc */

int FindKMinElement(int arr[], size_t size, int k);
size_t FindMin(int arr[], size_t size);
void Swap(int *a, int *b);
void PrintArr(int arr[], size_t size);



int main(void)
{
	int arr[] = {1,5,8,9,7,4,6,2,3,0};
	int k = 1;
    size_t size = sizeof(arr) / sizeof(int);
    int min = FindKMinElement(arr, size, k);

	printf("the %d smallest element is: %d\n", k, min);
	
	return 0;
}

int FindKMinElement(int arr[], size_t size, int k)
{
    size_t i = 0;
    size_t min_i = 0;
    int *new_arr = (int*)malloc(sizeof(int) * size);
    int *start_new_arr = new_arr;

    assert(arr);

    for (; i < size; ++i)
    {
        *new_arr = arr[i];
        ++new_arr;
    }

    for (i = 0; i < k; ++i)
    {
        min_i = FindMin(start_new_arr + i, size - i);
        Swap(start_new_arr + i, start_new_arr + min_i + i);
    }

    PrintArr(start_new_arr, size);

    return *(start_new_arr + i - 1);
}

size_t FindMin(int arr[], size_t size)
{
    size_t i = 0;
    size_t min = arr[0];
    size_t min_i = 0;

    for (; i < size; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
            min_i = i;
        }
    }

    return min_i;
}

void Swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void PrintArr(int arr[], size_t size)
{
    size_t i = 0;

    printf("[");

    for (; i < size; ++i)
    {
        printf(",%d", arr[i]);
    }

    printf("]\n");
}