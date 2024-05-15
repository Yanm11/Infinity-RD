/* 
yan meiri
checked by ido
*/

#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "sllist.h"
#include "queue.h"


struct queue
{
	sllist_t *list;
};

queue_t *QCreate(void)
{
	queue_t *ptr_queue = (queue_t *)malloc(sizeof(queue_t));

	if (NULL == ptr_queue)
	{
		return NULL;
	}
	
	ptr_queue->list = SllistCreate();
	
	if (NULL == ptr_queue->list)
	{
		free(ptr_queue);
		
		return NULL;
	}
	
	return ptr_queue;
}

void QDestroy(queue_t *queue)
{
	assert(NULL != queue);
	SllistDestroy(queue->list);
	free(queue);
}

int QEnqueue(queue_t *queue, void *data)
{
	sllist_iter_t iter = NULL;
	
	assert(NULL != queue);
	
	iter = SllistInsertBefore(queue->list, data, SllistEnd(queue->list));
	
	if (SllistIterIsEqual(iter, SllistEnd(queue->list)))
	{
		return 1;
	}
	
	return 0;
}

void QDequeue(queue_t *queue)
{
	assert(NULL != queue);
	SllistRemove(SllistBegin(queue->list));
}

size_t QSize(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SllistCount(queue->list);
}

void *QPeek(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SllistGetData(SllistBegin(queue->list));
}

int QIsEmpty(const queue_t *queue)
{
	assert(NULL != queue);
	
	return SllistIsEmpty(queue->list);
}

void QAppend(queue_t *dest_queue, queue_t *src_queue)
{
	assert(NULL != dest_queue);
	assert(NULL != src_queue);
	
	SllistAppend(dest_queue->list,src_queue->list);
}

