#include <stdio.h> /* printf */
#include <stdlib.h> /* exit sie_t */
#include <pthread.h> /* pthread_t pthread_create pthread_join */
#include <stdatomic.h> /* atomic type and functions */

#define NUMBER_OF_MESSEGES 5
#define MESSAGE_INITIAL_VALUE 0

void AcquireLock(atomic_flag* lock); 
void ReleaseLock(atomic_flag* lock);
void *Producer(void* arg); 
void *Consumer(void* arg); 

/* initialize global variables */
atomic_int g_message = ATOMIC_VAR_INIT(MESSAGE_INITIAL_VALUE);	
atomic_int g_done = ATOMIC_VAR_INIT(0);	 		   
atomic_flag g_lock = ATOMIC_FLAG_INIT;

int main() 
{
    pthread_t producer_thread = 0;
    pthread_t consumer_thread = 0;
    
	if (pthread_create(&producer_thread, NULL, Producer, NULL))
	{
		fprintf(stderr, "Failed to create producer_thread \n");
		exit(1);
	}
   
	if (pthread_create(&consumer_thread, NULL, Consumer, NULL))
	{
		fprintf(stderr, "Failed to create consumer_thread \n");
		exit(1);
	}
	
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    printf("All done!\n");
    return 0;
}

void AcquireLock(atomic_flag* lock) 
{
    while (atomic_flag_test_and_set(lock)) {}
}

void ReleaseLock(atomic_flag* lock) 
{
    atomic_flag_clear(lock);
}

void *Producer(void* arg) 
{
	int message_value = 0;
	int arr[NUMBER_OF_MESSEGES] = {1, 2, 3, 4, 5};
	size_t i = 0;
	
	(void)arg;
	
    while (i < NUMBER_OF_MESSEGES)
    {
        AcquireLock(&g_lock);
        
        message_value = atomic_load(&g_message);
        if (MESSAGE_INITIAL_VALUE == message_value) 
        {
        	atomic_store(&g_message, arr[i]);
        	++i;
        }
        
        ReleaseLock(&g_lock);
    }
    
    atomic_store(&g_done, 1);
    
    return NULL;
}

void *Consumer(void* arg) 
{
	int done_message = 0;
	int message_value = 0;
	
	(void)arg;
	
    while (!done_message)
    {
    	message_value = atomic_load(&g_message);
        if (MESSAGE_INITIAL_VALUE != message_value) 
        {
		    AcquireLock(&g_lock);
		    
			done_message = atomic_load(&g_done);
		    message_value = atomic_load(&g_message);
		    if (MESSAGE_INITIAL_VALUE != message_value) 
		    {
		    	atomic_store(&g_message, MESSAGE_INITIAL_VALUE);		
		    }

	        ReleaseLock(&g_lock);
	        printf("value: %d\n", message_value);
        }
    }

    return NULL;
}


