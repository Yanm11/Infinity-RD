#include <stdio.h> /* printf */
#include <time.h> /* time */
#include <unistd.h> /* getpid */

#include "uid.h"

void TestCreate();
void TestIsSame();

static int check = 0;

int main(void)
{
	printf("----- test create start -----\n");
	
	TestCreate();
	
	printf("----- test create end -----\n\n");
	
	printf("----- test IsSame start -----\n");
	
	TestIsSame();
	
	printf("----- test IsSame end -----\n\n");
	
	if (check > 0)
	{
		printf("failed in %d tests\n", check);
		return 0;
	}
	
	printf("PASSED ALL TESTS!\n");
	
	return 0;
}


void TestCreate()
{
	ilrd_uid_t UID = UIDCreate();
	
	if (UID.timestamp == 0 &&
		UID.counter == 0 &&
		UID.pid == 0)
	{
		printf("test Create FAILED!\n");
		++check;
		return;
	}
	
	if (UID.timestamp != time(NULL) &&
		UID.counter != 1 &&
		UID.pid != getpid())
	{
		printf("test Create FAILED2!\n");
		++check;
		return;
	}
	
	sleep(1);
	
	UID = UIDCreate();
	
	if (UID.timestamp != time(NULL) &&
		UID.counter != 2 &&
		UID.pid != getpid())
	{
		printf("test Create FAILED3!\n");
		++check;
		return;
	}

	printf("test Create PASSED!\n");
}

void TestIsSame()
{
	ilrd_uid_t UID = UIDCreate();
	
	ilrd_uid_t UID2 = UIDCreate();
	
	ilrd_uid_t UID3 = UIDCreate();
	
	if (!IsSameUID(UID, UID))
	{
		printf("test IsSame FAILED!\n");
		++check;
		return;
	}
	
	if(IsSameUID(UID, UID2))
	{
		printf("test IsSame FAILED2!\n");
		++check;
		return;
	}
	
	if(IsSameUID(UID, BadUID))
	{
		printf("test IsSame FAILED3!\n");
		++check;
		return;
	}
	
	if(IsSameUID(UID2, BadUID))
	{
		printf("test IsSame FAILED4!\n");
		++check;
		return;
	}
	
	if(IsSameUID(UID2, UID3))
	{
		printf("test IsSame FAILED5!\n");
		++check;
		return;
	}

	if(IsSameUID(UID, UID3))
	{
		printf("test IsSame FAILED6!\n");
		++check;
		return;
	}
	
	
	printf("test IsSame PASSED!\n");
}




