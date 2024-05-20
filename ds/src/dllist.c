/* 
yan meiri
reviwed by ___
*/

#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "dllist.h"


typedef struct dllist_node 
{
    void *data;
    struct dllist_node *next;
    struct dllist_node *prev;
} dllist_node_t;

struct dllist 
{
    dllist_node_t *head;
    dllist_node_t *tail;
};

static dllist_node_t *CreateNode(void *data, dllist_node_t *next, dllist_node_t *prev);
static int IsDummy(dllist_iter_t iter);


static dllist_node_t *CreateNode(void *data, dllist_node_t *next, dllist_node_t *prev)
{
	dllist_node_t *ptr_node = (dllist_node_t*)malloc(sizeof(dllist_node_t));
	
	if (NULL == ptr_node)
	{
		return NULL;
	}
	
	ptr_node->data = data;
	ptr_node->next = next;
	ptr_node->prev = prev;
	
	return ptr_node;
}

static int IsDummy(dllist_iter_t iter)
{
	assert(iter);
	
	return (iter->next == NULL || iter->prev == NULL);
}

dllist_t *DllistCreate(void)
{
	dllist_t *ptr_dllist = NULL;
	ptr_dllist = (dllist_t*)malloc(sizeof(dllist_t));
	
	if (NULL == ptr_dllist)
	{
		return NULL;
	}
	
	/* alocating memory to a dummy node that head point to*/
	ptr_dllist->head = CreateNode((void*)ptr_dllist, NULL, NULL);
	if (NULL == ptr_dllist->head)
	{
		free(ptr_dllist);
		return NULL;
	}
	
	/* alocating memory to a dummy node that tail point to*/
	ptr_dllist->tail = CreateNode((void*)ptr_dllist,NULL, NULL);
	if (NULL == ptr_dllist->tail)
	{
		free(ptr_dllist->head);
		free(ptr_dllist);
		return NULL;
	}
	
	ptr_dllist->head->next = ptr_dllist->tail;
	ptr_dllist->tail->prev = ptr_dllist->head;
	

	return ptr_dllist;
}

void DllistDestroy(dllist_t *list)
{
	dllist_node_t *node = NULL;

	assert(list);
	
	node = list->head->next;
	
	while (!IsDummy(node))
	{
		node = DllistRemove(node);
	}
	
	free(list->head);
	free(list->tail);
	free(list);
}

dllist_iter_t DllistNext(dllist_iter_t iter)
{
	assert(iter);
	
	return iter->next;
}

dllist_iter_t DllistPrev(dllist_iter_t iter)
{
	assert(iter);
	
	return iter->prev;
}

dllist_iter_t DllistGetBegin(const dllist_t *list)
{
	assert(list);
	
	return list->head->next;
}

dllist_iter_t DllistGetEnd(const dllist_t *list)
{
	assert(list);
	
	return list->tail;
}

dllist_iter_t DllistInsertBefore(dllist_t *list, void *data, dllist_iter_t where)
{	
	dllist_node_t *new_node = NULL;
	
	assert(where);
	assert(list);

	new_node = CreateNode(data, where, where->prev);
	if (NULL == new_node)
	{
		return NULL;
	}
	
	where->prev->next = new_node;
	where->prev = new_node;
	
	return new_node;
}

dllist_iter_t DllistRemove(dllist_iter_t where)
{
	dllist_iter_t tmp_node = NULL;
	
	assert(where);
	
	tmp_node = where->next;
	where->prev->next = where->next;
	where->next->prev = where->prev;
	
	free(where);
	
	return tmp_node;
}

size_t DllistSize(const dllist_t *list)
{
	size_t count = 0;
	dllist_node_t *node = NULL;
	
	assert(list);
	
	node = list->head->next;
	
	while (NULL != node->next)
	{
		++count;
		
		node = node->next;
	}
	
	return count;
}

void DllistSetData(dllist_iter_t iter, void* data)
{
	assert(iter);
	
	iter->data = data;
}

void *DllistGetData(dllist_iter_t iter)
{
	assert(iter);
	
	return iter->data;
}

dllist_iter_t DllistFind(void *param, dllist_iter_t from, dllist_iter_t to, match_func_t is_match)
{
	assert(from);
	assert(to);
	assert(is_match);
	
	while (!DllistIsSameIter(from,to))
	{
		if (is_match(from->data,param))
		{
			return from;
		}
		
		from = from->next;
	}
	
	return to;
}

int DllistIsSameIter(dllist_iter_t iter1, dllist_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

int DllistIsEmpty(const dllist_t *list)
{
	assert(list);
	
	/* check if head points to tail */
	return (DllistIsSameIter(list->head->next, list->tail));
}

int DllistForEach(dllist_iter_t from, dllist_iter_t to, action_func_t action, void *param)
{
	int status = 0;
	
	assert(from);
	assert(to);
	assert(action);
	
	while (!DllistIsSameIter(from,to))
	{
		status = action(from->data,param);
		from = from->next;
	}

	return status;
}

dllist_iter_t DllistPushFront(dllist_t *list, void *data)
{
	assert(list);
	
	return (DllistInsertBefore(list, data, list->head->next));
}

dllist_iter_t DllistPushBack(dllist_t *list, void *data)
{
	assert(list);
	
	return (DllistInsertBefore(list, data, list->tail));
}

void *DllistPopFront(dllist_t *list)
{
	dllist_node_t *front = NULL;
	void *data = NULL;
	
	assert(list);
	
	front = list->head->next;
	data = front->data;
	
	DllistRemove(front);
	
	return data;
}

void *DllistPopBack(dllist_t *list)
{
	dllist_node_t *back = NULL;
	void *data = NULL;
	
	assert(list);
	
	back = list->tail->prev;
	data = back->data;
	
	DllistRemove(back);
	
	return data;
}

dllist_iter_t DllistSplice(dllist_iter_t where, dllist_iter_t from, dllist_iter_t to)
{
	dllist_iter_t tmp = NULL;
	
	assert(from);
	assert(to);
	assert(where);
	
	where->prev->next = from;
	tmp = where->prev;
	where->prev = to->prev;
	to->prev->next = where;
	to->prev = from->prev;
	from->prev->next = to;
	from->prev = tmp;
	
	return where->prev;

}

int DllistMultiFind(dllist_iter_t from, dllist_iter_t to, match_func_t is_match, void *param, dllist_t *output)
{
	int count = 0;
	dllist_iter_t status = NULL;
	
	assert(from);
	assert(to);
	assert(is_match);
	assert(output);
	
	while (!DllistIsSameIter(from,to))
	{
		if (is_match(from->data,param))
		{
			status = DllistInsertBefore(output, from->data, output->tail);
			if (NULL == status)
			{
				return -1;
			}
			
			++count;
		}
		
		from = from->next;
	}
	
	return count;
}

