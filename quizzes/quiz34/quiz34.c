#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <assert.h> /* assert */

int FindCharInArray(char arr[], size_t size, char target)
{
    size_t i = 0;
    int is_char = 1;

    assert(arr);

    while (i < size)
    {
        is_char = is_char * (target - arr[i]);
        ++i;
    }

    return !is_char;
}

char *Reverse(char *str, size_t to)
{
    char *end = str + to - 1;
    char *start = str;

    while (start <= end)
    {
        char tmp = *start;
        *start = *end;
        *end = tmp;

        --end;
        ++start;
    }

    return str;
}

void ShiftArray(char arr[], size_t size, size_t n_shifts)
{
    assert(arr);

    n_shifts = n_shifts % size;

    /* reverse the entire string */
    Reverse(arr, size);

    /* reverse the string from the start to the n_shift element */
    Reverse(arr, n_shifts);

    /* reverse the string from the n_Shift element tot the end */
    Reverse(arr + n_shifts, size - n_shifts);
}


int main(void)
{
    char target = 'a';
    char arr[] = {'a','b','c','d','e','f','g'};
    size_t size = sizeof(arr) / sizeof(char);
    size_t i = 0;

    if (FindCharInArray(arr, size, target))
    {
        printf("found char!!\n");
    }
    else
    {
        printf("could not find char;(\n");
    }

    ShiftArray(arr, size, 5);


    printf("[");
    for (; i < size; ++i)
    {
        printf(",%c", arr[i]);
    }
    printf("]\n");

    return 0;
}