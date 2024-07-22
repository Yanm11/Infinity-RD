#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Global variable */
int global_var = 0;

/* Thread local storage (TLS) */
__thread int thread_local_var = 0;

/* Function to be executed by each thread */
void* thread_function(void* arg) {
    int stack_var = 0;
    int* heap_var1 = (int*) malloc(sizeof(int));
    int* heap_var2 = (int*) malloc(sizeof(int) * 10);

    printf("Thread ID: %lu\n", pthread_self());
    printf("  Address of stack variable: %p\n", (void*)&stack_var);
    printf("  Address of heap variable 1: %p\n", (void*)heap_var1);
    printf("  Address of heap variable 2: %p\n", (void*)heap_var2);
    printf("  Address of thread local variable: %p\n", (void*)&thread_local_var);

    return NULL;
}

void MapAddressSpace(void)
{
	char input[256] = {0};
	char dest[100] = {0};
	FILE *fp = NULL;
	sprintf(dest, "/proc/%d/maps", getpid());
	fp = fopen(dest, "r");
	if(!fp)
	{
		perror("fopen\n");
	}	
	
	while(fgets(input, 256, fp))
	{
		printf("%s", input);
	}
	
	fclose(fp);
}

int main() {
    pthread_t threads[2];
    int i;

    printf("Address of global variable: %p\n", (void*)&global_var);

    for (i = 0; i < 2; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
	MapAddressSpace();
    return 0;
}




