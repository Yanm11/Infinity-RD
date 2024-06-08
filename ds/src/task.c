/********************************** 
   Code by: Yan Meiri	
   Project: task part of scheduler
   Date: 30/05/24
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
**********************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "task.h"
#include "uid.h" 

struct task
{
    ilrd_uid_t uid;
    time_t exe_time;
    time_t interval_in_seconds;
    void (*action)(void *params);
    void *params;
};


task_t *TaskCreate(time_t exe_time, time_t interval_in_seconds, void (*action)(void *params), void *params)
{
	task_t *task = NULL;
	
	assert((time_t)0 <= exe_time);
	assert((time_t)0 <= interval_in_seconds);
	assert(action);
	
	task = (task_t*)malloc(sizeof(task_t));
	if (NULL == task)
	{
		return NULL;
	}
	
	task->uid = UIDCreate();
	if (IsSameUID(task->uid, BadUID))
	{
		free(task);
		return NULL;
	}
	
	task->exe_time = exe_time;
	task->interval_in_seconds = interval_in_seconds;
	task->action = action;
	task->params = params;
	
	return task;
}

void TaskDestroy(task_t *task)
{
	assert(task);
	
	free(task);
}

void TaskRun(task_t *task)
{
	assert(task);
	assert(task->action);
	
	task->action(task->params);
}

ilrd_uid_t GetUid(const task_t *task)
{
	assert(task);
	
	return task->uid;
}

time_t GetExecTime(const task_t *task)
{
	assert(task);
	
	return task->exe_time;
}

time_t IntervalTime(const task_t *task)
{
	assert(task);
	
	return task->interval_in_seconds;
}

void *GetParams(const task_t *task)
{
	assert(task);
	
	return task->params;
}

void (*GetActionFunc(const task_t *task))(void *params) 
{
	assert(task);
	
	return task->action;
}

void UpdateExecTime(task_t *task, time_t new_exec_time)
{
	assert(task);
	assert((time_t)0 < new_exec_time);
	
	task->exe_time = new_exec_time;
}

