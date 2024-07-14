#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define NUM_THREADS 32000
#define CHUNK_SIZE 100

void *StartRoutine(void *i);
static size_t g_input = 24522146392;

int main(void)
{
    pthread_t arr_threads[NUM_THREADS];
    size_t i, total_sum = 0;
    
    for (i = 0; i < NUM_THREADS; ++i)
    {
        size_t *index = malloc(sizeof(size_t));
        if (index == NULL) 
        {
            fprintf(stderr, "Failed to allocate memory for thread argument\n");
            exit(1);
        }
        *index = (i + 1) * CHUNK_SIZE;
        if (pthread_create(&arr_threads[i], NULL, StartRoutine, index) != 0) 
        {
            fprintf(stderr, "Failed to create thread %lu\n", i);
            free(index);
            exit(1);
        }
    }
    
    for (i = 0; i < NUM_THREADS; ++i)
    {
        size_t *thread_sum;
        if (pthread_join(arr_threads[i], (void**)&thread_sum) != 0) 
        {
            fprintf(stderr, "Failed to join thread %lu\n", i);
            exit(1);
        }
        if (thread_sum != NULL) 
        {
            total_sum += *thread_sum;
        }
    }
    
    printf("Total sum of divisors: %lu\n", total_sum);
    return 0;
}

void *StartRoutine(void *i)
{
    size_t number = *(size_t*)i;
    size_t start = number - CHUNK_SIZE + 1;
    size_t end = number;
    size_t j;
    size_t *sum_of_divisors = malloc(sizeof(size_t));
    
    if (sum_of_divisors == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory in thread\n");
        free(i);
        return NULL;
    }
    
    *sum_of_divisors = 0;
    
    for (j = start; j <= end && j <= g_input; ++j)
    {
        if (g_input % j == 0)
        {
            *sum_of_divisors += j;
        }
    }
    
    free(i);
    return sum_of_divisors;
}
