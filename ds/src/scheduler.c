/********************************** 
   Code by: Yan Meiri	
   Project: scheduler data structer
   Date: 30/05/24
   Review by: Or the king
   Review Date: 9/6/2024
   Approved by: Or the king
   Approval Date: 9/6/2024 
**********************************/


#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time */
#include <unistd.h> /* sleep */
#include <sys/types.h> /*size_t, time_t*/

#include "pq.h"
#include "scheduler.h"
#include "uid.h"
#include "task.h"

static int CompTask(const void *task1, const void *task2);
static int MatchTask(const void *task1, const void *task2);

struct scheduler
{
    pq_t *task_queue;
    int stop_flag;
};



scheduler_t *SchedulerCreate(void)
{
	scheduler_t *scheduler = (scheduler_t*)malloc(sizeof(scheduler_t));
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->task_queue = PQCreate(&CompTask);
	if (NULL == scheduler->task_queue)
	{
		free(scheduler);
		
		return NULL;
	}
	
	scheduler->stop_flag = 0;
	
	return scheduler;	
}

void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	SchedulerClear(scheduler);
	PQDestroy(scheduler->task_queue);
	free(scheduler);
}

ilrd_uid_t SchedulerAdd(scheduler_t *scheduler,
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
	status = PQEnqueue(scheduler->task_queue, task);
	if (0 != status)
	{
		TaskDestroy(task);

		return BadUID;
	}
	
	return GetUid(task);
}

int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	void *task = NULL;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	
	task = PQErase(scheduler->task_queue, &MatchTask, &uid);
	if (NULL == task)
	{
		return SCHEDULER_UID_NOT_FOUND;
	}
	
	TaskDestroy(task);
	
	return SUCCESS;
}

int SchedulerRun(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	scheduler->stop_flag = 0;
	
	while (!SchedulerIsEmpty(scheduler) && !scheduler->stop_flag)
	{
		task_t *task = (task_t*)PQDequeue(scheduler->task_queue);
		
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
				sleep(GetExecTime(task) - time(NULL));
				TaskRun(task);
			}
		
			if (IntervalTime(task))
			{
				int status = 0;
				time_t new_exec_time = time(NULL) + IntervalTime(task);
				UpdateExecTime(task,new_exec_time);
			
				status = PQEnqueue(scheduler->task_queue, task);
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
	
	if (!SchedulerIsEmpty(scheduler) && scheduler->stop_flag)
	{
		return SCHEDULER_STOP;
	}
	
	return SUCCESS;
}

void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	
	scheduler->stop_flag = 1;
}

size_t SchedulerSize(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	return PQSize(scheduler->task_queue);
}

int SchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(scheduler);
	assert(scheduler->task_queue);
	
	return PQIsEmpty(scheduler->task_queue);
}

void SchedulerClear(scheduler_t *scheduler)
{
	void *task = NULL;
	
	assert(scheduler);
	assert(scheduler->task_queue);
	
	while (!SchedulerIsEmpty(scheduler))
	{
		task = PQDequeue(scheduler->task_queue);
		TaskDestroy(task);
	}
}


static int CompTask(const void *task1, const void *task2)
{
	return (GetExecTime(task1) -GetExecTime(task2));
}

static int MatchTask(const void *task1, const void *task2)
{
	return (IsSameUID(GetUid(task1), GetUid(task2)));
}



























