#include <stdio.h> /* printf */
#include <omp.h>

#define INPUT 10000000000


void *StartRoutine(void *i);

int main(void)
{
    size_t i = 0;
    size_t total_sum = 0;
    
	#pragma omp parallel for
    for (i = 1; i <= INPUT; ++i)
    {
        if (INPUT % i == 0)
        {
        	total_sum += i;
        }
    }
    
    printf("Total sum of divisors: %lu\n", total_sum);
    return 0;
}


