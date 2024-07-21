#include <stdio.h> /* printf */
#include <stddef.h> /* size_t */
#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdlib.h> /* exit */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */

#include "fsq.h"

#define NUMBER_OF_MESSEGES 5
#define NUM_PRODUCERS 3
#define NUM_CONSUMERS 3

void *Producer(void *queue); 
void *Consumer(void *queue); 

int main() 
{
	pthread_t arr_producers[NUM_PRODUCERS] = {0};
	pthread_t arr_consumers[NUM_CONSUMERS] = {0};
	size_t i = 0;
	size_t capacity = 15;
	
   	/* creating the fsq */
	fsq_t *fsq = FSQCreate(capacity, sizeof(int));
	if (NULL == fsq)
	{
		printf("failed creating a cbuffer\n");
		exit(1);
	}
	
	/* creating all the producers threads */
    for (; i < NUM_PRODUCERS; ++i)
    {
        if (0 != pthread_create(&arr_producers[i], NULL, Producer, fsq)) 
        {
            fprintf(stderr, "Failed to create  producer thread %lu\n", i);
            exit(1);
        }
    }
    
    /* creating all the consumers threads */
    for (i = 0; i < NUM_CONSUMERS; ++i)
    {
        if (0 != pthread_create(&arr_consumers[i], NULL, Consumer, fsq)) 
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
    
	FSQDestroy(fsq);
	
    printf("All done!\n");
    
    return 0;
}


void *Producer(void *queue) 
{
	fsq_t *fsq = (fsq_t*)queue;
	int arr_inputs[NUMBER_OF_MESSEGES] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
    while (i < NUMBER_OF_MESSEGES)
    {
		/* write to buffer */
		if (0 != FSQEnqueue(fsq, arr_inputs + i))
		{
			printf("failed to enqueue\n");
			exit(1);
		}
		
       	++i;
    }
    
    return NULL;
}

void *Consumer(void *queue) 
{
	fsq_t *fsq = (fsq_t*)queue;
	int *element_value = (int*)malloc(sizeof(int));
	size_t i = 0;

	if (NULL == element_value)
	{
		printf("failed to allocate\n");
		exit(1);
	}
	
    while (i < NUMBER_OF_MESSEGES)
    {
		/* read from buffer */
		FSQDequeue(fsq, element_value);
		
		if (NULL == element_value)
		{
			printf("failed to dequeue\n");
			exit(1);
		}
		
	    printf("value: %d\n", *element_value);

    	++i;
    }

	free(element_value);
	
    return NULL;
}


