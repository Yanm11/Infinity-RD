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

#define CLIENT_PATH_INDEX 3

void ErrorHandlingWD(hscheduler_t *scheduler);

size_t g_num_reps = 0;
pid_t g_pid_to_send_to = 0;
int g_status = SUCCESS;

int main(int argc, char *argv[])
{
	time_t interval_in_sec = 0;
	hscheduler_t *scheduler = NULL;
	struct sigaction sa_1 = {0};
	struct sigaction sa_2 = {0};
	ilrd_uid_t uid = {0};

	(void)argc;
	
	/* Initialize SIGUSR 1 & 2 */
	if (FAILED == SignalInit(&sa_1, NULL, SIGUSR1))
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
	}
	
	if (FAILED == SignalInit(&sa_2, NULL, SIGUSR2))
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
	}

	/* Setting the env variable */
	SetEnvVarInt(ENV_NAME, getpid());
	
	/* Initialize semaphore to synchrnize between thread and wd */
	g_semaphore_thread_2_wd = sem_open(SEM_NAME, O_CREAT,
									   SEM_PERMITIONS, STARTING_VALUE_SEM);
	if (SEM_FAILED == g_semaphore_thread_2_wd)
	{
		return FAILED;
	}

	/* Releasing the lock so imortal can continue */
	if (-1 == sem_post(g_semaphore_thread_2_wd))
	{
		ErrorHandlingWD(NULL);

		return FAILED;
	}

	/* Create and check scheduler was created successfuly */
	scheduler = HSchedulerCreate();
	if (NULL == scheduler)
	{
		ErrorHandlingWD(NULL);

		return FAILED;
	}


	/* Initializing number of repetitions */
	g_num_reps = StrToSizeT(argv[REPS_INDEX]);
	if (0 == g_num_reps)
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
	}

	/* Changing back from str to time_t and updating the pid */
	g_pid_to_send_to = getppid();
	interval_in_sec = (time_t)StrToSizeT(argv[INTERVAL_INDEX]);
	if ((time_t)0 == interval_in_sec)
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
	}

	/* Adding all the tasks to the scheduler */
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  		interval_in_sec, CheckIfDNR, scheduler);
	if (IsSameUID(uid, BadUID))
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
 	}
	
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  		interval_in_sec, CheckIfAlive, (argv + CLIENT_PATH_INDEX));
	if (IsSameUID(uid, BadUID))
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
 	}	
	uid = HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  		interval_in_sec, RaiseCounter, "watchdog");
	if (IsSameUID(uid, BadUID))
	{
		ErrorHandlingWD(scheduler);

		return FAILED;
 	}

	HSchedulerRun(scheduler);

	/* Clean up*/
	ErrorHandlingWD(scheduler);

	/* Releasing the lock so imortal can continue */
	sem_post(g_semaphore_thread_2_wd);

	return g_status;
}

void ErrorHandlingWD(hscheduler_t *scheduler)
{
	if (NULL != scheduler)
	{
		HSchedulerDestroy(scheduler);
	}
	
	unsetenv(ENV_NAME);
}