#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* perror printf sprintf */
#include <stdlib.h> /* malloc free EXIT_FAILURE exit */
#include <errno.h>
#include <assert.h> /* assert */
#include <signal.h> /* sigemptyset sigaction */
#include <pthread.h> /* pthread_create pthread_detach */
#include <stdatomic.h> /* atomic type and functions */
#include <semaphore.h>
#include <unistd.h>	/* fork exec */
#include <time.h> /* time_t */
#include <sys/wait.h> /* waitpd pid_t */
#include <sys/ipc.h> /* ftok */
#include <sys/types.h> /* key_t */
#include <sys/shm.h> /* shmget shmat shmdt hmctr*/
#include <sys/stat.h> /* S_IRWXU */
#include <fcntl.h> /* S_IRWXU */

#include "imortal.h"

void *Imortal(void *imortal_ptr);
shared_data_t *CreateSharedData(size_t interval,
								size_t num_of_rep,
								char **args,
								int shmid);
void DestroySharedData(int shmid);
void Handler(int sig);
int CreateShmid(void);
void Loop(pid_t pid, shared_data_t *shared_data, char *word, char *args[]);
pid_t CreateChildProcess(char *args[]);
char **GetArgs(shared_data_t *shared_data);

int main(int argc, char *argv[])
{
	int shmid = atoi(argv[1]);
	shared_data_t *shared_data = NULL;

	struct sigaction sa = {0};
	sa.sa_handler = Handler;
	sa.sa_flags = 0; 
	sigemptyset(&sa.sa_mask); /* empty mask */

	/* initializing of shared memory */
	shared_data = (shared_data_t *)shmat(shmid, NULL, 0);
    if ((void*)-1 == (void*)shared_data) 
	{
        perror("shmat");
        exit(1);
    }

	/* handle SIGUSR1 */
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	DestroySharedData(shmid);
		printf("failed to create sigaction\n");
		
    	return -1;
	}
	if (kill(getppid(), SIGUSR1) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}

	printf("pid: %d\n", getpid());
	
	Loop(getppid(), shared_data, "child", GetArgs(shared_data));


	return 0;
}


/*************************** HELPER FUNCTION ***************************/