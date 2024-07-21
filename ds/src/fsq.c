#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <stdlib.h> /* exit */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */

#include "cbuffer.h" 
#include "fsq.h"

struct fsq
{
	size_t element_size;
	sem_t semaphore_write;
	sem_t semaphore_read;
	pthread_mutex_t lock_write;
	pthread_mutex_t lock_read;
	cbuffer_t *cbuffer;
};

fsq_t *FSQCreate(size_t capacity, size_t element_size)
{
	fsq_t *fsq = NULL;
	
	assert(0 < capacity);
	assert(0 < element_size);
	
	/* allocate memory for fsq struct */
	fsq = (fsq_t*)malloc(sizeof(fsq_t));
	if (NULL == fsq)
	{
		return NULL;
	}
	
	/* creating the cbuffer */
	fsq->cbuffer = CBuffCreate(capacity * element_size);
	if (NULL == fsq->cbuffer)
	{
		free(fsq);
		
		return NULL;
	}
	
	fsq->element_size = element_size;
	
	/* initializing the mutexes */
	if (0 != pthread_mutex_init(&fsq->lock_read, NULL))
	{
		CBuffDestroy(fsq->cbuffer);
 		free(fsq);
 		
 		return NULL;
	}
	if (0 != pthread_mutex_init(&fsq->lock_write, NULL))
	{
		CBuffDestroy(fsq->cbuffer);
		pthread_mutex_destroy(&fsq->lock_read);
 		free(fsq);
 		
 		return NULL;
	}

	/* initializing the read semaphore to start empty 0 */
	if (0 != sem_init(&(fsq->semaphore_read), 0, 0)) 
    {
 		CBuffDestroy(fsq->cbuffer);
 		pthread_mutex_destroy(&fsq->lock_read);
 		pthread_mutex_destroy(&fsq->lock_write);
 		free(fsq);
 		
 		return NULL;
    }
    /* initializing the write semaphore to start with the maximum capacity */
	if (0 != sem_init(&(fsq->semaphore_write), 0, capacity)) 
    {
 		CBuffDestroy(fsq->cbuffer);
 		pthread_mutex_destroy(&fsq->lock_read);
 		pthread_mutex_destroy(&fsq->lock_write);
 		free(fsq);
 		
 		return NULL;
    }
    
    return fsq;
}

void FSQDestroy(fsq_t *queue)
{
	assert(queue);
	
	CBuffDestroy(queue->cbuffer);
	
	sem_destroy(&queue->semaphore_read);
    sem_destroy(&queue->semaphore_write);
    
    pthread_mutex_destroy(&queue->lock_read);
    pthread_mutex_destroy(&queue->lock_write);
    
 	free(queue);
}

int FSQEnqueue(fsq_t *queue, void *data)
{
	assert(queue);
	
	/* decrement and wait for the wrtie semaphore to be available */
   	if (-1 == sem_wait(&queue->semaphore_write))
	{
		return 1;
	}
	
	/* thread is locking the write mutex */
    if (0 != pthread_mutex_lock(&queue->lock_write))
    {
    	return 1;
    }

	/* write to buffer */
	CBuffWrite(queue->cbuffer, data, queue->element_size);
   	
    /* thread is unlocking the mutex */
    if (0 != pthread_mutex_unlock(&queue->lock_write))
    {
    	return 1;
    }

   	/* increment the read semaphore */
   	if (-1 == sem_post(&queue->semaphore_read))
	{
		return 1;
	}
	
	return 0;
}

void FSQDequeue(fsq_t *queue, void *dest)
{	
	assert(queue);
	assert(dest);
	
	/* decrement the read semaphore */
   	if (-1 == sem_wait(&queue->semaphore_read))
	{
		return;
	}
	
	/* thread is locking the mutex */
    if (0 != pthread_mutex_lock(&queue->lock_read))
    {
    	return;
    }
    
	/* read from buffer */
	CBuffRead(queue->cbuffer, dest, queue->element_size);
	
    /* thread is unlocking the mutex */
    if (0 != pthread_mutex_unlock(&queue->lock_read))
    {
    	return;
    }

	/* increment the write semaphore */
   	if (-1 == sem_post(&queue->semaphore_write))
	{
		return;
	}
	
	return;
}
