/* 
yan meiri
reviwed by idan
*/

#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "dllist.h"


struct dllist_node 
{
    void *data;
    struct dllist_node *next;
    struct dllist_node *prev;
};

struct dllist 
{
    struct dllist_node *head;
    struct dllist_node *tail;
};

static dllist_iter_t CreateNode(void *data, dllist_iter_t next);						 
static int IsDummy(dllist_iter_t iter);
static int Counter(void *data, void *count);

static dllist_iter_t CreateNode(void *data, dllist_iter_t next)
{
	dllist_iter_t ptr_node = NULL;
	
	ptr_node = (dllist_iter_t)malloc(sizeof(struct dllist_node));
	
	if (NULL == ptr_node)
	{
		return NULL;
	}
	
	ptr_node->data = data;
	ptr_node->next = next;
	ptr_node->prev = DllistPrev(next);
	
	return ptr_node;
}

static int IsDummy(dllist_iter_t iter)
{
	assert(iter);
	
	return (DllistNext(iter) == NULL || DllistPrev(iter) == NULL);
}

dllist_t *DllistCreate(void)
{
	dllist_t *ptr_dllist = NULL;
	
	ptr_dllist = (dllist_t*)malloc(sizeof(dllist_t));
	if (NULL == ptr_dllist)
	{
		return NULL;
	}
	 
	ptr_dllist->head = (dllist_iter_t)malloc(sizeof(struct dllist_node));
	if (NULL == ptr_dllist->head)
	{
		free(ptr_dllist);
		return NULL;
	}
	
	ptr_dllist->tail = (dllist_iter_t)malloc(sizeof(struct dllist_node));
	if (NULL == ptr_dllist->tail)
	{
		free(ptr_dllist->head);
		free(ptr_dllist);
		return NULL;
	}
	
	ptr_dllist->head->next = ptr_dllist->tail;
	ptr_dllist->head->prev = NULL;
	
	ptr_dllist->tail->next = NULL;
	ptr_dllist->tail->prev = ptr_dllist->head;
	
	return ptr_dllist;
}

void DllistDestroy(dllist_t *list)
{
	dllist_iter_t node = NULL;

	assert(list);
	
	node = DllistGetBegin(list);
	
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

dllist_iter_t DllistInsertBefore(dllist_t *list,
								 void *data,
								 dllist_iter_t where)
{	
	dllist_iter_t new_node = NULL;
	
	assert(where);
	assert(where->prev);
	assert(list);

	new_node = CreateNode(data, where);
	if (NULL == new_node)
	{
		return DllistGetEnd(list);
	}
	
	where->prev->next = new_node;
	where->prev = new_node;
	
	return new_node;
}

dllist_iter_t DllistRemove(dllist_iter_t where)
{
	dllist_iter_t next_to_where_iter = NULL;
	
	assert(where);
	assert(where->next);
	assert(where->prev);
	
	next_to_where_iter = DllistNext(where);
	where->prev->next = next_to_where_iter;
	where->next->prev = DllistPrev(where);
	
	free(where);
	
	return next_to_where_iter;
}

size_t DllistSize(const dllist_t *list)
{
	size_t count = 0;
	
	assert(list);
	
	DllistForEach(DllistGetBegin(list), DllistGetEnd(list), &Counter, &count); 

	return count;
}

static int Counter(void *data, void *count)
{
	(void)data;
	++*(size_t*)count;
	
	return 0;
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

dllist_iter_t DllistFind(void *param,
						 dllist_iter_t from,
						 dllist_iter_t to,
						 match_func_t is_match)
{
	assert(from);
	assert(to);
	assert(is_match);
	
	while (!DllistIsSameIter(from,to))
	{
		if (is_match(DllistGetData(from), param))
		{
			return from;
		}
		
		from = DllistNext(from);
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
	
	return (DllistIsSameIter(DllistGetBegin(list), DllistGetEnd(list)));
}

int DllistForEach(dllist_iter_t from,
				  dllist_iter_t to,
				  action_func_t action,
				  void *param)
{
	int status = 0;
	
	assert(from);
	assert(to);
	assert(action);
	
	while (!DllistIsSameIter(from,to))
	{
		status = action(DllistGetData(from), param);
		from = DllistNext(from);
	}

	return status;
}

dllist_iter_t DllistPushFront(dllist_t *list, void *data)
{
	assert(list);
	
	return (DllistInsertBefore(list, data, DllistGetBegin(list)));
}

dllist_iter_t DllistPushBack(dllist_t *list, void *data)
{
	assert(list);
	
	return (DllistInsertBefore(list, data, DllistGetEnd(list)));
}

void *DllistPopFront(dllist_t *list)
{
	void *data = NULL;
	
	assert(list);
	
	data = DllistGetData(DllistGetBegin(list));
	
	DllistRemove(DllistGetBegin(list));
	
	return data;
}

void *DllistPopBack(dllist_t *list)
{
	dllist_iter_t iter_before_tail = NULL;
	void *data = NULL;
	
	assert(list);
	
	iter_before_tail = DllistPrev(DllistGetEnd(list));
	data = DllistGetData(iter_before_tail);
	
	DllistRemove(iter_before_tail);
	
	return data;
}

dllist_iter_t DllistSplice(dllist_iter_t where,
						   dllist_iter_t from,
						   dllist_iter_t to)
{
	dllist_iter_t tmp = NULL;
	
	assert(from);
	assert(to);
	assert(where);
	assert(where->prev);
	assert(to->prev);
	assert(from->prev);
	
	where->prev->next = from;
	tmp = DllistPrev(where);
	where->prev = DllistPrev(to);
	to->prev->next = where;
	to->prev = DllistPrev(from);
	from->prev->next = to;
	from->prev = tmp;
	
	return DllistPrev(where);

}

int DllistMultiFind(dllist_iter_t from,
					dllist_iter_t to,
					match_func_t is_match,
					void *param,
					dllist_t *output)
{
	int count = 0;
	dllist_iter_t status = NULL;
	
	assert(from);
	assert(to);
	assert(is_match);
	assert(output);
	
	while (!DllistIsSameIter(from,to))
	{
		if (is_match(DllistGetData(from), param))
		{
			status = DllistInsertBefore(output,
										DllistGetData(from),
										 DllistGetEnd(output));
			if (NULL == status)
			{
				return -1;
			}
			
			++count;
		}
		
		from = DllistNext(from);
	}
	
	return count;
}

