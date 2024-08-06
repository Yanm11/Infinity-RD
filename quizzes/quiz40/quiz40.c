#include <stddef.h> /* size_t */
#include <stdio.h> /* printf */

#define NUMBER_BITS 32

size_t MaxConsecutive1s(unsigned int n)
{
    size_t max_consecutive = 0;
    size_t new_consecutive = 0;
    size_t i = 0;
    unsigned char binary = 0;

    for(; i < NUMBER_BITS; ++i)
    {
        binary = (n >> i) & 1;
        if ( 0 == binary)
        {
            new_consecutive = 0;
        }
        else
        {
            ++new_consecutive;
        }

        if (new_consecutive > max_consecutive)
        {
            max_consecutive = new_consecutive;
        }
    }

    return max_consecutive;
}

int main(void)
{
    unsigned int x = 1;

    printf("max consecutive 1s is: %d\n", MaxConsecutive1s(x));

    return 0;
}