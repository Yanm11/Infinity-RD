#include <stdlib.h> /* size_t malloc() realloc() free() */
#include <stdio.h> /* perror() */
#include <assert.h> /* assert() */

#include "dvector.h"

#define GROWTHFACTOR 2

struct dvector
{
    size_t capacity;
    size_t size;
    size_t element_size;
    char *buffer;
};

dvector_t *DvectorCreate(size_t capacity, size_t element_size)
{
	dvector_t *vector_ptr = NULL;

	vector_ptr = (dvector_t*)malloc(sizeof(dvector_t));
	
	if (NULL == vector_ptr)
	{
		free(vector_ptr);
		return NULL;
	}
	
	vector_ptr->capacity = capacity;
	vector_ptr->size = 0;
	vector_ptr->element_size = element_size;
	vector_ptr->buffer = (char*)malloc(capacity * element_size);
	
	if (NULL == vector_ptr -> buffer)
	{
		free(vector_ptr -> buffer);
		return NULL;
	}
	
	return vector_ptr;
}

void DvectorDestroy(dvector_t *vector)
{
	assert(NULL != vector);
	free(vector->buffer);
	free(vector);
}

int DvectorPushBack(dvector_t *vector, const void *new_element)
{
	size_t i = 0;
	char *ptr_elem = (char*)new_element;
	
	assert(NULL != vector);
	if (vector->size == vector->capacity)
	{
		int status = DvectorReserve(vector, vector->capacity * GROWTHFACTOR);
		if (status == -1)
		{
			return -1;
		}	
	}

	
	for (;i < vector->element_size; ++i)
	{
		*((vector->buffer) + (vector->size) * (vector->element_size) + i) = *ptr_elem;
		++ptr_elem;
	}
	
	vector->size += 1;
	
	return 0; 	
}

void DvectorPopBack(dvector_t *vector)
{
	assert(NULL != vector);
	vector->size -= 1;	
}

int DvectorShrink(dvector_t *vector)
{
	return DvectorReserve(vector, vector->size);
}

int DvectorReserve(dvector_t *vector, size_t new_size)
{
	size_t total_size = new_size * vector->element_size;
	vector->buffer = (char*)realloc(vector->buffer, total_size);
	
	if (NULL == vector->buffer)
	{
		free(vector->buffer);
		return -1;
	}
	
	vector->capacity = new_size;
	
	return 0;
}

size_t DvectorSize(const dvector_t *vector)
{
	assert(NULL != vector);
	return vector->size;
}

size_t DvectorCapacity(const dvector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}

void *DvectorGetElement(const dvector_t *vector, size_t index)
{
	assert(NULL != vector);
	return (vector->buffer + vector->element_size * index);
}

