#include <stdio.h> /* printf */
#include <assert.h> /* assert*/ 
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

ssize_t SearchForElement(int arr[], size_t size, int target);
int InRange(int left, int right, int target);

int main(void)
{
	int arr[] = {7,8,9,10,11,12,1,2,3,4,5};
	int target = 12;
    size_t size = sizeof(arr) / sizeof(int);

	printf("num: %d is in index: %ld\n", target,
                                        SearchForElement(arr,
                                                         size,
                                                         target));
	
	return 0;
}

ssize_t SearchForElement(int arr[], size_t size, int target)
{
    size_t start = 0;
    size_t end = size - 1;
    size_t middle = end / 2;

    assert(arr);

    while (start <= end)
    {
        middle = (end - start) / 2 + start;
       
        if (arr[middle] == target)
        {
            return middle;
        }
        /* if left half is sorted */
        if (arr[start] <= arr[middle])
        {
            if(InRange(arr[start], arr[middle], target))
            {
                end = middle - 1;
            }
            else
            {
                start = middle + 1;
            }
        }
        /* if right half is sorted */
        else
        {
            if(InRange(arr[middle], arr[end], target))
            {
                start = middle + 1;
            }
            else
            {
                end = middle - 1;
            }
        }

    }

    return -1;
}

int InRange(int left, int right, int target)
{
    return ((left <= target) && (right >= target));
}