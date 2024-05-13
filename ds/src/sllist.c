#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "sllist.h"

/*
yan meiri
checked and reviewed by many but mainly oded
*/

typedef struct sllist_node 
{
    void *data;
    struct sllist_node *next;
}sllist_node_t;

struct sllist 
{
    sllist_node_t *head;
    sllist_node_t *tail;
};

static int Counter(void *data, void *param);
static sllist_node_t *CreateNode(void *data, sllist_node_t *next);
static int IsDummy(sllist_node_t *iter);

sllist_t *SllistCreate(void)
{
	sllist_t *ptr_sllist = NULL;
	ptr_sllist = (sllist_t*)malloc(sizeof(sllist_t));
	
	if (NULL == ptr_sllist)
	{
		return NULL;
	}
	
	/* alocating memory to a dummy node that both head and tail will point to*/
	ptr_sllist->head = CreateNode((void*)ptr_sllist,NULL);
	if (NULL == ptr_sllist->head)
	{
		free(ptr_sllist);
		return NULL;
	}
	
	ptr_sllist->tail = ptr_sllist->head;
	
	return ptr_sllist;
}

void SllistDestroy(sllist_t *sllist)
{
	sllist_node_t *node = NULL;

	assert(NULL != sllist);
	
	node = sllist->head;
	
	while (!IsDummy(node))
	{
		SllistRemove(node);
	}
	
	free(node);
	free(sllist);
}

sllist_iter_t SllistNext(sllist_iter_t iter)
{
	assert(NULL != iter);
	
	return iter->next;
}

sllist_iter_t SllistBegin(const sllist_t *sllist)
{
	assert(NULL != sllist);
	return sllist->head;
}

sllist_iter_t SllistEnd(const sllist_t *sllist)
{
	assert(NULL != sllist);
	return sllist->tail;
}

sllist_iter_t SllistInsertBefore(sllist_t *sllist, void *data, sllist_iter_t where)
{
	sllist_node_t *new_node = NULL;
	
	assert(NULL != sllist);
	assert(NULL != where);
	
	/* allocating memory for new node */
	new_node = CreateNode(where->data, where->next);
	if (NULL == new_node)
	{
		return sllist->tail;
	}
	
	/* only if its the element before the tail */
	if(IsDummy(where))
	{
		sllist->tail = new_node;
	}
	
	/* changing the old node to the new one */
	where->data = data;
	where->next = new_node;
	
	return where;
}

sllist_iter_t SllistRemove(sllist_iter_t where)
{	
	sllist_node_t *temp_node = NULL;

	assert(NULL != where);
	
	temp_node = where->next;
	
	if(IsDummy(where->next))
	{
		((sllist_t *)where->next->data)->tail = where;
	}
	
	where->data = where->next->data;
	where->next = where->next->next;
	
	free(temp_node);
	temp_node = NULL;
	
	return where;	
}

size_t SllistCount(const sllist_t *sllist)
{
	size_t number_nodes = 0;
	action_func_t action = &Counter;
	
	assert(NULL != sllist);
	 
	SllistForEach(sllist->head, sllist->tail, action, &number_nodes);
	
	return number_nodes; 
}

void *SllistGetData(sllist_iter_t iterator)
{
	assert(NULL != iterator);

	return iterator->data;
}

sllist_iter_t SllistSetData(sllist_iter_t iterator, void *new_data)
{
	assert(NULL != iterator);
	
	iterator->data = new_data;
	
	return iterator;
}

sllist_iter_t SllistFind(void *param, sllist_iter_t from, sllist_iter_t to, match_func_t is_match)
{
	assert(NULL != to);
	assert(NULL != from);
	
	while (!SllistIterIsEqual(from,to))
	{
		if (is_match(from->data,param))
		{
			return from;
		}
		from = from->next;
	}
	
	return to;
}

int SllistIterIsEqual(sllist_iter_t iterator1, sllist_iter_t iterator2)
{
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	
	return (iterator1 == iterator2);
}

int SllistIsEmpty(const sllist_t *sllist)
{
	assert(NULL != sllist);
	return (sllist->head == sllist->tail);
}

int SllistForEach(sllist_iter_t from, sllist_iter_t to, action_func_t action, void *param)
{		
	int status = 0;
	
	assert(NULL != from);
	assert(NULL != to);
	
	while (!SllistIterIsEqual(from,to))
	{
		status = action(from->data,param);
		from = from->next;
	}

	return status;
}

void SllistAppend(sllist_t *dest, sllist_t *src)
{	
	assert(NULL != dest);
	assert(NULL != src);
	
	dest->tail->next = src->head->next;
	dest->tail->data = src->head->data;
	
	dest->tail = src->tail;
	
	src->head->next = NULL;
	src->head->data = (void*)src;
	src->tail = src->head;
}

static int Counter(void *data, void *param)
{
	assert(NULL != param);
	(void)data;
	
	*(size_t*)param += 1;
	
	return 0;
}

static sllist_node_t *CreateNode(void *data, sllist_node_t *next)
{
	sllist_node_t *ptr_node = (sllist_node_t*)malloc(sizeof(sllist_node_t));
	
	if (NULL == ptr_node)
	{
		return NULL;
	}
	
	ptr_node->data = data;
	ptr_node->next = next;
	
	return ptr_node;
}

static int IsDummy(sllist_node_t *iter)
{
	assert(NULL != iter);
	return (iter->next == NULL);
}
