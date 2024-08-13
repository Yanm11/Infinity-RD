#include <stdio.h>
#include <stddef.h>
#include <assert.h> 

/* Function to find the number of rotations in a circularly sorted array */
size_t FindRotations(int arr[], size_t size) 
{
    size_t low = 0;
    size_t high = size - 1;
    size_t mid = 0;

    assert(arr);

    /* If the array is already sorted */
    if (arr[low] <= arr[high])
    {
        return low;
    }

    while (low <= high) 
    {
        mid = (low + high) / 2;
        size_t next = (mid + 1) % size;
        size_t prev = (mid - 1 + size) % size; 

        /* Check if mid is the smallest element */
        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev]) 
        {
            return (size - mid);
        }

        /* Decide whether to go to the left half or the right half */
        else if (arr[mid] <= arr[high]) 
        {
            high = mid - 1;
        }
        else if (arr[mid] >= arr[low]) 
        {
            low = mid + 1;
        }
    }
}

int main(void) 
{
    int arr[] = {7, 8, 11,2,3,4};
    int n = sizeof(arr) / sizeof(arr[0]);

    int rotations = FindRotations(arr, n);
    printf("The array is rotated %d times\n", rotations);

    return 0;
}
