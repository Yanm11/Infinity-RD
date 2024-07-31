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
#include <signal.h> /* pthread_sigmask */

#include <uid.h>
#include "hscheduler.h"
#include "imortal.h"

#define STARTING_VALUE_SEM 0
#define PATH_TO_WD "./watchdog"
#define PROJECT_ID 11
#define SEM_NAME "watchdog"
#define NUM_ARGS_TO_WD 20
#define ENV_NAME "WD_PID"
#define MAX_NUM_DIGITS_INT 12
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
void BlockSig(int sig);

static sem_t g_semaphore_thread_2_main;
atomic_int g_count = ATOMIC_VAR_INIT(0);
sem_t *g_semaphore_thread_2_wd =  NULL;
pthread_t g_imortal_thread = 0;
atomic_int g_stop_run = ATOMIC_VAR_INIT(0);
/*************************** API FUNCTIONS ***************************/


int MMI(size_t interval_in_seconds, size_t repetitions, char **argv)
{
	int shmid = 0;
	shared_data_t *shared_data = NULL;
	struct sigaction sa = {0};
	struct sigaction sa_2 = {0};
	atomic_store(&g_stop_run, 0);
	atomic_store(&g_count, 0);
	
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
	
    /* Initialize the semaphore to synchrnize between threads to zero */
    if (0 != sem_init(&g_semaphore_thread_2_main, 0, STARTING_VALUE_SEM)) 
    {
    	DestroySharedData(shmid);
		printf("failed to create semaphore thread to main\n");
		
    	return -1;
    }

	/* Initialize the semaphore to synchrnize between wd and thread to zero */
	g_semaphore_thread_2_wd = sem_open(SEM_NAME, O_CREAT,
									   SEM_PERMITIONS, STARTING_VALUE_SEM);
	if (SEM_FAILED == g_semaphore_thread_2_wd)
	{
		DestroySharedData(shmid);
		printf("failed to create semaphore thread to wd\n");
		
    	return -1;
	}

    /* creating the thread*/
    if (pthread_create(&g_imortal_thread, NULL, Imortal, shared_data))
	{
		DestroySharedData(shmid);
		printf("failed to create thread\n");
		
    	return -1;
	}

    /* decrement the semaphore will wait for imortal thread to finish all  */
    if (-1 == sem_wait(&g_semaphore_thread_2_main))
    {
        DestroySharedData(shmid);
		printf("faieled to decrement semaphore\n");
        
		return -1;
    }
	
	sem_destroy(&g_semaphore_thread_2_main);

	return 0;
}

void DNR(void)
{
	/* stop the current thread */
	raise(SIGUSR2);

	pthread_join(g_imortal_thread,NULL);

	
}

/*************************** HELPER FUNCTION ***************************/


/*Signal handler function */
void HandlerSig1(int sig) 
{
	(void)sig;
    atomic_store(&g_count, 0);
}

void HandlerSig2(int sig) 
{
	(void)sig;
    atomic_store(&g_stop_run, 1);
}

/* watchdog thread routine */
void *Imortal(void *shared_data)
{
	shared_data_t *share_d = (shared_data_t*)shared_data;
	pid_t pid = 0;
	hscheduler_t *scheduler = HSchedulerCreate();
	task_data_t *task_data_ptr = (task_data_t*)malloc(sizeof(task_data_t));
	char shmid_str[20] = {0};
	char *args[NUM_ARGS_TO_WD] = {0};
	size_t i = 0;
	int value = -1;
	struct sigaction sa_prev = {0};
	assert(share_d);

	/* check scheduler was created successfuly */
	if (NULL == scheduler)
	{
		printf("faieled to create scheduler\n");
		
		return NULL;
	}

	/* check task_data_ptr was created successfully */
	if (NULL == task_data_ptr)
	{
		printf("failed to create task data ptr\n");

		return NULL;
	}

	/* Convert shmid to string for passing to child */
	sprintf(shmid_str, "%d", share_d->shmid);

	/* enter to a args all variable required for exec of watchdog */
	args[0] = PATH_TO_WD;
	args[1] = shmid_str;

	while (NULL != share_d->file_name_and_commands[i] && NUM_ARGS_TO_WD >= i +2)
	{
		args[i + 2] = share_d->file_name_and_commands[i];

		++i;
	}

	if (getenv(ENV_NAME) == NULL)
	{
		pid	= CreateChildProcess(args);
		
		printf("env: %s\n", getenv(ENV_NAME));
		printf("first time here\n");
	}
	else
	{
		pid = atoi(getenv(ENV_NAME));
		sem_getvalue(g_semaphore_thread_2_wd, &value);

		printf("second time here\n");
		printf("sem is: %d\n", value);
		/* releasing the lock for wd to continue */
		if (-1 == sem_post(g_semaphore_thread_2_wd))
		{
			printf("faieled to increment semaphore\n");
			
		}
		sem_getvalue(g_semaphore_thread_2_wd, &value);
		printf("sem is: %d\n", value);
			
	}


	

	/* releasing the MMI function to return */
	if (-1 == sem_post(&g_semaphore_thread_2_main))
	{
		printf("faieled to increment semaphore\n");
		
		return NULL;
	}

	/* assigning all the nececary variable to task_data */
	task_data_ptr->pid = pid;
	task_data_ptr->shared_data = share_d;
	task_data_ptr->word = "parent";
	task_data_ptr->args = args;
	task_data_ptr->scheduler = scheduler;

	HSchedulerAdd(scheduler,time(NULL) + share_d->interval_seconds,
				  share_d->interval_seconds, SentSignal, task_data_ptr);
	
	HSchedulerRun(scheduler);
	kill(task_data_ptr->pid,SIGUSR2);
	/* BlockSig(SIGUSR1); */

	sem_wait(g_semaphore_thread_2_wd);
	HSchedulerDestroy(scheduler);
	
	free(task_data_ptr);
	
	DestroySharedData(share_d->shmid);

	sem_close(g_semaphore_thread_2_wd);
	sem_unlink(SEM_NAME);

	/* return SIGUSR1 to defoult */
	if (sigaction(SIGUSR1, &sa_prev, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	
	/* return SIGUSR2 to defoult */
	if (sigaction(SIGUSR2, &sa_prev, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	return NULL;
}

pid_t CreateChildProcess(char *args[])
{
	pid_t pid = 0;
	int value = -1;

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
	
	printf("WAITING HERE\n");
	sem_getvalue(g_semaphore_thread_2_wd, &value);
	printf("sem before waiting: %d\n", value);
	/* making sure wd is up and ready before continuing */
	if (-1 == sem_wait(g_semaphore_thread_2_wd))
	{
		printf("faieled to decrement semaphore\n");
		
		return 0;
	}

	sem_getvalue(g_semaphore_thread_2_wd, &value);
	printf("sem after wait is: %d\n", value);
	return pid;
}
void SentSignal(void *task_data_ptr)
{
	task_data_t *task_data = (task_data_t*)task_data_ptr;
	pid_t pid = task_data->pid;
	shared_data_t *shared_data = task_data->shared_data;
	hscheduler_t *scheduler = task_data->scheduler;
	char *word = task_data->word;
	/* stop the counter */
	if (atomic_load(&g_stop_run) == 1)
	{
		HSchedulerStop(scheduler);
	}

	/* if the counter is lower than the recived threshold */
	else if (atomic_load(&g_count) < shared_data->reps)
	{
		printf("%s: %d sent to:%d\n", word, getpid(),pid);

		/* sending the signal */
		kill(pid, SIGUSR1);
		

		/* increase the reptions */
		atomic_fetch_add(&g_count, 1);
	}
	/* means that the other process as fallen and we will revive it */
	else
	{
		atomic_store(&g_count, 0);
		printf("im here\n");

		printf("pid before awake: %d\n", pid);
		task_data->pid = CreateChildProcess(task_data->args);

		printf("pid after awake: %d\n", task_data->pid);

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

void SetEnvVar(const char *name, const char *value) 
{
    if (setenv(name, value, 1) != 0) 
	{
        perror("setenv");
    }
}

void SetEnvVarInt(const char *name, int value) 
{
    char buffer[MAX_NUM_DIGITS_INT] = {0};
    sprintf(buffer, "%d", value);
    SetEnvVar(name, buffer);
}

void BlockSig(int sig)
{
	sigset_t set = {0};
    int result = 0;

    /* Initialize the signal set */
    sigemptyset(&set);
    
    /* Add SIGUSR1 to the set */
    sigaddset(&set, sig);

    /* Block SIGUSR1 */
    result = pthread_sigmask(SIG_BLOCK, &set, NULL);
    if (result != 0) 
	{
        printf("coud not block\n");
    }
}