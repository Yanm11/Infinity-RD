#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <assert.h>

void Swap(char *x, char *y) 
{
    char temp = *x;
    *x = *y;
    *y = temp;
}

void Permute(char *str, size_t start, size_t end) 
{
    size_t i = 0;

    assert(str);

    if (start == end) 
    {
        printf("%s ", str);

        return;
    }

    
    for (i = start; i <= end; ++i)
    {
        Swap((str + start), (str + i));
        Permute(str, start + 1, end);
        Swap((str + start), (str + i));
    }

}

int main() 
{
    char str[100] ={0};
    int n = 0;

    printf("Enter a string: ");
    scanf("%s", str);

    n = strlen(str);
    printf("The permutations of string \"%s\": ", str);
    Permute(str, 0, n - 1);
    printf("\n");

    return 0;
}