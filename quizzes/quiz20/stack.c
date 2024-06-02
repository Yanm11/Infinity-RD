#include "stack.h"
/*
yan meiri
approved by Or
4.5.2024
*/

/* 
compile
gd stack.c ../test/test_stack.c -I ../include/ -o ../bin/debug/test_stack 
execute
 ../bin/debug/test_stack
  */

struct stack
{
    size_t capacity;
    size_t size;
    size_t element_size;
    char *buffer;
};


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t *ptr = NULL;
	size_t size_malloc = (4 * sizeof(size_t)) +(capacity * element_size);
	
	ptr = (stack_t *)malloc(size_malloc);
	
	if (NULL == ptr)
	{
		free(ptr);
		return NULL;
	}
	
	ptr -> capacity = capacity * element_size;
	ptr -> size = 0;
	ptr -> element_size = element_size;
	ptr -> buffer = (char*)(ptr + (4 * sizeof(size_t)));
	
	return ptr;
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free(stack);
}

void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack -> size != 0);

	stack -> size -= stack -> element_size; 
}

void StackPush(stack_t *stack, void *new_element)
{
	size_t i = 0;
	char *ptr_elem = (char*)new_element;
	
	assert(NULL != stack);
	assert(stack -> size != stack -> capacity);

	
	for (;i < stack -> element_size; ++i)
	{
		*((stack -> buffer) + (stack -> size) + i) = *ptr_elem;
		++ptr_elem;
	}
	
	stack -> size += stack -> element_size; 	
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack -> size == 0);
}

size_t StackGetSize(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack -> size / stack -> element_size);
}

size_t StackGetCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	return (stack -> capacity / stack -> element_size);
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(stack -> size != 0);

	
	return (stack -> buffer + (stack -> size - stack -> element_size));
}
