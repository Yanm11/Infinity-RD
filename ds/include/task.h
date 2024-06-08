#ifndef __TASK_H__
#define __TASK_H__

#include "uid.h" /*ilrd_uid_t*/


typedef struct task task_t;

/*
TaskCreate
description: create a task
input: execution time, an action function and params
return: a pointer to a task if success NULL if failed
time complexity: O(1)
space complexity: O(1)
*/
task_t *TaskCreate(time_t exe_time, time_t interval_in_seconds, void (*action)(void *params), void *params);

/*
TaskDestroy
description: destroy a task
input: a pointer to a task
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void TaskDestroy(task_t *task);

/*
TaskRun
description: run the task's function
input: a pointer to a task
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void TaskRun(task_t *task);

/*
GetUid
description: get UID of a task
input: a pointer to a task
return: the UID of the task
time complexity: O(1)
space complexity: O(1)
*/
ilrd_uid_t GetUid(const task_t *task);

/*
GetExecTime
description: get the execution time of a specific task
input: pointer to task
return: execution time
time complexity: O(1)
space complexity: O(1)
*/
time_t GetExecTime(const task_t *task);

/*
IntervalTime
description: get the interval time of a specific task
input: pointer to task
return: interval in seconds time
time complexity: O(1)
space complexity: O(1)
*/
time_t IntervalTime(const task_t *task);

/*
GetParams
description: get the params of a specific task
input: pointer to task
return: pointer to the params
time complexity: O(1)
space complexity: O(1)
*/
void *GetParams(const task_t *task);

/*
GetActionFunc
description: get the action function of a specific task
input: pointer to task
return: pointer to the action function
time complexity: O(1)
space complexity: O(1)
*/
void (*GetActionFunc(const task_t *task))(void *params);

/*
UpdateExecTime
description: update the execution time of a task
input: pointer to task, new execution time to be set
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void UpdateExecTime(task_t *task, time_t new_exec_time);

#endif /*__TASK_H__*/

