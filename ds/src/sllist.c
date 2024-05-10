#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "sllist.h"


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
static int IsNextDummy(sllist_node_t *iter);

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
	sllist_node_t *node_next = NULL;
	
	assert(NULL != sllist);
	
	node = sllist->head;
	node_next = node->next;
	
	while (!IsNextDummy(node))
	{
		free(node);
		node = node_next;
		node_next = node->next;
	}
	free(node);
	free(sllist);
}

sllist_iter_t SllistNext(sllist_iter_t iter)
{
	/*
	assert(NULL != iter);
	*/
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
		return NULL;
	}
	
	/* only if its the element before the tail */
	if(IsNextDummy(where))
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
	/*
	assert(NULL != where);
	*/
	
	sllist_node_t *temp_node = where->next;
	
	if(IsNextDummy(where->next))
	{
		((sllist_t *)where->next->data)->tail = where;
	}
	
	where->data = where->next->data;
	where->next = where->next->next;
	
	free(temp_node);
	
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
	/*
	assert(NULL != iterator->next);
	*/
	return iterator->data;
}

sllist_iter_t SllistSetData(sllist_iter_t iterator, void *new_data)
{
	/*
	assert(NULL != iterator);
	*/
	iterator->data = new_data;
	
	return iterator;
}

sllist_iter_t SllistFind(void *param, sllist_iter_t from, sllist_iter_t to, match_func_t is_match)
{
	sllist_node_t *dummy = NULL;
	/*
	assert(NULL != to);
	assert(NULL != from);
	*/
	while (!SllistIterIsEqual(from,to))
	{
		if (is_match(from->data,param))
		{
			return from;
		}
		from = from->next;
	}
	
	dummy = CreateNode(NULL,NULL);
	return dummy;
}

int SllistIterIsEqual(sllist_iter_t iterator1, sllist_iter_t iterator2)
{
	/*
	assert(NULL != iterator1);
	assert(NULL != iterator2);
	*/
	return (iterator1 == iterator2);
}

int SllistIsEmpty(const sllist_t *sllist)
{
	assert(NULL != sllist);
	return (sllist->head == sllist->tail);
}

int SllistForEach(sllist_iter_t from, sllist_iter_t to, action_func_t action, void *param)
{	
	/*
	assert(NULL != from);
	assert(NULL != to);
	*/
	
	int status = 0;
	
	while (!SllistIterIsEqual(from,to))
	{
		status = action(from->data,param);
		from = from->next;
	}

	return status;
}

static int Counter(void *data, void *param)
{
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

static int IsNextDummy(sllist_node_t *iter)
{
	return (iter->next == NULL);
}
