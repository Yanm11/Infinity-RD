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

#include "imortal.h"

#define STARTING_VALUE_SEM 0
#define PATH_TO_WD "./watchdog"
#define PROJECT_ID 11

struct shared_data
{
	size_t reps;
	time_t interval_seconds;
	int shmid;
	char **file_name_and_commands;
};

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

static sem_t g_semaphore;
static atomic_int g_count = ATOMIC_VAR_INIT(0);


/*************************** API FUNCTIONS ***************************/


int MMI(size_t interval_in_seconds, size_t repetitions, char **argv)
{
	int shmid = 0;
	shared_data_t *shared_data = NULL;
	pthread_t imortal_thread = 0;
	
	struct sigaction sa = {0};
	sa.sa_handler = Handler;
	sa.sa_flags = 0; 
	sigemptyset(&sa.sa_mask); /* empty mask */

	

	/* initializing shared memeory ID*/
	shmid = CreateShmid();
	if (-1 == shmid)
	{
		printf("failed to create shmid\n");

		return -1;
	}

	/* initializing of shared memory */
	shared_data = CreateSharedData(interval_in_seconds,
								   repetitions,
								   argv,
								   shmid);
	
	if (NULL == shared_data)
	{
		printf("failed to create shared_data\n");

		return -1;
	}

	/* handle SIGUSR1 */
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	DestroySharedData(shmid);
		printf("failed to create sigaction\n");
		
    	return -1;
	}
	
    /* Initialize the semaphore to zero */
    if (0 != sem_init(&g_semaphore, 0, STARTING_VALUE_SEM)) 
    {
    	DestroySharedData(shmid);
		printf("failed to create semaphore\n");
		
    	return -1;
    }

    /* creating the thread*/
    if (pthread_create(&imortal_thread, NULL, Imortal, shared_data))
	{
		DestroySharedData(shmid);
		printf("failed to create thread\n");
		
    	return -1;
	}

    /* decrement the semaphore will wait for imortal thread to finish all  */
    if (-1 == sem_wait(&g_semaphore))
    {
        DestroySharedData(shmid);
		printf("faieled to decrement semaphore\n");
        
		return -1;
    }
	
	sem_destroy(&g_semaphore);

	
	return 0;
}


/*************************** HELPER FUNCTION ***************************/


/*Signal handler function */
void Handler(int sig) 
{
	(void)sig;
    atomic_store(&g_count, 1);
}

/* watchdog thread routine */
void *Imortal(void *shared_data)
{
	shared_data_t *share_d = (shared_data_t*)shared_data;
	pid_t pid = 0;
	char shmid_str[20] = {0};
	char *args[3] = {0};
	
	assert(share_d);

	/* Convert shmid to string for passing to child */
	sprintf(shmid_str, "%d", share_d->shmid);

	/* enter to a args all variable required for exec of watchdog */
	args[0] = PATH_TO_WD;
	args[1] = shmid_str;

	
	pid = CreateChildProcess(args);
	
	/* releasing the MMI function to return */
	if (-1 == sem_post(&g_semaphore))
	{
		printf("faieled to increment semaphore\n");
		
		return NULL;
	}

	/* replying ping for a signal in an infinate loop */
	Loop(pid, share_d, "parent", args);
	
	return NULL;
}

pid_t CreateChildProcess(char *args[])
{
	pid_t pid = 0;
	
	pid = fork();

	if (0 > pid) 
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)  /* child */
	{
	 	execvp(args[0], args);
	 	
	 	/* happen only when execvp fails */
		printf("execl failed");
	}

	return pid;
}

void Loop(pid_t pid, shared_data_t *shared_data, char *word, char *args[])
{	
	int count = 3;
	while (1)
	{
		if (g_count)
		{
			 atomic_store(&g_count, 0);
			
			printf("%s: interval: %ld\n", word,shared_data->interval_seconds);
			++(shared_data->interval_seconds);
			sleep(1);
			if (kill(pid, SIGUSR1) == -1)
			{
				perror("kill");
				exit(EXIT_FAILURE);
			}
		}
		else if (0 > count)
		{
			CreateChildProcess(args);
			count = 3;
		}
		else
		{
			sleep(4);
			--count;
		}
	}
}



shared_data_t *CreateSharedData(size_t interval,
								size_t num_of_rep,
								char **args,
								int shmid)
{
	shared_data_t *share_d = (shared_data_t*)shmat(shmid, NULL, 0);
	if ((void*)-1 == (void*)share_d)
	{
		printf("failed creating share_memory\n");

		return NULL;
	}

	share_d->reps = num_of_rep;
	share_d->interval_seconds = (time_t)interval;
	share_d->shmid = shmid;
	share_d->file_name_and_commands = args;

	return share_d;
}

void DestroySharedData(int shmid)
{
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
    	printf("failed to destroy\n");
	}
}

int CreateShmid(void)
{
	key_t key = ftok(PATH_TO_WD, PROJECT_ID);

	if (-1 == key)
	{
		return -1;
	}

	return shmget(key, sizeof(shared_data_t), IPC_CREAT | S_IRWXU);
}

char **GetArgs(shared_data_t *shared_data)
{
	assert(shared_data);

	return shared_data->file_name_and_commands;
}