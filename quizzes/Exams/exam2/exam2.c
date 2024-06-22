#include <stdio.h> /* printf */
#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#define Q_SIZE 5

typedef struct queue
{
	char m_queue[Q_SIZE];
	size_t m_elements_in_q;
	size_t m_first_element_index;
} cqueue_t;

int WhichNumberIsMissing(int arr[]);
int QueuePushChar(cqueue_t *cqueue, char element);
int QueuePopChar(cqueue_t *cqueue);
char QueuePeek(cqueue_t *cqueue);
void TestWhoIsMissing(void);
void TestQueuePushChar(void);
void TestQueuePopChar(void);


int main(void)
{
	TestWhoIsMissing();
	TestQueuePopChar();
	TestQueuePushChar();
	
	return 0;
	
}

void TestWhoIsMissing(void)
{
	int arr[1023] = {0};
	size_t i = 0;
	int missing = 1023;
	
	for (; i < 1024; ++i)
	{
		arr[i] = i;
	}
	arr[missing] = 1024;
	
	if (missing != WhichNumberIsMissing(arr))
	{
		printf("Failed Missing test\n");
		
		return;	
	}
	
	printf("PASSED Missing test\n");
}

void TestQueuePushChar(void)
{
	char *str = "HELLO!";
	int status = 0;
	size_t loop_count = 0;
	cqueue_t queue = {0};
	
	while(loop_count < 6)
	{
		status += QueuePushChar(&queue, str[loop_count]);
		++loop_count;
	}
	
	printf("---------------TestQueuePushChar---------------\n\n");
	
	printf("status should be -1: %d\n\n", status);
}


void TestQueuePopChar(void)
{
	char *str = "HELLO!";
	int status = 0;
	size_t loop_count = 0;
	cqueue_t queue = {0};
	
	printf("---------------TestQueuePopChar---------------\n\n");
	status = QueuePopChar(&queue);
	printf("status should be -1: %d\n\n", status);
	
	while(loop_count < 5)
	{
		QueuePushChar(&queue, str[loop_count]);
		++loop_count;
	}
	
	printf("first char before pop: %c\n\n", QueuePeek(&queue));
	
	status = QueuePopChar(&queue);
	printf("status should be 0: %d\n\n", status);
	printf("first char after pop: %c\n\n", QueuePeek(&queue));
	
	status = QueuePushChar(&queue, str[loop_count]);
	printf("status should be 0: %d\n\n", status);
}

int WhichNumberIsMissing(int arr[])
{
	size_t sum_0_1024 = 0;
	size_t sum_arr = 0;
	size_t i = 0;
	
	assert(arr);
	
	for(; i < 1024; ++i)
	{
		sum_0_1024 += i;
		sum_arr += arr[i];
	}
	
	sum_0_1024 += 1024;
	sum_0_1024 -= sum_arr;
	
	return sum_0_1024;
}

int QueuePushChar(cqueue_t *cqueue, char element)
{
	size_t index_to_push = 0;
	
	assert(cqueue);
	
	if (cqueue->m_elements_in_q == Q_SIZE)
	{
		return -1;
	}
	
	index_to_push = (cqueue->m_elements_in_q + cqueue->m_first_element_index) %
					 Q_SIZE;

	cqueue->m_queue[index_to_push] = element;
	
	++(cqueue->m_elements_in_q);
	
	return 0;
}

int QueuePopChar(cqueue_t *cqueue)
{
	assert(cqueue);
	
	if (0 == cqueue->m_elements_in_q)
	{
		return -1;
	}
	
	cqueue->m_first_element_index = ((cqueue->m_first_element_index) + 1) %
									 Q_SIZE;
	
	--(cqueue->m_elements_in_q);
	
	return 0;
}

char QueuePeek(cqueue_t *cqueue)
{
	assert(cqueue);
	
	return (cqueue->m_queue[cqueue->m_first_element_index]);
}


























