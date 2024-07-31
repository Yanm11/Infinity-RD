#ifndef __WATCH_DOG_H__
#define __WATCH_DOG_H__
#define NUM_ARGS_TO_WD 20

#include <stddef.h> /* size_t */
#include <time.h> /* time_t */
#include <sys/wait.h> /* waitpd pid_t */
#include "hscheduler.h"
#include <semaphore.h>
#include <unistd.h>
typedef struct shared_data
{
	int reps;
	time_t interval_seconds;
	int shmid;
	char **file_name_and_commands;
}shared_data_t;

typedef struct task_data
{
	pid_t pid;
	shared_data_t *shared_data;
	char *word;
	char **args;
    hscheduler_t *scheduler;
}task_data_t;

extern sem_t *g_semaphore_thread_2_wd;

/*
MMI(MakeMeImortal)
description: will activaate a watchdog process that will execute the client 
            program again once it has been killed until DNR will be called
input: interval in second, times of reptitions to send a signal before revivng, and all arguments nececary to execute
return: status 0 for success non 0 otherwise
time comlexity: O(1)
space complexity: O(1)
*/
int MMI(size_t interval_in_seconds, size_t repetitions, char **argv);

/*
MMI(MakeMeImortal)
description: stop the watchdog from running
input: nothing
return: nothing
time comlexity: O(1)
space complexity: O(1)
*/
void DNR(void);

#endif /*__WATCH_DOG_H__*/