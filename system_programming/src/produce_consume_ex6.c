#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdlib.h> /* exit */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */

#include "sllist.h"

#define NUMBER_OF_MESSEGES 5
#define NUM_CONSUMERS 3
#define STARTING_VALUE_SEM 0

void *Producer(void *list); 
void *Consumer(void *list); 

/* initialize global variables */
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t g_condition = PTHREAD_COND_INITIALIZER;
sem_t g_semaphore;

int main() 
{
	pthread_t producer_thread = 0;
	pthread_t arr_consumers[NUM_CONSUMERS] = {0};
	size_t i = 0;
	
	/* creating the list */
	sllist_t *list = SllistCreate();
	if (NULL == list)
	{
		printf("failed creating a list\n");
		exit(1);
	}
	
	/* Initialize the semaphore */
    if (0 != sem_init(&g_semaphore, 0, STARTING_VALUE_SEM)) 
    {
        printf("failed initializing a semaphore\n");
		exit(1);
    }
	
	/* creating the producer thread */
    if (0 != pthread_create(&producer_thread, NULL, Producer, list)) 
    {
        fprintf(stderr, "Failed to create  producer thread %lu\n", i);
        exit(1);
    }
    
    /* creating all the consumers threads */
    for (i = 0; i < NUM_CONSUMERS; ++i)
    {
        if (0 != pthread_create(&arr_consumers[i], NULL, Consumer, list)) 
        {
            fprintf(stderr, "Failed to create  consumer thread %lu\n", i);
            exit(1);
        }   
    }
    
	/* joining the producer thread */
    if (0 != pthread_join(producer_thread, NULL)) 
    {
        fprintf(stderr, "Failed to join thread %lu\n", i);
        exit(1);
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
    
	SllistDestroy(list);
	
    printf("All done!\n");
    
    return 0;
}

void *Producer(void *list) 
{
	sllist_t *sllist = (sllist_t*)list;
	sllist_iter_t iter = NULL;
	int *element_value = NULL;
	int arr_inputs[NUMBER_OF_MESSEGES] = {1, 2, 3, 4, 5};
	int sem_value = 0;
	size_t i = 0;
	size_t j = 0;

    while (i < NUMBER_OF_MESSEGES)
    {
		/* thread is locking the mutex */
        if (0 != pthread_mutex_lock(&g_lock))
        {
        	printf("erroe while locking\n");
        	exit(1);
        }
		
		/* assigning addresses to save the data in them */
    	element_value = (int*)malloc(sizeof(int));
        if (NULL == element_value)
		{
			printf("malloc failed\n");
			exit(1);
		}
		
        *element_value = arr_inputs[i];

		/* insert and checking for errors */
		iter = SllistInsertBefore(sllist, element_value, SllistEnd(sllist));
       	if (SllistIterIsEqual(iter, SllistEnd(sllist)))
       	{
       		printf("faieled to insert\n");
       		exit(1);
       	}
       	
       	++i;
       	
        /* Reset the semaphore to NUM_CONSUMERS */
        j = 0;
        while (NUM_CONSUMERS > j) 
        {
			/* increment the semaphore to indicate a message was written */
			if (-1 == sem_post(&g_semaphore))
			{
				printf("faieled to decrement the semaphore\n");
				exit(1);
			}
			
           ++j;
        }

        /* Wait for all consumers to consume the message */
        sem_value = 1;
        while (0 != sem_value) 
        {
            pthread_cond_wait(&g_condition, &g_lock);
            
            /* send a signal to the consumers to read */
   			pthread_cond_broadcast(&g_condition);
            
            sem_getvalue(&g_semaphore, &sem_value);
        }

        /* thread is unlocking the mutex */
        if (0 != pthread_mutex_unlock(&g_lock))
        {
        	printf("erroe while unlocking\n");
        	exit(1);
        }
        
        free(element_value);
    }
    
    return NULL;
}

void *Consumer(void *list) 
{
	sllist_t *sllist = (sllist_t*)list;
	sllist_iter_t iter = NULL;
	int *element_value = NULL;
	size_t i = 0;
	static size_t counter = 0;
	
    while (i < NUMBER_OF_MESSEGES)
    {    
    	/* decrement the semaphore to make sure it is not empty */
		if (-1 == sem_wait(&g_semaphore))
		{
			printf("faieled to decrement the semaphore\n");
			exit(1);
		}

	    /* thread is locking the mutex */
        if (0 != pthread_mutex_lock(&g_lock))
        {
        	printf("erroe while locking\n");
        	exit(1);
        }

		/* read the element and print it */
		iter = SllistBegin(sllist);
    	element_value = (int*)SllistGetData(iter);
		
    	++i; 
			
	    printf("Thread id: %ld, value: %d\n", pthread_self(), *element_value);
	    
		
        /* Wait for producer to create new message or if all read sent signal */
        ++counter;
        if (NUM_CONSUMERS == counter)
        {
        	counter = 0;
        	pthread_cond_broadcast(&g_condition);
        }

	    pthread_cond_wait(&g_condition, &g_lock);

        /* thread is unlocking the mutex */
        if (0 != pthread_mutex_unlock(&g_lock))
        {
        	printf("erroe while unlocking\n");
        	exit(1);
        }
    }
    
    return NULL;
}


