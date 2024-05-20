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
	
}




