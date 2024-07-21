#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdlib.h> /* exit */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */

#include "cbuffer.h"

#define NUMBER_OF_MESSEGES 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define MIN_VALUE_SEM 0
#define MAX_VALUE_SEM 15

void *Producer(void *buffer); 
void *Consumer(void *buffer); 

/* initialize global variables mutex and semaphore */
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER; 
sem_t g_semaphore_read;
sem_t g_semaphore_write;

int main() 
{
	pthread_t arr_producers[NUM_PRODUCERS] = {0};
	pthread_t arr_consumers[NUM_CONSUMERS] = {0};
	size_t i = 0;
	cbuffer_t *cbuffer = NULL;
	
    /* Initialize the semaphores */
    if (0 != sem_init(&g_semaphore_read, 0, MIN_VALUE_SEM)) 
    {
        printf("failed initializing a semaphore\n");
		exit(1);
    }
    if (0 != sem_init(&g_semaphore_write, 0, MAX_VALUE_SEM)) 
    {
        printf("failed initializing a semaphore\n");
		exit(1);
    }
    
	/* creating the cbuffer */
	cbuffer = CBuffCreate(sizeof(int) * MAX_VALUE_SEM);
	if (NULL == cbuffer)
	{
		printf("failed creating a cbuffer\n");
		exit(1);
	}
	
	/* creating all the producers threads */
    for (; i < NUM_PRODUCERS; ++i)
    {
        if (0 != pthread_create(&arr_producers[i], NULL, Producer, cbuffer)) 
        {
            fprintf(stderr, "Failed to create  producer thread %lu\n", i);
            exit(1);
        }
    }
    
    /* creating all the consumers threads */
    for (i = 0; i < NUM_CONSUMERS; ++i)
    {
        if (0 != pthread_create(&arr_consumers[i], NULL, Consumer, cbuffer)) 
        {
            fprintf(stderr, "Failed to create  consumer thread %lu\n", i);
            exit(1);
        }
        
    }
    
	/* joining all the producers threads */
	for (i = 0; i < NUM_PRODUCERS; ++i)
    {
        if (0 != pthread_join(arr_producers[i], NULL)) 
        {
            fprintf(stderr, "Failed to join thread %lu\n", i);
            exit(1);
        }
    }
    
    /* joining all the consumers threads */
	for (i = 0; i < NUM_CONSUMERS; ++i)
    {
        if (0 != pthread_join(arr_consumers[i], NULL)) 
        {
            fprintf(stderr, "Failed to join thread %lu\n", i);
            exit(1);
        }
    }
    
    sem_destroy(&g_semaphore_read);
    sem_destroy(&g_semaphore_write);
    
    pthread_mutex_destroy(&g_lock);
    
	CBuffDestroy(cbuffer);
	
    printf("All done!\n");
    
    return 0;
}


void *Producer(void *buffer) 
{
	cbuffer_t *cbuffer = (cbuffer_t*)buffer;
	int arr_inputs[NUMBER_OF_MESSEGES] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
    while (i < NUMBER_OF_MESSEGES)
    {
		/* decrement the write semaphore */
	   	if (-1 == sem_wait(&g_semaphore_write))
		{
			printf("faieled to decrement semaphore\n");
			exit(1);
		}
		
		/* thread is locking the mutex */
        if (0 != pthread_mutex_lock(&g_lock))
        {
        	printf("erroe while locking\n");
        	exit(1);
        }

		/* write to buffer */
		CBuffWrite(cbuffer, arr_inputs + i, sizeof(int));
       	
       	/* increment the read semaphore */
       	if (-1 == sem_post(&g_semaphore_read))
		{
			printf("faieled to increment semaphore\n");
			exit(1);
		}
		
       	++i;
    
        /* thread is unlocking the mutex */
        if (0 != pthread_mutex_unlock(&g_lock))
        {
        	printf("erroe while unlocking\n");
        	exit(1);
        }
    }
    
    return NULL;
}

void *Consumer(void *buffer) 
{
	cbuffer_t *cbuffer = (cbuffer_t*)buffer;
	int *element_value = (int*)malloc(sizeof(int));
	size_t i = 0;
	
	if (NULL == element_value)
	{
		printf("failed to allocate memory\n");
		exit(1);
	}

    while (i < NUMBER_OF_MESSEGES)
    {
		/* decrement the read semaphore */
	   	if (-1 == sem_wait(&g_semaphore_read))
		{
			printf("faieled to decrement semaphore\n");
			exit(1);
		}
		
		
		/* thread is locking the mutex */
        if (0 != pthread_mutex_lock(&g_lock))
        {
        	printf("erroe while locking\n");
        	exit(1);
        }
        
		/* read from buffer */
		CBuffRead(cbuffer, element_value, sizeof(int));
    	
    	/* increment the write semaphore */
	   	if (-1 == sem_post(&g_semaphore_write))
		{
			printf("faieled to decrement semaphore\n");
			exit(1);
		}
		
    	++i;
	    	
	    printf("value: %d\n", *element_value);
	    
        /* thread is unlocking the mutex */
        if (0 != pthread_mutex_unlock(&g_lock))
        {
        	printf("erroe while unlocking\n");
        	exit(1);
        }
    }
    
    free(element_value);

    return NULL;
}


