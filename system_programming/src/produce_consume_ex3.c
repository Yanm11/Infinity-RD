#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdatomic.h> /* atomic type and functions */
#include <stdlib.h> /* exit */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */

#include "sllist.h"

#define NUMBER_OF_MESSEGES 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3
#define STARTING_VALUE_SEM 0

void *Producer(void *list); 
void *Consumer(void *list); 

/* initialize global variables mutex and semaphore */
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER; 
sem_t g_semaphore_thread_2_main;

int main() 
{
	pthread_t arr_producers[NUM_PRODUCERS] = {0};
	pthread_t arr_consumers[NUM_CONSUMERS] = {0};
	size_t i = 0;
	sllist_t *list = NULL;
	
    /* Initialize the semaphore */
    if (0 != sem_init(&g_semaphore_thread_2_main, 0, STARTING_VALUE_SEM)) 
    {
        printf("failed initializing a semaphore\n");
		exit(1);
    }
    
	/* creating the list */
	list = SllistCreate();
	if (NULL == list)
	{
		printf("failed creating a list\n");
		exit(1);
	}
	
	/* creating all the producers threads */
    for (; i < NUM_PRODUCERS; ++i)
    {
        if (0 != pthread_create(&arr_producers[i], NULL, Producer, list)) 
        {
            fprintf(stderr, "Failed to create  producer thread %lu\n", i);
            exit(1);
        }
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
    
    sem_destroy(&g_semaphore_thread_2_main);
    
	SllistDestroy(list);
	
    printf("All done!\n");
    
    return 0;
}


void *Producer(void* list) 
{
	sllist_t *sllist = (sllist_t*)list;
	sllist_iter_t iter = NULL;
	int *element_value = NULL;
	int arr_inputs[NUMBER_OF_MESSEGES] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
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
       	
       	/* increment the semaphore */
       	if (-1 == sem_post(&g_semaphore_thread_2_main))
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

void *Consumer(void* list) 
{
	sllist_t *sllist = (sllist_t*)list;
	sllist_iter_t iter = NULL;
	int *element_value = NULL;
	size_t i = 0;

    while (i < NUMBER_OF_MESSEGES)
    {
    	/* decrement the semaphore */
	   	if (-1 == sem_wait(&g_semaphore_thread_2_main))
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
		
		/* read the value, remove it from rhe list, print it and free it */
		iter = SllistBegin(sllist);
    	element_value = (int*)SllistGetData(iter);
    	SllistRemove(iter);
    
    	++i;
		    
	    printf("value: %d\n", *element_value);
	    free(element_value);
	    
        /* thread is unlocking the mutex */
		if (0 != pthread_mutex_unlock(&g_lock))
		{
			printf("erroe while unlocking\n");
			exit(1);
		}
    }

    return NULL;
}


