#include <stdio.h> /*printf */
#include "stack.h"

void TestCreate(stack_t *stack_ptr);
void TestPop(stack_t *stack_ptr);
void TestPush(stack_t *stack_ptr, int *new_element);
void TestIsEmpty(stack_t *stack_ptr , int empty);
void TestGetSize(stack_t *stack_ptr , size_t size);
void TestGetCapacity(stack_t *stack_ptr , size_t cap);
void TestPeek(stack_t *stack_ptr , int peek);

int main(void)
{
	size_t capacity = 20;
	size_t elem_size = 4;
	stack_t *stack_ptr = NULL;
	int x = 10;
	int y = 35;
	int z = 1684; 
	
	stack_ptr = StackCreate(capacity,elem_size);
	
	TestCreate(stack_ptr);
	
	TestGetCapacity(stack_ptr, capacity);
	TestGetSize(stack_ptr, 0);
	
	TestPush(stack_ptr, &x);
	TestPush(stack_ptr, &y);
	TestPush(stack_ptr, &z);
	
	TestGetSize(stack_ptr, 3);
	
	TestIsEmpty(stack_ptr, 0);
	
	TestPeek(stack_ptr, 1684);
	TestPop(stack_ptr);
	
	TestPeek(stack_ptr, 35);
	TestPop(stack_ptr);
	
	TestPeek(stack_ptr, 10);
	TestPop(stack_ptr);
	
	TestIsEmpty(stack_ptr, 1);
	
	TestPush(stack_ptr, &z);
	
	TestIsEmpty(stack_ptr, 0);
	
	StackDestroy(stack_ptr);
	
	return 0;
}

void TestCreate(stack_t *stack_ptr)
{
	if (NULL != stack_ptr)
	{
		printf("Create Stack PASSED\n");
	} 
	else
	{
		printf("Create Stack FAILED\n");
	}
	printf("-------------------\n");
}

void TestPop(stack_t *stack_ptr)
{
	size_t size = StackGetSize(stack_ptr);
	size_t new_size = 0;
	StackPop(stack_ptr);
	new_size = StackGetSize(stack_ptr);
	
	if ( new_size == (size - 1))
	{
		printf("Pop Stack PASSED\n");
	} 
	else
	{
		printf("Pop Stack FAILED\n");
	}
	printf("-------------------\n");
}

void TestPush(stack_t *stack_ptr, int *new_element)
{
	
	size_t size = StackGetSize(stack_ptr);
	size_t new_size = 0;
	StackPush(stack_ptr, new_element);
	new_size = StackGetSize(stack_ptr);
	
	if ( new_size == (size + 1))
	{
		printf("Push Stack PASSED\n");
	} 
	else
	{
		printf("Push Stack FAILED\n");
	}
	printf("-------------------\n");
}

void TestIsEmpty(stack_t *stack_ptr , int empty)
{	
	if (StackIsEmpty(stack_ptr) == empty)
	{
		printf("Empty Test PASSED\n");
	}
	else
	{
		printf("Empty Test FAILED\n");
	}
	printf("-------------------\n");
}

void TestGetSize(stack_t *stack_ptr , size_t size)
{	
	if (StackGetSize(stack_ptr) == size)
	{
		printf("Size Test PASSED\n");
	}
	else
	{
		printf("Size Test FAILED\n");
	}
	printf("-------------------\n");
}

void TestGetCapacity(stack_t *stack_ptr , size_t cap)
{	
	if (StackGetCapacity(stack_ptr) == cap)
	{
		printf("Capacity Test PASSED\n");
	}
	else
	{
		printf("Capacity Test FAILED\n");
	}
	printf("-------------------\n");
}

void TestPeek(stack_t *stack_ptr , int peek)
{	
	if (*(int*)StackPeek(stack_ptr) == peek)
	{
		printf("Peek Test PASSED\n");
	}
	else
	{
		printf("Peek Test FAILED\n");
	}
	printf("-------------------\n");
}
