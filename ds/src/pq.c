#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free */

#include "pq.h"
#include "sortedlist.h"

struct pq
{
	sortedlist_t *list;
};


pq_t *PQCreate(pq_compare_func_t cmp_func)
{
	pq_t *pq_ptr = (pq_t*)malloc(sizeof(pq_t));
	
	if (NULL ==pq_ptr)
	{
		return NULL;
	}
	
	assert(cmp_func);
	
	pq_ptr->list = SortedlistCreate(cmp_func);
	
	if (NULL == pq_ptr->list)
	{
		free(pq_ptr);
		
		return NULL;
	}
	
	return pq_ptr;
}

void PQDestroy(pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	SortedlistDestroy(queue->list);
}

int PQEnqueue(pq_t *queue, void *data)
{
	sortedlist_iter_t iter = {NULL};
	int status = 0;
	
	assert(queue);
	assert(queue->list);
	assert(data);
	
	iter = SortedlistInsert(queue->list, data);
	status = SortedlistIsSameIter(iter, SortedlistGetEnd(queue->list));

	return status;
}

void *PQDequeue(pq_t *queue)
{
	void *data = NULL;
	sortedlist_iter_t iter = {NULL};
	
	assert(queue);
	assert(queue->list);
	
	iter = SortedlistGetBegin(queue->list);
	data = SortedlistGetData(iter);
	SortedlistRemove(iter);
	
	return data;
}

void *PQPeek(const pq_t *queue)
{
	void *data = NULL;
	sortedlist_iter_t iter = {NULL};
	
	assert(queue);
	assert(queue->list);
	
	iter = SortedlistGetBegin(queue->list);
	data = SortedlistGetData(iter);
	
	return data;
}

int PQIsEmpty(const pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	return SortedlistIsEmpty(queue->list);
}

size_t PQSize(const pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	return SortedlistSize(queue->list);
}

void PQClear(pq_t *queue)
{
	assert(queue);
	assert(queue->list);
	
	while(!PQIsEmpty(queue))
	{
		PQDequeue(queue);
	}
}

void *PQErase(pq_t *queue, pq_match_func_t is_match, void *param)
{
	void *data = NULL;
	sortedlist_iter_t from = {NULL};
	sortedlist_iter_t to = {NULL};
	
	assert(queue);
	assert(queue->list);
	
	from = SortedlistGetBegin(queue->list);
	to = SortedlistGetEnd(queue->list);
	
	from = SortedlistFindIf(from, to, is_match, param);
	
	if (SortedlistIsSameIter(from, to))
	{
		return NULL;
	}
	
	data = SortedlistGetData(from);
	SortedlistRemove(from);
	
	return data;
}
















