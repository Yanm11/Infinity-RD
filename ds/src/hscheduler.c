/********************************** 
   Code by: Yan Meiri	
   Project: heap scheduler data structer
   Date: 2/07/24
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
**********************************/


#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time */
#include <unistd.h> /* sleep */
#include <sys/types.h> /*size_t, time_t*/

#include "hpq.h"
#include "hscheduler.h"
#include "uid.h"
#include "task.h"

static int CompTask(const void *task1, const void *task2);
static int MatchTask(const void *task1, const void *task2);

struct hscheduler
{
    hpq_t *task_queue;
    int stop_flag;
};



hscheduler_t *HSchedulerCreate(void)
{
	hscheduler_t *scheduler = (hscheduler_t*)malloc(sizeof(hscheduler_t));
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->task_queue = HPQCreate(&CompTask);
	if (NULL == scheduler->task_queue)
	{
		free(scheduler);
		
		return NULL;
	}
	
	scheduler->stop_flag = 0;
	
	return scheduler;	
}

void HSchedulerDestroy(hscheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	HSchedulerClear(scheduler);
	HPQDestroy(scheduler->task_queue);
	free(scheduler);
}

ilrd_uid_t HSchedulerAdd(hscheduler_t *scheduler,
                    time_t exec_time, 
                    time_t interval_in_seconds, 
                    void (*action)(void *params), 
                    void *params)
{
	task_t *task = NULL;
	int status = 0;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	assert(0 < exec_time);
	assert(0 <= interval_in_seconds);
	assert(action);
	
	/* create task */
	task = TaskCreate(exec_time, interval_in_seconds, action, params);
	if (NULL == task)
	{
		return BadUID;
	}
	
	/* add to the queue */
	status = HPQEnqueue(scheduler->task_queue, task);
	if (0 != status)
	{
		TaskDestroy(task);

		return BadUID;
	}
	
	return GetUid(task);
}

int HSchedulerRemove(hscheduler_t *scheduler, ilrd_uid_t uid)
{
	void *task = NULL;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	
	task = HPQErase(scheduler->task_queue, &MatchTask, &uid);
	if (NULL == task)
	{
		return SCHEDULER_UID_NOT_FOUND;
	}
	
	TaskDestroy(task);
	
	return SUCCESS;
}

int HSchedulerRun(hscheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	scheduler->stop_flag = 0;
	
	while (!HSchedulerIsEmpty(scheduler) && !scheduler->stop_flag)
	{
		task_t *task = (task_t*)HPQDequeue(scheduler->task_queue);
		
		if (time(NULL) > GetExecTime(task))
		{
			TaskDestroy(task);
		}
		else
		{
			if (time(NULL) == GetExecTime(task))
			{
				TaskRun(task);
			}
			else
			{
				time_t remaining_time = GetExecTime(task) - time(NULL);
				
				while (0 != remaining_time)
				{
					remaining_time = sleep(remaining_time);
				}

				TaskRun(task);
			}
		
			if (IntervalTime(task))
			{
				int status = 0;
				time_t new_exec_time = time(NULL) + IntervalTime(task);
				UpdateExecTime(task,new_exec_time);
			
				status = HPQEnqueue(scheduler->task_queue, task);
				if (0 != status)
				{
					return FAILURE;
				}
			}
			else
			{
				TaskDestroy(task);
			}
		}
	}
	
	if (!HSchedulerIsEmpty(scheduler) && scheduler->stop_flag)
	{
		return SCHEDULER_STOP;
	}
	
	return SUCCESS;
}

void HSchedulerStop(hscheduler_t *scheduler)
{
	assert(scheduler);
	
	scheduler->stop_flag = 1;
}

size_t HSchedulerSize(hscheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	return HPQSize(scheduler->task_queue);
}

int HSchedulerIsEmpty(hscheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	return HPQIsEmpty(scheduler->task_queue);
}

void HSchedulerClear(hscheduler_t *scheduler)
{
	void *task = NULL;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	
	while (!HSchedulerIsEmpty(scheduler))
	{
		task = HPQDequeue(scheduler->task_queue);
		TaskDestroy(task);
	}
}


static int CompTask(const void *task1, const void *task2)
{
	return (GetExecTime(task2) - GetExecTime(task1));
}

static int MatchTask(const void *task1, const void *task2)
{
	return (IsSameUID(GetUid(task1), GetUid(task2)));
}



























