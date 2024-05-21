#include <stdlib.h> /* size_t malloc() free() */
#include <assert.h> /* assert() */

#include "dllist.h"
#include "sortedlist.h"

struct sortedlist
{
    dllist_t *list;
    comp_func_t compare;
}

sortedlist_t *SortedlistCreate(sortedlist_cmp_func_t compare)
{
	sortedlist_t *ptr_list = NULL;
	
	assert(compare);
	
	ptr_list = (sortedlist_t*)malloc(sizeof(sortedlist_t));
	if (NULL == ptr_list)
	{
		return NULL;
	}
	
	ptr_list->list = DllistCreate();
	if (NULL == ptr_list->list)
	{
		free(ptr_list);
		return NULL;
	}
	
	ptr_list->compare = compare;
}

void SortedlistDestroy(sortedlist_t *list)
{
	assert(list);
	
	DllistDestroy(list->list);
	
	free(list);
}

sortedlist_iter_t SortedlistNext(sorted_iter_t iter)
{	
	assert(iter.iter);
	
	iter.iter = DllistNext(iter.iter);
	
	return iter;
}

sortedlist_iter_t SortedlistPrev(sorted_iter_t iter)
{	
	assert(iter.iter);
	
	iter.iter = DllistPrev(iter.iter);
	
	return iter;
}

sortedlist_iter_t SortedlistGetBegin(const sortedlist_t *list)
{
	sortedlist_iter_t iter;
	
	assert(list);
	
	#ifndef NDEBUG
        iter.list = list;
    #endif
	
	iter.iter = DllistGetBegin(list->list);
	
	return iter;
}

sortedlist_iter_t SortedlistGetEnd(const sortedlist_t *list)
{
	sortedlist_iter_t iter;
	
	assert(list);
	
	#ifndef NDEBUG
        iter.list = list;
    #endif
    
	iter.iter = DllistGetEnd(list->list);
	
	return iter;
}

sortedlist_iter_t SortedlistInsert(sortedlist_t *list, void *data)
{
	sortedlist_iter_t where;
	
	assert(list);
	
	where = SortedlistGetBegin(list);
	
	while (NULL != where.iter->next)
	{
		if (0 < compare(where.iter->data, data))
		{
			where.iter = DllistInsertBefore(list, data, where.iter);
			
			return where;
		}
		
		where.iter = where.iter->next;
	}
	
	where.iter = DllistInsertBefore(list, data, where.iter);
	
	return where;
	
}

sortedlist_iter_t SortedlistRemove(sorted_iter_t where)
{
	assert(where.iter);

	where.iter = DllistRemove(where.iter);
	
	return where;
}

size_t SortedlistSize(const sortedlist_t *list)
{
	assert(list);
	
	return DllistSize(list->list);
}

void *SortedlistGetData(sorted_iter_t iter)
{
	assert(iter.iter);
	
	return iter.iter->data;
}

sortedlist_iter_t SortedlistFind(
    sortedlist_t *list,
    sorted_iter_t from, 
    sorted_iter_t to, 
    const void *param)
{
	sortedlist_iter_t where;
	
	assert(list);
	assert(from.iter);
	assert(to.iter);
	#ifndef NDEBUG
		assert(from.list);
		assert(to.list);
        assert(from.list == to.list)
    #endif
    
    while (!DllistIsSameIter(from.iter,to.iter))
	{
		if (0 == list.compare(from.iter->data,param))
		{
			where.iter = from.iter;
			
			return where;
		}
		
		from.iter = from.iter->next;
	}
	
	where.iter = to.iter;
	
	return where;
}




