#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <unistd.h> /* sleep */
#include <pthread.h> /* pthread_create pthread_detach */

#define SIZE_OF_ARRAY 100000

void *StartRoutine(void *i);

static int arr[SIZE_OF_ARRAY] = {0};

int main(void)
{
    pthread_t arr_threads[SIZE_OF_ARRAY] = {0};
    size_t i = 0;
    
    for (; i < SIZE_OF_ARRAY; ++i)
    {
    	size_t *index = (size_t*)malloc(sizeof(size_t));
    	*index = i;
		pthread_create(&arr_threads[i], NULL, &StartRoutine, index);
		pthread_detach(arr_threads[i]);
    }
    
    sleep(2);
    
    for (i = 0; i < SIZE_OF_ARRAY; ++i)
    {
    	if (arr[i] != (int)i)
    	{
    		printf("index not equal\ni: %ld\n", i);
    	}
    }
    
   return 0;
}




void *StartRoutine(void *i)
{
	arr[*(size_t*)i] = *(size_t*)i; 
	free(i);
	
	return NULL;
}









