#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* perror printf sprintf */
#include <stdlib.h> /* malloc free EXIT_FAILURE exit */
#include <errno.h>
#include <assert.h> /* assert */
#include <signal.h> /* sigemptyset sigaction */
#include <pthread.h> /* pthread_create pthread_detach */
#include <stdatomic.h> /* atomic type and functions */
#include <semaphore.h> /* sem_wait sem_post sem_init sem_destroy */
#include <unistd.h>	/* fork exec */
#include <time.h> /* time_t */
#include <sys/wait.h> /* waitpd pid_t */
#include <sys/ipc.h> /* ftok */
#include <sys/types.h> /* key_t */
#include <sys/shm.h> /* shmget shmat shmdt hmctr*/
#include <sys/stat.h> /* S_IRWXU */
#include <fcntl.h> /* S_IRWXU */

#include <uid.h>
#include "hscheduler.h"
#include "imortal.h"

#define SEM_NAME "watchdog"
#define STARTING_VALUE_SEM 0
#define ENV_NAME "WD_PID"
#define SEM_PERMITIONS (S_IRWXU | S_IRWXG | S_IRWXO)

void *Imortal(void *imortal_ptr);
shared_data_t *CreateSharedData(size_t interval,
								size_t num_of_rep,
								char **args,
								int shmid);
void DestroySharedData(int shmid);
void HandlerSig1(int sig);
int CreateShmid(void);
pid_t CreateChildProcess(char *args[]);
char **GetArgs(shared_data_t *shared_data);
void SentSignal(void *task_data_ptr);
void SetEnvVar(const char *name, const char *value);
void SetEnvVarInt(const char *name, int value); 
void HandlerSig2(int sig);

int main(int argc, char *argv[])
{
	int shmid = atoi(argv[1]);
	shared_data_t *shared_data = NULL;
	hscheduler_t *scheduler = HSchedulerCreate();
	task_data_t *task_data_ptr = (task_data_t*)malloc(sizeof(task_data_t));
	struct sigaction sa = {0};
	struct sigaction sa_2 = {0};

	/* initializing of shared memory */
	shared_data = (shared_data_t *)shmat(shmid, NULL, 0);
    if ((void*)-1 == (void*)shared_data) 
	{
        perror("shmat");
        exit(1);
    }

	/* handle SIGUSR1 */
	sa.sa_handler = HandlerSig1;
	sa.sa_flags = 0; 
	sigemptyset(&sa.sa_mask); /* empty mask */
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	DestroySharedData(shmid);
		printf("failed to create sigaction\n");
		
    	return -1;
	}
		/* handle SIGUSR2 */
	sa_2.sa_handler = HandlerSig2;
	sa_2.sa_flags = 0; 
	sigemptyset(&sa_2.sa_mask); /* empty mask */
    if (sigaction(SIGUSR2, &sa_2, NULL) == -1)
    {
    	DestroySharedData(shmid);
		printf("failed to create sigaction\n");
		
    	return -1;
	}

	/* Initialize the semaphore to synchrnize between wd and thread to zero */
	g_semaphore_thread_2_wd = sem_open(SEM_NAME, O_CREAT,
									   SEM_PERMITIONS, STARTING_VALUE_SEM);
	if (SEM_FAILED == g_semaphore_thread_2_wd)
	{
		perror("creating semaphore failed");
		exit(EXIT_FAILURE);
	}

	/* releasing the lock for imortal to continue */
	if (-1 == sem_post(g_semaphore_thread_2_wd))
	{
		printf("faieled to increment semaphore\n");
		
		return -1;
	}

	SetEnvVarInt(ENV_NAME, getpid());

	/* assigning all the nececary variable to task_data */
	task_data_ptr->pid = getppid();
	task_data_ptr->shared_data = shared_data;
	task_data_ptr->word = "child";
	task_data_ptr->args = (argv + 2);
	task_data_ptr->scheduler = scheduler;
	printf("shared data->filename: %d\n", (shared_data->shmid));
	HSchedulerAdd(scheduler,time(NULL) + shared_data->interval_seconds +1,
				  shared_data->interval_seconds, SentSignal, task_data_ptr);
	
	HSchedulerRun(scheduler);

	HSchedulerDestroy(scheduler);
	
	sem_post(g_semaphore_thread_2_wd);
	
	free(task_data_ptr);
	if (unsetenv(ENV_NAME) != 0) 
	{
		perror("unsetenv");
		return 1;
	}

	return 0;
}


/*************************** HELPER FUNCTION ***************************/