#include <stdio.h> /*printf */
#include <stddef.h> /*size_t */

#include "stack.h"

#define CAP 20

static int min_arr[CAP];

int PushNew(stack_t *stack, void *new_element);
int PopNew(stack_t *stack);

int main(void)
{
	size_t elem_size = 4;
	stack_t *stack_ptr = NULL;
	int x = 10;
	int y = 35;
	int z = 1684; 
	int a = -1; 
	int b = -10; 
	stack_ptr = StackCreate(CAP,elem_size);	
	
	printf("min elem in stack is: %d\n", PushNew(stack_ptr,&x));
	printf("min elem in stack is: %d\n", PushNew(stack_ptr,&y));
	printf("min elem in stack is: %d\n", PushNew(stack_ptr,&z));
	printf("min elem in stack is: %d\n", PushNew(stack_ptr,&a));
	printf("min elem in stack is: %d\n", PushNew(stack_ptr,&b));
	
	printf("min elem in stack is: %d\n", PopNew(stack_ptr));
	printf("min elem in stack is: %d\n", PopNew(stack_ptr));
	printf("min elem in stack is: %d\n", PopNew(stack_ptr));
	printf("min elem in stack is: %d\n", PopNew(stack_ptr));
	printf("min elem in stack is: %d\n", PopNew(stack_ptr));
	
	return 0;
}
	
	
	
	
int PushNew(stack_t *stack, void *new_element)
{
	size_t size = 0;
	
	assert(stack);
	
	size = StackGetSize(stack);
	if (0 == size)
	{
		min_arr[size] = *(int*)new_element;
	}	
	else if (*(int*)new_element < min_arr[size - 1])
	{
		min_arr[size] = *(int*)new_element;
	}
	else
	{
		min_arr[size] = min_arr[size - 1];
	}
	
	StackPush(stack, new_element);
	
	return min_arr[size];
}

int PopNew(stack_t *stack)
{
	size_t size = 0;
	
	assert(stack);
	
	StackPop(stack);
	size = StackGetSize(stack);
	
	if (0 == size)
	{
		return 0;
	}
	return min_arr[size - 1];
}
