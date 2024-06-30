#include <assert.h> /* assert */
#include <stdlib.h> /* maloc free */

#include "heap.h"
#include "dvector.h"

static dvector_t *GetDvector(const heap_t *heap);

struct heap
{
	dvector_t *dvector;
	heap_compare_func_t cmp_func;
};


heap_t *HeapCreate(heap_compare_func_t compare_func)
{
	heap_t *heap = NULL;
	size_t size_of_element = sizeof(size_t);
	size_t capacity = 10;
	
	assert(compare_func);
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	heap->dvector =  DvectorCreate(capacity, size_of_element);
	if (NULL == heap->dvector)
	{
		free(heap);
		
		return NULL;
	}
	
	heap->cmp_func = compare_func;
	
	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);
	
	DvectorDestroy(GetDvector(heap));
	free(heap);
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return DvectorSize(GetDvector(heap));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return (0 == HeapSize(heap));
}


/********************* HELPER FUNCTIONS ********************/

static dvector_t *GetDvector(const heap_t *heap)
{
	assert(heap);
	
	return heap->dvector;
}

