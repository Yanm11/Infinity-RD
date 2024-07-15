#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <pthread.h> /* pthread_create pthread_detach */
#include <errno.h>

#define NUM_THREADS 4
#define INPUT 10000000000
#define CHUNK_SIZE (INPUT / NUM_THREADS)

void *StartRoutine(void *i);

int main(void)
{
    pthread_t arr_threads[NUM_THREADS] = {0};
    size_t i = 0, total_sum = 0;

    for (i = 0; i < NUM_THREADS; ++i)
    {
        size_t *index = (size_t*)malloc(sizeof(size_t));
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
        size_t *thread_sum = NULL;
        if (pthread_join(arr_threads[i], (void**)&thread_sum) != 0) 
        {
            fprintf(stderr, "Failed to join thread %lu\n", i);
            exit(1);
        }
        
        if (thread_sum != NULL) 
        {
            total_sum += *thread_sum;
            free(thread_sum);
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
    size_t j = 0;
    size_t *sum_of_divisors = malloc(sizeof(size_t));
    
    if (sum_of_divisors == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory in thread\n");
        free(i);
        return NULL;
    }
    
    *sum_of_divisors = 0;
    
    for (j = start; j <= end && j <= INPUT; ++j)
    {
        if (INPUT % j == 0)
        {
            *sum_of_divisors += j;
        }
    }
    
    free(i);
    
    return sum_of_divisors;
}
