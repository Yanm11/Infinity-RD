#include <stdlib.h> /* size_t malloc() realloc() free() */
#include <assert.h> /* assert() */

#include "dvector.h"

#define GROWTHFACTOR 2

/*
yan meiri
checked by or
*/

static int IsDvectorFull(dvector_t *vector);

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
	
	assert(0 < element_size);
	assert(0 < capacity);
	
	vector_ptr = (dvector_t*)malloc(sizeof(dvector_t));
	
	if (NULL == vector_ptr)
	{
		return NULL;
	}
	
	vector_ptr->capacity = capacity;
	vector_ptr->size = 0;
	vector_ptr->element_size = element_size;
	vector_ptr->buffer = (char*)malloc(capacity * element_size);
	
	if (NULL == vector_ptr -> buffer)
	{
		free(vector_ptr);
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
	char *ptr_elem = NULL;
	
	assert(vector);
	assert(new_element);
	
	ptr_elem = (char*)new_element;
	
	if (IsDvectorFull(vector))
	{
		int status = DvectorReserve(vector, vector->capacity * GROWTHFACTOR);
		if (status == -1)
		{
			return -1;
		}	
	}

	
	for (;i < vector->element_size; ++i)
	{
		*((vector->buffer)+(vector->size)*(vector->element_size)+i)=*ptr_elem;
		++ptr_elem;
	}
	
	vector->size += 1;
	
	return 0; 	
}

static int IsDvectorFull(dvector_t *vector)
{
	assert(vector);
	
	return (vector->size == vector->capacity);
}

void DvectorPopBack(dvector_t *vector)
{
	assert(vector);
	vector->size -= 1;	
}

int DvectorShrink(dvector_t *vector)
{
	assert(vector);
	
	return DvectorReserve(vector, vector->size);
}

int DvectorReserve(dvector_t *vector, size_t new_size)
{
	size_t total_size = 0;
	char *ptr_realloc = NULL;
	
	assert(vector);
	assert(0 <= new_size);
	
	total_size = new_size * vector->element_size;
	ptr_realloc =(char*)realloc(vector->buffer, total_size);
	
	if (NULL == ptr_realloc)
	{
		return -1;
	}
	
	if (new_size > vector->size)
	{
		vector->size = new_size;
	}
	
	vector->buffer = ptr_realloc;
	
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
	assert(vector->size >= index);
	
	return (vector->buffer + vector->element_size * index);
}

