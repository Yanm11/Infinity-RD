#include <stddef.h> /*size_t*/
#include <stdio.h> /*printf*/

#include "queue.h"

void TestAll(void);
void TestCreateDestroy(void);
void TestEnqueue(void);
void TestDequeue(void);
void TestQSize(void);
void TestQPeek(void);
void TestQIsEmpty(void);
void TestAppend(void);

int main(void)
{
    TestAll();
	return 0;
}

void TestAll(void) 
{
    /* Call all test functions */
    TestCreateDestroy();
    TestEnqueue();
    TestDequeue();
    TestQSize();
    TestQPeek() ;
    TestQIsEmpty();
 	TestAppend();
 	
    printf("All tests passed.\n");
}

void TestCreateDestroy(void) 
{
	queue_t *queue = QCreate();
	if (NULL == queue)
	{
		printf("Test Create FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test Create Destroy PASSED!\n");
}

void TestEnqueue(void) 
{
	queue_t *queue = QCreate();
	int data[] = {10,20,30,40};
	size_t count = 0;
	int elem = 0;
	int status = 0;
	
	status = QEnqueue(queue, data);
	++count;
	elem = *(int*)(QPeek(queue));
	
	if ((0 != status) || (data[0] != elem) || (QSize(queue) != count))
	{
		printf("Test Enqueue FAILED\n");
		return;
	}
	
	status = QEnqueue(queue, data + 1);
	++count;
	elem = *(int*)(QPeek(queue));
	
	if ((0 != status) || (data[0] != elem) || (QSize(queue) != count))
	{
		printf("Test Enqueue FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test Enqueue PASSED!\n");
}

void TestDequeue(void) 
{
	queue_t *queue = QCreate();
	int data[] = {10,20,30,40};
	size_t count = 0;
	int elem = 0;
	
	QEnqueue(queue, data);
	++count;
	QEnqueue(queue, data + 1);
	++count;
	QDequeue(queue);
	--count;
	
	elem = *(int*)(QPeek(queue));
	
	if ((data[1] != elem) || (QSize(queue) != count))
	{
		printf("Test Dequeue FAILED\n");
		return;
	}
	
	QDequeue(queue);
	--count;
	
	if ((QSize(queue) != count))
	{
		printf("Test Dequeue FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test Dequeue PASSED!\n");
}

void TestQSize(void) 
{
	queue_t *queue = QCreate();
	int data[] = {10,20,30,40};
	size_t count = 0;

	
	QEnqueue(queue, data);
	++count;
	QEnqueue(queue, data + 1);
	++count;
	QDequeue(queue);
	--count;
	
	
	if ((QSize(queue) != count))
	{
		printf("Test QSize FAILED\n");
		return;
	}
	
	QEnqueue(queue, data + 2);
	++count;
	QEnqueue(queue, data + 3);
	++count;
	
	if ((QSize(queue) != count))
	{
		printf("Test QSize FAILED\n");
		return;
	}
	
	QDequeue(queue);
	--count;
	QDequeue(queue);
	--count;
	QDequeue(queue);
	--count;
	
	if ((QSize(queue) != count))
	{
		printf("Test QSize FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test QSize PASSED!\n");
}

void TestQPeek(void) 
{
	queue_t *queue = QCreate();
	int data[] = {10,20,30,40};
	int elem = 0;
	
	QEnqueue(queue, data);
	QEnqueue(queue, data + 1);
	QEnqueue(queue, data + 2);
	QEnqueue(queue, data + 3);
	elem = *(int*)(QPeek(queue));

	if (elem != data[0])
	{
		printf("Test QPeek FAILED\n");
		return;
	}
	
	QDequeue(queue);
	elem = *(int*)(QPeek(queue));
	
	if (elem != data[1])
	{
		printf("Test QPeek FAILED\n");
		return;
	}
	
	QDequeue(queue);
	elem = *(int*)(QPeek(queue));
	
	if (elem != data[2])
	{
		printf("Test QPeek FAILED\n");
		return;
	}
	
	QDequeue(queue);
	elem = *(int*)(QPeek(queue));
	
	if (elem != data[3])
	{
		printf("Test QPeek FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test QPeek PASSED!\n");
}


void TestQIsEmpty(void) 
{
	queue_t *queue = QCreate();
	int data[] = {10,20,30,40};

	if (1 != QIsEmpty(queue))
	{
		printf("Test QIsEmpty FAILED\n");
		return;
	}
	
	QEnqueue(queue, data);
	QEnqueue(queue, data + 1);
	
	if (0 != QIsEmpty(queue))
	{
		printf("Test QIsEmpty FAILED\n");
		return;
	}
	
	QDequeue(queue);
	QDequeue(queue);

	if (1 != QIsEmpty(queue))
	{
		printf("Test QIsEmpty FAILED\n");
		return;
	}
	
	QDestroy(queue);
	
	printf("Test QIsEmpty PASSED!\n");
}

void TestAppend(void) 
{
	queue_t *queue_dest = QCreate();
	queue_t *queue_src = QCreate();
	int data_dest[] = {10,20,30,40};
	int data_src[] = {50,60,70};
	size_t size_dest = 4;
	size_t size_src = 3;
	size_t append = size_dest + size_src;
	int elem_dest = 0;
	int elem_src = 0;
	
	QEnqueue(queue_dest, data_dest);
	QEnqueue(queue_dest, data_dest + 1);
	QEnqueue(queue_dest, data_dest + 2);
	QEnqueue(queue_dest, data_dest + 3);
	
	QEnqueue(queue_src, data_src);
	QEnqueue(queue_src, data_src + 1);
	QEnqueue(queue_src, data_src + 2);
	
	
	elem_dest = *(int*)(QPeek(queue_dest));
	elem_src = *(int*)(QPeek(queue_src));	
	
	if ((elem_dest != data_dest[0]) || (elem_src != data_src[0]))
	{
		printf("Test QAppend FAILED\n");
		return;
	}

	if ((QSize(queue_dest) != size_dest) || (QSize(queue_src) != size_src))
	{
		printf("Test QAppend FAILED\n");
		return;
	}
	
	QAppend(queue_dest, queue_src);
	elem_dest = *(int*)(QPeek(queue_dest));
	
	if ((elem_dest != data_dest[0]) ||
	    (QSize(queue_dest) != append) || 
	    (!QIsEmpty(queue_src)))
	{
		printf("Test QAppend FAILED\n");
		return;
	}
	
	QDequeue(queue_dest);
	QDequeue(queue_dest);
	QDequeue(queue_dest);
	QDequeue(queue_dest);
	QDequeue(queue_dest);
	QDequeue(queue_dest);
	
	elem_dest = *(int*)(QPeek(queue_dest));
	
	if (elem_dest != data_src[2])
	{
		printf("Test QAppend FAILED\n");
		return;
	}
	
	QDestroy(queue_dest);
	QDestroy(queue_src);
	printf("Test QAppend PASSED!\n");
}
