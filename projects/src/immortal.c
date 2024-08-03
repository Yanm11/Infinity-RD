/* approved by jorge */
#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /*  printf sprintf strtoul */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <signal.h> /* sigemptyset sigaction */
#include <pthread.h> /* pthread_create pthread_join */
#include <stdatomic.h> /* atomic type and functions */
#include <semaphore.h> /* sem_wait sem_post sem_init sem_destroy */
#include <unistd.h>	/* fork exec */
#include <time.h> /* time_t */
#include <sys/wait.h> /* waitpd pid_t */
#include <sys/stat.h> /* S_IRWXU */
#include <fcntl.h> /* S_IRWXU */
#include <signal.h> /* pthread_sigmask */

#include "uid.h"
#include "hscheduler.h"
#include "watchdog.h"
#include "immortal.h"

#define MAX_ARGS_TO_WD 20
#define MAX_NUM_DIGITS_INT 12
#define MAX_DIGITS_SIZE_T 20
#define MAX_LENGHT_OF_STRING 50
#define PATH_TO_WD "./watchdog"

static atomic_int g_count = ATOMIC_VAR_INIT(0);
static atomic_int g_stop_run = ATOMIC_VAR_INIT(0);
sem_t g_semaphore_thread_2_main;
sem_t *g_semaphore_thread_2_wd =  NULL;
pthread_t g_immortal_thread = 0;
int g_status = SUCCESS;
pid_t g_pid_to_send_to = 0;
size_t g_num_reps = 0;


/*************************** API FUNCTIONS ***************************/


int MMI(size_t interval_in_seconds, size_t repetitions, char **argv)
{
	/* Initialize arrays for transfering the required data */
	static char *args[MAX_ARGS_TO_WD] = {0};
	static char interval_str[MAX_DIGITS_SIZE_T] = {0};
	static char reps_str[MAX_DIGITS_SIZE_T] = {0};
	size_t i = 0;

	/* Assert inputs*/
	assert(0 < interval_in_seconds);
	assert(0 < repetitions);
	assert(argv);

	/* Initialize 2 atomic type variable to their start value*/
	atomic_store(&g_stop_run, 0);
	atomic_store(&g_count, 0);

	/* Initialize global variable reps */	
	g_num_reps = repetitions;

	/* Convert interval and repetitions to string for passing to wd */
	sprintf(interval_str, "%ld", interval_in_seconds);
	sprintf(reps_str, "%ld", repetitions);

	/* Insert to a args all variable required for exec of watchdog */
	args[0] = PATH_TO_WD;
	args[INTERVAL_INDEX] = interval_str;
	args[REPS_INDEX] = reps_str;

	while (NULL != argv[i] && MAX_ARGS_TO_WD > (i + 3))
	{
		args[i + 3] = argv[i];

		++i;
	}

    /* Initialize semaphore to synchronize between thread and MMI */
    if (0 != sem_init(&g_semaphore_thread_2_main, 0, STARTING_VALUE_SEM)) 
    {
    	return FAILED;
    }

	/* Initialize semaphore to synchrnize between thread and wd */
	g_semaphore_thread_2_wd = sem_open(SEM_NAME, O_CREAT,
									   SEM_PERMITIONS, STARTING_VALUE_SEM);
	if (SEM_FAILED == g_semaphore_thread_2_wd)
	{	
    	return FAILED;
	}

	/* Blocking both SIGUSR1/2 from the main thread */
	if ( 0 != MaskSignal(SIGUSR1, SIG_BLOCK))
	{
		return FAILED;
	}
	if ( 0 != MaskSignal(SIGUSR2, SIG_BLOCK))
	{
		return FAILED;
	}

    /* Creating the thread*/
    if (0 != pthread_create(&g_immortal_thread, NULL, Immortal, args))
	{	
    	return FAILED;
	}

    /* Waiting for imortal thread to finish all necessary preperations  */
    if (-1 == sem_wait(&g_semaphore_thread_2_main))
    {   
		return FAILED;
    }
	
	/* Cleaning */
	sem_destroy(&g_semaphore_thread_2_main);

	return g_status;
}

void DNR(void)
{
	/* Stop the immortal thread and wd */
	kill(g_pid_to_send_to,SIGUSR2);
	kill(getpid(), SIGUSR2);

	pthread_join(g_immortal_thread,NULL);

	/* Unblocking both SIGUSR1/2 for the main thread */
	MaskSignal(SIGUSR1, SIG_UNBLOCK);
	MaskSignal(SIGUSR2, SIG_UNBLOCK);
}


/*************************** SIGNAL FUNCTIONS ***************************/


/*Signal handler functions */
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

int SignalInit(struct sigaction *sa, struct sigaction *sa_prev, int sig)
{
	sa->sa_flags = 0; 
	
	/* handler SIGUSR */
	if (SIGUSR1 == sig)
	{
		sa->sa_handler = HandlerSig1;
	}
	else
	{
		sa->sa_handler = HandlerSig2;
	}
	
	sigemptyset(&(sa->sa_mask)); /* empty mask */
   
    if (-1 == sigaction(sig, sa, sa_prev))
    {	
    	return FAILED;
	}

	return SUCCESS;
}

int MaskSignal(int sig, int sig_block)
{
	sigset_t set = {0};

    /* Initialize the signal set */
    sigemptyset(&set);
    
    /* Add SIG to the set */
    sigaddset(&set, sig);

    /* Block / Unblock SIG */
    return pthread_sigmask(sig_block, &set, NULL);
}


/*************************** THREAD ROUTINE  **********************/


void *Immortal(void *args_to_thread)
{
	char **args = (char**)args_to_thread;
	time_t interval_in_sec = 0;
	hscheduler_t *scheduler = HSchedulerCreate();
	ilrd_uid_t uid = {0};

	/* Initialize 2 sigaction structers and 2 other to keep the old vlues */
	struct sigaction sa_1 = {0};
	struct sigaction sa_2 = {0};
	struct sigaction sa_1_prev = {0};
	struct sigaction sa_2_prev = {0};

	assert(args_to_thread);

	/* Check scheduler was created successfuly */
	if (NULL == scheduler)
	{
		return ErrorHandling(NULL, NULL, NULL);
	}

	/* Unblocking both SIGUSR1/2 for the thread */
	if ( 0 != MaskSignal(SIGUSR1, SIG_UNBLOCK))
	{
		return ErrorHandling(scheduler, NULL, NULL);
	}
	if ( 0 != MaskSignal(SIGUSR2, SIG_UNBLOCK))
	{
		return ErrorHandling(scheduler, NULL, NULL);
	}

	/* Initialize SIGUSR 1 & 2 */
	if (FAILED == SignalInit(&sa_1, &sa_1_prev, SIGUSR1))
	{
		return ErrorHandling(scheduler, NULL, NULL);
	}
	
	if (FAILED == SignalInit(&sa_2, &sa_2_prev, SIGUSR2))
	{
		return ErrorHandling(scheduler, &sa_1_prev, NULL);
	}
	
	/* Check if env variable exist if not create the wd process else get pid */
	if (NULL == getenv(ENV_NAME))
	{
		/* Creating wd process and checking for error */
		g_pid_to_send_to = CreateChildProcess(args);

		if (FAILED == g_pid_to_send_to)
		{
			return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
		}
	}
	else
	{
		g_pid_to_send_to = atoi(getenv(ENV_NAME));
	
		/* Releasing the lock for wd to continue */
		if (-1 == sem_post(g_semaphore_thread_2_wd))
		{
			return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
		}
	}

	/* Changing back from str to time_t */
	interval_in_sec = (time_t)StrToSizeT(args[INTERVAL_INDEX]);
	if ((time_t)0 == interval_in_sec)
	{
		return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
	}

	/* Adding all the tasks to the scheduler */
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  		interval_in_sec, CheckIfDNR, scheduler);
	if (IsSameUID(uid, BadUID))
	{
		return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
	}
	
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  		interval_in_sec, CheckIfAlive, args);
	if (IsSameUID(uid, BadUID))
	{
		return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
	}	
	
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  interval_in_sec, RaiseCounter, "immortal");
	if (IsSameUID(uid, BadUID))
	{
		return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
	}
	
	/* Releasing the MMI function so it can return to client */
	if (-1 == sem_post(&g_semaphore_thread_2_main))
	{	
		return ErrorHandling(scheduler, &sa_1_prev, &sa_2_prev);
		
		return NULL;
	}
	
	HSchedulerRun(scheduler);

	sem_wait(g_semaphore_thread_2_wd);
	
	CleanUp(scheduler, &sa_1_prev, &sa_2_prev);

	return NULL;
}


/*************************** THREAD HELPER FUNCTIONS  **********************/


pid_t CreateChildProcess(char *args[])
{
	pid_t pid = 0;

	pid = fork();

	/* Error*/
	if (0 > pid) 
	{
		return FAILED;
	}
	/* Child */
	else if (pid == 0) 
	{
	 	execvp(args[0], args);
	 	
	 	/* Happens only when execvp fails */
		return FAILED;
	}

	/* Parent */
	/* Waiting for child procss to be ready */
	if (-1 == sem_wait(g_semaphore_thread_2_wd))
	{
		return FAILED;
	}

	return pid;
}

void SetEnvVarInt(const char *name, int value) 
{
    char buffer[MAX_NUM_DIGITS_INT] = {0};
    
	sprintf(buffer, "%d", value);
   
    setenv(name, buffer, 1);
}

size_t StrToSizeT(const char *str)
{
	char *endptr = "";
	unsigned long result = 0;

	result = strtoul(str, &endptr, 10);

	if ('\0' != *endptr)
	{
		result = 0;
	}

	return (size_t)result;
}

void CleanUp(hscheduler_t *scheduler, 
			 struct sigaction *sa_1_prev,
			 struct sigaction *sa_2_prev)
{
	if (NULL != scheduler)
	{
		HSchedulerDestroy(scheduler);
	}

	/* Closing & deleting the semaphore */
	sem_close(g_semaphore_thread_2_wd);
	sem_unlink(SEM_NAME);

	/* Return SIGUSR1 to  old preference */
	if (NULL != sa_1_prev)
	{
		sigaction(SIGUSR1, sa_1_prev, NULL);
	}
	
	/* Return SIGUSR2 to old preference */
	if (NULL != sa_2_prev)
	{
		sigaction(SIGUSR2, sa_2_prev, NULL);
	}
}

void *ErrorHandling(hscheduler_t *scheduler, 
				   struct sigaction *sa_1_prev,
				   struct sigaction *sa_2_prev)
{
	g_status = FAILED;
	
	sem_post(&g_semaphore_thread_2_main);

	CleanUp(scheduler, sa_1_prev, sa_2_prev);
	
	return NULL;
}


/*************************** TASK FUNCTIONS ***************************/


void RaiseCounter(void *word)
{
	/* if the counter is lower than the recived threshold */
	if (atomic_load(&g_count) < (int)g_num_reps)
	{
		printf("%s: %d sent to:%d\n", (char*)word, getpid(),g_pid_to_send_to);

		/* Sending the signal */
		kill(g_pid_to_send_to, SIGUSR1);
		
		/* Increase the reption's counter */
		atomic_fetch_add(&g_count, 1);
	}
}

void CheckIfAlive(void *args)
{
	assert(args);

	/* If the counter passed the reps lim we need to revive the other process */
	if (atomic_load(&g_count) >= (int)g_num_reps)
	{
		atomic_store(&g_count, 0);
		printf("revive\n");
	
		g_pid_to_send_to = CreateChildProcess((char**)args);
	}
}

void CheckIfDNR(void *scheduler)
{
	assert(scheduler);

	/* If stop flag is TRUE stop the scheduler */
	if (1 == atomic_load(&g_stop_run))
	{
		HSchedulerStop((hscheduler_t*)scheduler);
	}
}  


