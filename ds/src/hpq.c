/********************************** 
   Code by: Yan Meiri	
   Project: Heap Priority queue
   Date: 2/07/24
   Review by: 
   Review Date: 
   Approved by: 
   Approval Date: 
**********************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */

#include "hpq.h"
#include "heap.h"

struct hpq
{
	heap_t *heap;
};


hpq_t *HPQCreate(hpq_compare_func_t cmp_func)
{
	hpq_t *hpq_ptr = NULL;
	
	assert(cmp_func);

	hpq_ptr = (hpq_t*)malloc(sizeof(hpq_t));
	if (NULL == hpq_ptr)
	{
		return NULL;
	}
	
	
	hpq_ptr->heap = HeapCreate(cmp_func);
	if (NULL == hpq_ptr->heap)
	{
		free(hpq_ptr);
		
		return NULL;
	}
	
	return hpq_ptr;
}

void HPQDestroy(hpq_t *queue)
{
	assert(queue);
	assert(queue->heap);
	
	HeapDestroy(queue->heap);
	free(queue);
}

int HPQEnqueue(hpq_t *queue, void *data)
{
	int status = 0;
	
	assert(queue);
	assert(queue->heap);
	
	status = HeapPush(queue->heap, data);

	return status;
}

void *HPQDequeue(hpq_t *queue)
{
	void *data = NULL;
	
	assert(queue);
	assert(queue->heap);
	
	data = HeapPeek(queue->heap);
	
	HeapPop(queue->heap);
	
	return data;
}

void *HPQPeek(const hpq_t *queue)
{
	assert(queue);
	assert(queue->heap);
	
	return HeapPeek(queue->heap);
}

int HPQIsEmpty(const hpq_t *queue)
{
	assert(queue);
	assert(queue->heap);
	
	return HeapIsEmpty(queue->heap);
}

size_t HPQSize(const hpq_t *queue)
{
	assert(queue);
	assert(queue->heap);
	
	return HeapSize(queue->heap);
}

void HPQClear(hpq_t *queue)
{
	assert(queue);
	assert(queue->heap);
	
	while(!HPQIsEmpty(queue))
	{
		HPQDequeue(queue);
	}
}

void *HPQErase(hpq_t *queue, hpq_match_func_t is_match, void *param)
{
	void *data = NULL;
	
	assert(queue);
	assert(queue->heap);
	assert(is_match);

	data = HeapRemove(queue->heap, is_match, param);
	if (NULL == data)
	{
		return NULL;
	}
	
	return data;
}
















