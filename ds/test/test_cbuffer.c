#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */

#include "cbuffer.h"

#define TESTNUM 5

static char failed_tests_print[200] = {'\0'};

int TestFreeSpace();
int TestSize();
int TestRead();
int TestWrite();
int TestIsEmpty();

void AddFailedTest(const char *str);

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestFreeSpace();
	printf("Tested FreeSpace\n");
	failed_tests_num += TestSize();
	printf("Tested Size\n");
	failed_tests_num += TestRead();
	printf("Tested Read\n");
	failed_tests_num += TestWrite();
	printf("Tested Write\n");
	failed_tests_num += TestIsEmpty();
	printf("Tested IsEmpty\n");
	
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

int TestFreeSpace()
{
	cbuffer_t *buffer = CBuffCreate(5);
	size_t get_free_space = 0;
	char src[] = "Hello1234?!";
	char dest[5] = {'\0'};
	int one = 1;
	
	get_free_space = CBuffFreeSpace(buffer);
	
	if (5 != get_free_space)
	{
		AddFailedTest("TestFreeSpace1\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src, 5);
	get_free_space = CBuffFreeSpace(buffer);
	
	if (0 != get_free_space)
	{
		AddFailedTest("TestFreeSpace2\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 3);
	get_free_space = CBuffFreeSpace(buffer);
	
	if (3 != get_free_space)
	{
		AddFailedTest("TestFreeSpace3\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+5, 4);
	get_free_space = CBuffFreeSpace(buffer);
	
	if (0 != get_free_space)
	{
		AddFailedTest("TestFreeSpace4\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 3);
	get_free_space = CBuffFreeSpace(buffer);
	
	if (3 != get_free_space)
	{
		AddFailedTest("TestFreeSpace5\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+9, 2);
	get_free_space = CBuffFreeSpace(buffer);
	
	if (1 != get_free_space)
	{
		AddFailedTest("TestFreeSpace6\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 1);
	CBuffWrite(buffer, &one, 4);
	CBuffWrite(buffer, src, 1);
	
	get_free_space = CBuffFreeSpace(buffer);
	
	if (0 != get_free_space)
	{
		AddFailedTest("TestFreeSpace6\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffDestroy(buffer);
	return 0;
}

int TestSize()
{
	cbuffer_t *buffer = CBuffCreate(5);
	size_t get_size = 0;
	char src[] = "Hello1234?!";
	char dest[5] = {'\0'};
	
	get_size = CBuffSize(buffer);
	
	if (5 != get_size)
	{
		AddFailedTest("TestSize\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src, 5);
	get_size = CBuffSize(buffer);
	
	if (5 != get_size)
	{
		AddFailedTest("TestSize\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 3);
	get_size = CBuffSize(buffer);
	
	if (5 != get_size)
	{
		AddFailedTest("TestSize\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+5, 4);
	get_size = CBuffSize(buffer);
	
	if (5 != get_size)
	{
		AddFailedTest("TestSize\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 3);
	get_size = CBuffSize(buffer);
	
	if (5 != get_size)
	{
		AddFailedTest("TestSize\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffDestroy(buffer);
	return 0;
}

int TestRead()
{
	cbuffer_t *buffer = CBuffCreate(5);
	char src[] = "Hello1234?!";
	char dest[5] = {'\0'};
	
	CBuffWrite(buffer, src, 5);
	CBuffRead(buffer, dest, 3);
	
	if (0 != strncmp(dest, src, 3))
	{
		AddFailedTest("TestRead1\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+5, 4);
	CBuffRead(buffer, dest, 3);

	if (0 != strncmp(dest, src+4, 3))
	{
		AddFailedTest("TestRead2\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+9, 2);
	CBuffRead(buffer, dest, 12);

	if (0 != strncmp(dest, src+7, 3))
	{
		AddFailedTest("TestRead3\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffDestroy(buffer);
	return 0;
}

int TestWrite()
{
	cbuffer_t *buffer = CBuffCreate(5);
	char src[] = "Hello1234?!";
	char dest[5] = {'\0'};
	
	CBuffWrite(buffer, src, 5);
	CBuffWrite(buffer, src+5, 4);
	CBuffRead(buffer, dest, 4);

	if (0 != strncmp(dest, src+4, 4))
	{
		AddFailedTest("TestWrite1\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src, 5);
	CBuffRead(buffer, dest, 5);

	if (0 != strncmp(dest, src, 5))
	{
		AddFailedTest("TestWrite2\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffDestroy(buffer);
	return 0;
}


int TestIsEmpty()
{
	cbuffer_t *buffer = CBuffCreate(5);
	int is_empty = 0;
	char src[] = "Hello1234?!";
	int one = 1;
	char dest[5] = {'\0'};
	
	is_empty = CBuffIsEmpty(buffer);
	
	if (1 != is_empty)
	{
		AddFailedTest("TestIsEmpty1\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src, 4);
	is_empty = CBuffIsEmpty(buffer);
	
	if (0 != is_empty)
	{
		AddFailedTest("TestIsEmpty2\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 3);
	is_empty = CBuffIsEmpty(buffer);
	
	if (0 != is_empty)
	{
		AddFailedTest("TestIsEmpty3\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 1);
	is_empty = CBuffIsEmpty(buffer);
	
	if (1 != is_empty)
	{
		AddFailedTest("TestIsEmpty4\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, src+4, 4);
	is_empty = CBuffIsEmpty(buffer);
	
	if (0 != is_empty)
	{
		AddFailedTest("TestIsEmpty5\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffRead(buffer, dest, 4);
	is_empty = CBuffIsEmpty(buffer);
	
	if (1 != is_empty)
	{
		AddFailedTest("TestIsEmpty6\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffWrite(buffer, &one, 4);
	CBuffWrite(buffer, src, 1);
	is_empty = CBuffIsEmpty(buffer);
	
	if (0 != is_empty)
	{
		AddFailedTest("TestIsEmpty6\n");
		CBuffDestroy(buffer);
		return 1;
	}
	
	CBuffDestroy(buffer);
	return 0;
}









