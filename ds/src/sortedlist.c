#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "dllist.h"
#include "sortedlist.h"

static int IsDummy(sortedlist_iter_t iter);

struct sortedlist
{
    dllist_t *list;
    sortedlist_cmp_func_t compare;
};	

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
	
	return ptr_list;
}

void SortedlistDestroy(sortedlist_t *list)
{
	assert(list);
	
	DllistDestroy(list->list);
	
	free(list);
}

sortedlist_iter_t SortedlistNext(sortedlist_iter_t iter)
{	
	assert(iter.iter);
	
	iter.iter = DllistNext(iter.iter);
	
	return iter;
}

sortedlist_iter_t SortedlistPrev(sortedlist_iter_t iter)
{	
	assert(iter.iter);
	
	iter.iter = DllistPrev(iter.iter);
	
	return iter;
}

sortedlist_iter_t SortedlistGetBegin(const sortedlist_t *list)
{
	sortedlist_iter_t iter = {NULL};
	
	assert(list);
	
	#ifndef NDEBUG
        iter.list = (sortedlist_t*)list;
    #endif
	
	iter.iter = DllistGetBegin(list->list);
	
	return iter;
}

sortedlist_iter_t SortedlistGetEnd(const sortedlist_t *list)
{
	sortedlist_iter_t iter = {NULL};
	
	assert(list);
	
	#ifndef NDEBUG
        iter.list = (sortedlist_t*)list;
    #endif
    
	iter.iter = DllistGetEnd(list->list);
	
	return iter;
}

sortedlist_iter_t SortedlistInsert(sortedlist_t *list, void *data)
{
	sortedlist_iter_t where = {NULL};
	
	assert(list);
	assert(data);
	
	where = SortedlistGetBegin(list);

	while (!IsDummy(where))
	{
		if (0 < list->compare(DllistGetData(where.iter), data))
		{
			where.iter = DllistInsertBefore(list->list, data, where.iter);
			return where;
		}
		
		where.iter = DllistNext(where.iter);
	}

	where.iter = DllistInsertBefore(list->list, data, where.iter);
	
	return where;
	
}

sortedlist_iter_t SortedlistRemove(sortedlist_iter_t where)
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

void *SortedlistGetData(sortedlist_iter_t iter)
{
	assert(iter.iter);
	
	return DllistGetData(iter.iter);
}

sortedlist_iter_t SortedlistFind(
    sortedlist_t *list,
    sortedlist_iter_t from, 
    sortedlist_iter_t to, 
    const void *param)
{
	sortedlist_iter_t where = {NULL};
	
	assert(list);
	assert(from.iter);
	assert(to.iter);
	assert(param);
	assert(from.list);
	assert(to.list);
    assert(from.list == to.list);
    
    while (!DllistIsSameIter(from.iter,to.iter))
	{
		if (0 == list->compare(DllistGetData(from.iter), param))
		{
			where.iter = from.iter;
			
			return where;
		}
		
		from.iter = DllistNext(from.iter);
	}
	
	where.iter = to.iter;
	
	return where;
}

sortedlist_iter_t SortedlistFindIf(
    sortedlist_iter_t from, 
    sortedlist_iter_t to, 
    int (*is_match)(const void *data, void *param), 
    void *param
    )
{
	sortedlist_iter_t where = {NULL};
	
	assert(from.iter);
	assert(to.iter);
	assert(param);
	assert(from.list);
	assert(to.list);
    assert(from.list == to.list);
    
   where.iter =  DllistFind(param, from.iter, to.iter, is_match);
   
   return where;
}

int SortedlistIsSameIter(sortedlist_iter_t iter1, sortedlist_iter_t iter2)
{
	assert(iter1.iter);
	assert(iter2.iter);
	
	return (iter1.iter == iter2.iter);
}

int SortedlistIsEmpty(const sortedlist_t *list)
{
	assert(list);
	
	return DllistIsEmpty(list->list);
}

void *SortedlistPopFront(sortedlist_t *list)
{
	assert(list);
	
	return DllistPopFront(list->list);

}

void *SortedlistPopBack(sortedlist_t *list)
{
	assert(list);
	
	return DllistPopBack(list->list);
}

static int IsDummy(sortedlist_iter_t iter)
{
	assert(iter.iter);
	
	return (NULL == SortedlistNext(iter).iter);
}



void SortedlistMerge(sortedlist_t *dest, sortedlist_t *src)
{
	sortedlist_iter_t where_dest_from = {NULL}; 
	sortedlist_iter_t where_dest_to = {NULL};
	sortedlist_iter_t where_src_from = {NULL};
	sortedlist_iter_t where_src_to = {NULL};
	
	assert(dest);
	assert(src);
	assert(dest->compare == src->compare);
	
	where_dest_from = SortedlistGetBegin(dest);
	where_src_from = SortedlistGetBegin(src);
	where_dest_to = where_dest_from;
	where_src_to = SortedlistNext(where_src_from);	

	while ((!IsDummy(where_dest_to)) && (!IsDummy(where_src_to)))
	{
		while ((0 < dest->compare(SortedlistGetData(where_dest_to)
							    , SortedlistGetData(where_src_to))) &&
				(!IsDummy(where_src_to)))
		{
			where_src_to = SortedlistNext(where_src_to);
		}
		
		if ((0 < dest->compare(SortedlistGetData(where_dest_to)
							, SortedlistGetData(where_src_from))))
		{
			DllistSplice(where_dest_to.iter,
						 where_src_from.iter,
						 where_src_to.iter);
						 		
			where_src_from = where_src_to;
		}
		
		where_dest_to = SortedlistNext(where_dest_to);
	}
	
	if ((IsDummy(where_dest_to)) && (!IsDummy(where_src_to)))
	{
		where_src_to = SortedlistGetEnd(src);
		
		DllistSplice(where_dest_to.iter,
					 where_src_from.iter,
					 where_src_to.iter);
	}

}

int SortedlistForEach(
    sortedlist_iter_t from, 
    sortedlist_iter_t to, 
    int (*action)(void *data, void *param), 
    void *param
    )
{
	assert(from.iter);
	assert(to.iter);
	assert(from.list);
	assert(to.list);
    assert(from.list == to.list);
        
    return DllistForEach(from.iter, to.iter, action, param);
}








