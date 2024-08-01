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

#include "uid.h"
#include "hscheduler.h"
#include "watchdog.h"
#include "immortal.h"

#define CLIENT_PATH_INDEX 3

size_t g_num_reps = 0;
pid_t g_pid_to_send_to = 0;
int g_status = SUCCESS;

int main(int argc, char *argv[])
{
	time_t interval_in_sec = 0;
	hscheduler_t *scheduler = HSchedulerCreate();
	struct sigaction sa_1 = {0};
	struct sigaction sa_2 = {0};
	
	(void)argc;

	g_num_reps = StrToSizeT(argv[REPS_INDEX]);

	/* Check scheduler was created successfuly */
	printf("here\n");
	if (NULL == scheduler)
	{
		return FAILED;
	}

	/* Initialize SIGUSR 1 & 2 */
	if (FAILED == SignalInit(&sa_1, NULL, SIGUSR1))
	{
		return FAILED;
	}
	
	if (FAILED == SignalInit(&sa_2, NULL, SIGUSR2))
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
	/* Releasing the lock so imortal can continue */
	if (-1 == sem_post(g_semaphore_thread_2_wd))
	{
		return FAILED;
	}

	/* Setting the env variable */
	SetEnvVarInt(ENV_NAME, getpid());

	/* Changing back from str to time_t and updating the pid */
	interval_in_sec = (time_t)StrToSizeT(argv[INTERVAL_INDEX]);
	g_pid_to_send_to = getppid();

	/* Adding all the tasks to the scheduler */
	HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  interval_in_sec, CheckIfDNR, scheduler);
	
	HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  interval_in_sec, CheckIfAlive, (argv + CLIENT_PATH_INDEX));
	
	HSchedulerAdd(scheduler,time(NULL) + interval_in_sec,
				  interval_in_sec, RaiseCounter, "watchdog");

	HSchedulerRun(scheduler);

	HSchedulerDestroy(scheduler);
	
	sem_post(g_semaphore_thread_2_wd);
	
	if (unsetenv(ENV_NAME) != 0) 
	{
		return FAILED;
	}

	return g_status;
}