#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/

#include "cbuffer.h"


void test_CBuffCreate(void);
void test_CBuffSize(void);
void test_CBuffWrite(void);
void test_CBuffRead(void);
void test_CBuffIsEmpty(void);
void test_CBuffFreeSpace(void);


static size_t checker = 0;



int main(void)
{
	
	test_CBuffCreate();
	test_CBuffSize();
	test_CBuffWrite();
	test_CBuffRead();
	test_CBuffIsEmpty();
	test_CBuffFreeSpace();
	
	if(0 == checker)
	{
		printf("\nAll tests passed\n");
	}
	return 0;
}


void test_CBuffCreate(void)
{
	cbuffer_t *buffer = CBuffCreate(30);
	if(NULL == buffer)
	{
		printf("CBuffCreate test failed\n");
		++checker;
		return;
	}
	printf("CBuffCreate test passed\n");
	CBuffDestroy(buffer);
}
	
	
	
void test_CBuffSize(void)
{
	cbuffer_t *buffer = CBuffCreate(30);
	if(NULL == buffer)
	{
		printf("CBuffSize malloc failed\n");
		++checker;
		return;
	}
	if(CBuffSize(buffer) == 30)
	{
		printf("CBuffSize test passed\n");
	}
	else
	{
		printf("CBuffSize test failed\n");
		++checker;
	}
	CBuffDestroy(buffer);
}
	
	
void test_CBuffWrite(void)
{
	cbuffer_t *buffer = CBuffCreate(30);
	char *str = "hello";
	char str2[50];
	CBuffWrite(buffer, str, 2);
	if(28 == CBuffFreeSpace(buffer))
	{
		printf("CBuffWrite test passed\n");
	}
	else
	{
		printf("CBuffWrite test failed\n");
		++checker;
	}
	
	CBuffWrite(buffer, str, 5);
	if(23 == CBuffFreeSpace(buffer))
	{
		printf("CBuffWrite test 2 passed\n");
	}
	else
	{
		printf("CBuffWrite test 2 failed\n");
		++checker;
	}
	
	CBuffRead(buffer, str2, 7);
	CBuffWrite(buffer, str, 30);
	if(0 == CBuffFreeSpace(buffer))
	{
		printf("CBuffWrite test 3 passed\n");
	}
	else
	{
		printf("CBuffWrite test 3 failed\n");
		++checker;
	}
	
	CBuffWrite(buffer, str, 13);
	if(0 == CBuffFreeSpace(buffer))
	{
		printf("CBuffWrite test 4 passed\n");
	}
	else
	{
		printf("CBuffWrite test 4 failed\n");
		++checker;
	}
	
	
	
	CBuffDestroy(buffer);
}
	
	
void test_CBuffRead(void)
{
	cbuffer_t *buffer = CBuffCreate(13);
	char str[15] = {'\0'};
	char str2[10] = {'\0'};
	char *string = "hello world!";
	
	CBuffWrite(buffer, string, 12);
	CBuffRead(buffer, str, 5);
	
	if('o' == str[4] && 'h' == str[0])
	{
		printf("CBuffRead test passed\n");
	}
	else
	{
		printf("CBuffRead test failed\n");
		++checker;
	}
	
	CBuffRead(buffer, str, 2);
	if('w' == str[1])
	{
		printf("CBuffRead test 2 passed\n");
	}
	else
	{
		printf("CBuffRead test 2 failed\n");
		++checker;
	}
	
	CBuffRead(buffer, str2, 64);
	if('!' == str2[4])
	{
		printf("CBuffRead test 3 passed\n");
	}
	else
	{
		printf("CBuffRead test 3 failed\n");
		++checker;
	}
	
	CBuffDestroy(buffer);
}
	
	
void test_CBuffIsEmpty(void)
{
	cbuffer_t *buffer = CBuffCreate(30);
	char str[15];
	char *string = "hello world!";
	
	if( 1 != CBuffIsEmpty(buffer))
	{
		++checker;
	}
	
	CBuffWrite(buffer, string, 11);
	if( 0 != CBuffIsEmpty(buffer))
	{
		++checker;
	}
	
	CBuffRead(buffer, str, 14);
	if( 1 != CBuffIsEmpty(buffer))
	{
		++checker;
	}
	
	if(0 != checker)
	{
		printf("CBuffIsEmpty test failed\n");
	}
	else
	{
		printf("CBuffIsEmpty test passed\n");
	}
	
	CBuffDestroy(buffer);
}
	


void test_CBuffFreeSpace(void)
{
	cbuffer_t *buffer = CBuffCreate(30);
	char str[15];
	char *string = "hello world!";
	
	if( 30 != CBuffFreeSpace(buffer))
	{
		++checker;
	}
	
	CBuffWrite(buffer, string, 11);
	if( 19 != CBuffFreeSpace(buffer))
	{
		++checker;
	}
	
	CBuffRead(buffer, str, 3);
	if( 22 != CBuffFreeSpace(buffer))
	{
		++checker;
	}
	
	if(0 != checker)
	{
		printf("CBuffFreeSpace test failed\n");
	}
	else
	{
		printf("CBuffFreeSpace test passed\n");
	}
	
	CBuffDestroy(buffer);
}


