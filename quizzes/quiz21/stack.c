#include <string.h>
#include <stdlib.h>

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
	size_t size_malloc = sizeof(struct stack) + (capacity * element_size);
	
	ptr = (stack_t *)malloc(size_malloc);
	
	if (NULL == ptr)
	{
		free(ptr);
		
		return NULL;
	}
	
	ptr -> capacity = capacity;
	ptr -> size = 0;
	ptr -> element_size = element_size;
	ptr -> buffer = (char*)ptr + (sizeof(struct stack));
	
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
	assert(stack->size != 0);

	--(stack->size); 
}

void StackPush(stack_t *stack, void *new_element)
{
	char *dest = NULL;
	
	assert(NULL != stack);
	assert(stack->size != stack->capacity);
	
	dest = stack->buffer + (stack->size * stack->element_size);
	memcpy(dest, new_element, stack->element_size);
	
	++(stack->size);	
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->size == 0);
}

size_t StackGetSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->size;
}

size_t StackGetCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return stack->capacity;
}

void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	assert(stack -> size != 0);

	
	return (stack->buffer + ((stack->size - 1) * stack->element_size));
}





