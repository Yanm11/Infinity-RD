#include <string.h> /* strlen */
#include <stdio.h> /* printf */
#include <assert.h> /* assert*/ 
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

ssize_t SearchForElement(int arr[], size_t size, int target);
int InRange(int left, int right, int target);

int main(void)
{
	int arr[] = {7,1,2,3,4,5};
	int target = 1;
    size_t size = sizeof(arr) / sizeof(int);

	printf("num: %d is in index: %d\n", target,
                                        SearchForElement(arr,
                                                         size,
                                                         target));
	
	return 0;
}

ssize_t SearchForElement(int arr[], size_t size, int target)
{
    ssize_t start = 0;
    ssize_t end = size - 1;
    size_t middle = end / 2;

    assert(arr);

    while (start != end - 1)
    {
        if(InRange(arr[start], arr[middle], target))
        {
            end = middle;
        }
        else if (arr[end] >= target)
        {
            start = middle;
        }
        else
        {
            /* will return -1 to indicate that target is not in arr */
            start = -1;
            end = 0;
        }

        middle = (end - start) / 2 + start;
    }

    if (arr[end] == target)
    {
        return end;
    }

    return start;
}

int InRange(int left, int right, int target)
{
    return ((left <= target) && (right >= target));
}