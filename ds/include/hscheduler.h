#ifndef __HSCHEDULER_H__
#define __HSCHEDULER_H__

#include <sys/types.h> /*size_t, time_t*/

#include "uid.h" /*ilrd_uid_t*/

typedef struct hscheduler hscheduler_t;

enum status
{
	SUCCESS = 0,
    FAILURE = 1,
    SCHEDULER_STOP = 2,
    SCHEDULER_UID_NOT_FOUND = 3
};


/*
SchedulerCreate
description: create a scheduler
input: nothing
return: a pointer to a scheduler 
time complexity: O(1)
space complexity: O(1)
*/
hscheduler_t *HSchedulerCreate(void);

/*
SchedulerDestroy
description: destroy a scheduler
input: a pointer to a scheduler
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void HSchedulerDestroy(hscheduler_t *scheduler);

/*
SchedulerAdd
description: adds a task to the scheduler
input: a pointer to a scheduler, execution time, interval in seconds, an action func and a params
return: if success UID if failed BadUID
time complexity: O(1)
space complexity: O(1)
*/
ilrd_uid_t HSchedulerAdd(hscheduler_t *scheduler,
                    time_t exec_time, 
                    time_t interval_in_seconds, 
                    void (*action)(void *params), 
                    void *params);

/*
SchedulerRemove
description: removes a task from the scheduler
input: a pointer to a scheduler, uid
return: a status (0 means success, otherwise means fail)
time complexity: O(n)
space complexity: O(1)
*/
int HSchedulerRemove(hscheduler_t *scheduler, ilrd_uid_t uid);

/*
SchedulerRun
description: Run the scheduler until stop/ end of tasks/ error.
input: pointer to scheduler
return: a status (SUCCESS if finished and scheduler is empty, FAILURE if failed in some way during the run, SCHEDULER_STOP if we stoped the scheduler and there are still task in it
time complexity: O(n)
space complexity: O(n)
*/
int HSchedulerRun(hscheduler_t *scheduler);

/*
SchedulerStop
description: stop the runing of the processes
input: a pointer to a scheduler
return: nothing
time complexity: O(1)
space complexity:O(1)
*/
void HSchedulerStop(hscheduler_t *scheduler);

/*
SchedulerSize
description: get size of scheduler
input: a pointer to a scheduler
return: size of scheduler
time complexity: O(n)
space complexity: O(1)  
*/
size_t HSchedulerSize(hscheduler_t *scheduler);

/*
SchedulerIsEmpty
description: tells if there are tasks 
input: pointer to schedualer
return: 1 if empty 0 if not
time complexity: O(n)
space complexity: O(1)
*/
int HSchedulerIsEmpty(hscheduler_t *scheduler);

/*
SchedulerClear
description: delete all tasks
input: pointer to schedualer
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void HSchedulerClear(hscheduler_t *scheduler);

#endif /*__HSCHEDULER_H__*/
