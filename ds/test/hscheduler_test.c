#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <unistd.h> /* sleep() */
#include <time.h> /* time() */
#include <sys/types.h> /*size_t, time_t*/

#include "hscheduler.h"
#include "uid.h"

#define TESTNUM 7

static char failed_tests_print[200] = {'\0'};

static int TestSchedulerAdd(void);
static int TestSchedulerRemove(void);
static int TestSchedulerRun(void);
static int TestSchedulerStop(void);

static int TestSchedulerSize(void);
static int TestSchedulerIsEmpty(void);
static int TestSchedulerClear(void);

void PrintInTest(void *str)
{
	printf("\n%s\n\n", (char *)str);
}

void IncrementInTest(void *count)
{
	++*(size_t *)count;
}

void StopInTest(void *scheduler)
{
	HSchedulerStop(scheduler);
}

void AddFailedTest(const char *str);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestSchedulerAdd();
	printf("Tested SchedulerAdd\n");
	failed_tests_num += TestSchedulerRemove();
	printf("Tested SchedulerRemove\n");
	failed_tests_num += TestSchedulerRun();
	printf("Tested SchedulerRun\n");
	failed_tests_num += TestSchedulerStop();
	printf("Tested SchedulerStop\n");
	
	failed_tests_num += TestSchedulerSize();
	printf("Tested SchedulerSize\n");
	failed_tests_num += TestSchedulerIsEmpty();
	printf("Tested SchedulerIsEmpty\n");
	failed_tests_num += TestSchedulerClear();
	printf("Tested SchedulerClear\n");
	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}


void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestSchedulerAdd(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	ilrd_uid_t get_uid1 = BadUID;
	ilrd_uid_t get_uid2 = BadUID;
	ilrd_uid_t get_uid3 = BadUID;
	size_t test_count = 0;
	size_t get_size = 0;
	int status = 0;
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 6, 0, IncrementInTest,
															 &test_count);	
	if (IsSameUID(BadUID, get_uid1))
	{
		AddFailedTest("TestSchedulerAdd1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	

	get_uid2 = HSchedulerAdd(scheduler, time(NULL) + 3, 0, PrintInTest,
										"---Started testing SchedulerAdd---");
	if (IsSameUID(BadUID, get_uid2))
	{
		AddFailedTest("TestSchedulerAdd2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_uid3 = HSchedulerAdd(scheduler, time(NULL) + 4, 0, StopInTest,scheduler);
	
	if (IsSameUID(BadUID, get_uid3))
	{
		AddFailedTest("TestSchedulerAdd3\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_size = HSchedulerSize(scheduler);
	if (3 != get_size)
	{
		AddFailedTest("TestSchedulerAdd4\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	status = HSchedulerRun(scheduler);
	if (SCHEDULER_STOP != status)
	{
		AddFailedTest("TestSchedulerAdd5\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_size = HSchedulerSize(scheduler);
	if (1 != get_size)
	{
		AddFailedTest("TestSchedulerAdd6\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (0 != test_count)
	{
		AddFailedTest("TestSchedulerAdd7\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerAdd(scheduler, time(NULL) + 1, 0, PrintInTest,
										"---SchedulerAdd second run---");

	status = HSchedulerRun(scheduler);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerAdd8\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (1 != test_count)
	{
		AddFailedTest("TestSchedulerAdd9\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (!HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerAdd10\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}

	HSchedulerDestroy(scheduler);
	
	return 0;
}

static int TestSchedulerRemove(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	ilrd_uid_t get_uid1 = BadUID;
	ilrd_uid_t get_uid2 = BadUID;
	ilrd_uid_t get_uid3 = BadUID;
	size_t test_count = 0;
	size_t get_size = 0;
	int status = 0;
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 3, 0, PrintInTest,
									"---Started testing SchedulerRemove---");
	get_uid2 = HSchedulerAdd(scheduler, time(NULL) + 4, 1, IncrementInTest,
															 &test_count);
															 
	get_uid3 = HSchedulerAdd(scheduler, time(NULL) + 4, 0, StopInTest, 
															scheduler);
															 
	status = HSchedulerRemove(scheduler, get_uid2);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerRemove1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	status = HSchedulerRun(scheduler);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerRemove2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (0 != test_count)
	{
		AddFailedTest("TestSchedulerRemove3\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
						 
	get_size = HSchedulerSize(scheduler);
	if (0 != get_size)
	{
		AddFailedTest("TestSchedulerRemove5\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 2, 0, PrintInTest,
									"---SchedulerRemove second run---");
	get_uid2 = HSchedulerAdd(scheduler, time(NULL) + 2, 1, IncrementInTest,
															 &test_count);
															 
	get_uid3 = HSchedulerAdd(scheduler, time(NULL) + 4, 1, StopInTest, 
															scheduler);
															
															
	status = HSchedulerRun(scheduler);
	if (SCHEDULER_STOP != status)
	{
		AddFailedTest("TestSchedulerRemove6\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
						 
	get_size = HSchedulerSize(scheduler);
	if (2 != get_size)
	{
		AddFailedTest("TestSchedulerRemove7\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (2 != test_count)
	{
		AddFailedTest("TestSchedulerRemove8\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	status = HSchedulerRemove(scheduler, get_uid1);
	if (SCHEDULER_UID_NOT_FOUND != status)
	{
		AddFailedTest("TestSchedulerRemove9\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	status = HSchedulerRemove(scheduler, get_uid2);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerRemove10\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	status = HSchedulerRemove(scheduler, get_uid3);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerRemove11\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
						 
	get_size = HSchedulerSize(scheduler);
	if (0 != get_size)
	{
		AddFailedTest("TestSchedulerRemove12\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (!HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerRemove13\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}

	HSchedulerDestroy(scheduler);
	
	return 0;
}
	
	
static int TestSchedulerRun(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	size_t test_count = 0;
	int status = 0;
	
	HSchedulerAdd(scheduler, time(NULL) - 1, 0, IncrementInTest,
															 &test_count);
															 
	HSchedulerAdd(scheduler, time(NULL) - 3, 0, PrintInTest,
							"---SchedulerRun runs irrelevant tasks---");
	
	HSchedulerAdd(scheduler, time(NULL) + 0, 0, StopInTest,
															 scheduler);
															 
	HSchedulerRun(scheduler);
	
	if (0 != test_count)
	{
		AddFailedTest("TestSchedulerRun0\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerAdd(scheduler, time(NULL) + 3, 0, PrintInTest,
										"---Started testing SchedulerRun---");
	HSchedulerAdd(scheduler, time(NULL) + 4, 1, IncrementInTest,
															 &test_count);
	HSchedulerAdd(scheduler, time(NULL) + 9, 0, StopInTest,
															 scheduler);
	
	status = HSchedulerRun(scheduler);
	
	if (SCHEDULER_STOP != status)
	{
		AddFailedTest("TestSchedulerRun1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	if (test_count < 5)
	{
		AddFailedTest("TestSchedulerRun2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerClear(scheduler);

	HSchedulerAdd(scheduler, time(NULL) + 3, 0, PrintInTest,
										"---SchedulerRun second run---");
	HSchedulerAdd(scheduler, time(NULL) + 4, 0, IncrementInTest,
															 &test_count);
	HSchedulerAdd(scheduler, time(NULL) + 5, 0, IncrementInTest,
															 &test_count);					
	status = HSchedulerRun(scheduler);
	if (SUCCESS != status)
	{
		AddFailedTest("TestSchedulerRun3\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
										
	HSchedulerDestroy(scheduler);
	
	return 0;
}



static int TestSchedulerStop(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	size_t test_count = 0;
	
	HSchedulerAdd(scheduler, time(NULL) + 2, 0, PrintInTest,
										"---Started testing SchedulerStop---");
	HSchedulerAdd(scheduler, time(NULL) + 3, 1, IncrementInTest,
															 &test_count);
	HSchedulerAdd(scheduler, time(NULL) + 8, 1, StopInTest,
															 scheduler);
	
	HSchedulerRun(scheduler);

	if (test_count < 5)
	{
		AddFailedTest("TestSchedulerStop1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerAdd(scheduler, time(NULL) + 1, 0, PrintInTest,
										"---SchedulerStop second run---");

	HSchedulerRun(scheduler);
	if (test_count > 6)
	{
		AddFailedTest("TestSchedulerStop2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}

	HSchedulerDestroy(scheduler);
	
	return 0;
}

static int TestSchedulerSize(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	ilrd_uid_t get_uid1 = BadUID;
	ilrd_uid_t get_uid2 = BadUID;
	ilrd_uid_t get_uid3 = BadUID;
	size_t test_count = 0;
	size_t get_size = 0;
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 2, 0, PrintInTest,
										"---Started testing SchedulerSize---");
	get_uid2 = HSchedulerAdd(scheduler, time(NULL) + 3, 0, IncrementInTest,
															 &test_count);
	get_uid3 = HSchedulerAdd(scheduler, time(NULL) + 4, 0, StopInTest,
															 scheduler);
	HSchedulerRun(scheduler);
	
	get_size = HSchedulerSize(scheduler);
	if (0 != get_size)
	{
		AddFailedTest("TestSchedulerSize1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 2, 0, PrintInTest,
										"---Started testing SchedulerSize---");
	
	get_size = HSchedulerSize(scheduler);
	if (1 != get_size)
	{
		AddFailedTest("TestSchedulerSize2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	get_uid2 = HSchedulerAdd(scheduler, time(NULL) + 3, 0, IncrementInTest, 
															&test_count);
	
	get_size = HSchedulerSize(scheduler);
	if (2 != get_size)
	{
		AddFailedTest("TestSchedulerSize3\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}															

	get_uid3 = HSchedulerAdd(scheduler, time(NULL) + 4, 0, StopInTest,
																scheduler);
	get_size = HSchedulerSize(scheduler);
	if (3 != get_size)
	{
		AddFailedTest("TestSchedulerSize4\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}								
						 
	HSchedulerRemove(scheduler, get_uid1);
	get_size = HSchedulerSize(scheduler);
	if (2 != get_size)
	{
		AddFailedTest("TestSchedulerSize5\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerRemove(scheduler, get_uid3);
	get_size = HSchedulerSize(scheduler);
	if (1 != get_size)
	{
		AddFailedTest("TestSchedulerSize6\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerRemove(scheduler, get_uid2);
	get_size = HSchedulerSize(scheduler);
	if (0 != get_size)
	{
		AddFailedTest("TestSchedulerSize7\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}

	HSchedulerDestroy(scheduler);
	
	return 0;
}


static int TestSchedulerIsEmpty(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	ilrd_uid_t get_uid1 = BadUID;
	
	if (!HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerIsEmpty1\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_uid1 = HSchedulerAdd(scheduler, time(NULL) + 3, 0, PrintInTest,
								"---Started testing SchedulerIsEmpty---");
	if (HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerIsEmpty2\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerRemove(scheduler, get_uid1);
	if (!HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerIsEmpty3\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerDestroy(scheduler);
	
	return 0;
}


static int TestSchedulerClear(void)
{
	hscheduler_t *scheduler = HSchedulerCreate();
	size_t test_count = 0;
	size_t get_size = 0;
	
	
	HSchedulerAdd(scheduler, time(NULL) + 2, 0, PrintInTest,
										"---Started testing SchedulerClear---");
	HSchedulerAdd(scheduler, time(NULL) + 3, 0, IncrementInTest, 
															&test_count);
															
	HSchedulerClear(scheduler);
	
	if (!HSchedulerIsEmpty(scheduler))
	{
		AddFailedTest("TestSchedulerClear\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	get_size = HSchedulerSize(scheduler);
	if (0 != get_size)
	{
		AddFailedTest("TestSchedulerClear\n");
		HSchedulerDestroy(scheduler);
		
		return 1;
	}
	
	HSchedulerDestroy(scheduler);
	
	return 0;
}
















