#include <stdio.h> /*printf */
#include <stddef.h> /*size_t */

#include "stack.h"

#define CAP 20

typedef struct queue
{
	stack_t *stack_in;
	stack_t *stack_out;
}queue_t;


void Enqueue(queue_t *queue, void *new_elem);
void *Dequeue(queue_t *queue);

int main(void)
{
	queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
	size_t elem_size = 4;
	int x = 10;
	int y = 35;
	int z = 1684; 
	int a = -1; 
	int b = -10; 
	queue->stack_in = StackCreate(CAP,elem_size);
	queue->stack_out = StackCreate(CAP,elem_size);
	
	Enqueue(queue, &x);
	Enqueue(queue, &y);
	Enqueue(queue, &z);
	Enqueue(queue, &a);
	
	
	
	printf("first element in queue is: %d\n", *(int*)Dequeue(queue));
	printf("second element in queue is: %d\n", *(int*)Dequeue(queue));
	printf("third element in queue is: %d\n", *(int*)Dequeue(queue));
	
	Enqueue(queue, &b);
	
	printf("forth element in queue is: %d\n", *(int*)Dequeue(queue));
	printf("fifth element in queue is: %d\n", *(int*)Dequeue(queue));
	
	
	return 0;
}

void Enqueue(queue_t *queue, void *new_elem)
{
	assert(queue);
	
	StackPush(queue->stack_in, new_elem);
}

void *Dequeue(queue_t *queue)
{
	void *element = NULL;
	
	assert(queue);
	
	if (StackIsEmpty(queue->stack_out))
	{
		while (!StackIsEmpty(queue->stack_in))
		{
			StackPush(queue->stack_out, StackPeek(queue->stack_in));
			StackPop(queue->stack_in);
		}
	}
	
	element = StackPeek(queue->stack_out);
	StackPop(queue->stack_out);
	
	return element;
}
	
