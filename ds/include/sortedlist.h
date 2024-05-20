#ifndef __SORTEDLIST_H__
#define __SORTEDLIST_H__

#include <stddef.h> /*size_t*/
#include "dllist.h" /*dllist_iter_t*/

typedef struct sortedlist sortedlist_t;

typedef struct 
{
    #ifndef NDEBUG
        sortedlist_t *list;
    #endif
    dllist_iter_t iter;
} sortedlist_iter_t;

typedef int (*sortedlist_cmp_func_t)(const void *data, const void *new_data);

/*
SortedlistCreate
description: create sortedlist
input: function compare to decide which element goes first. 
        the compare function should return positive value if data is bigger, negative if new_data is bigger, zero if equal. (like strcmp)
return: a pointer to a sorted linked list
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_t *SortedlistCreate(sortedlist_cmp_func_t compare);

/*
SortedlistDestroy
description: free sorted list
input: pointer to sorted link list
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void SortedlistDestroy(sortedlist_t *list);

/*
SortedlistNext
description: moves iterator to next element
input: iterator
return: iterator of next element
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistNext(sorted_iter_t iter);

/*
SortedlistPrev
description: Return the previos iterator of the current iterator
input: iterator
return: a pointer to previos iterator
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistPrev(sorted_iter_t iter);

/*
SlistBegin
description: returns iterator to the first valid element of the list
input: pointer to list
return: iterator of first valid element
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistGetBegin(const sortedlist_t *list);

/*
SortedlistEnd
description: Return iterator to the end of the list, invalid iterator
input: pointer to list
return: invalid iterator
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistGetEnd(const sortedlist_t *list);

/*
SortedlistInsert
description: inserts an element according to its value
input: pointer to list, pointer to wanted data
return: iterator to the added element, invalid iterator if failed
time complexity: O(n)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistInsert(sortedlist_t *list, void *data);

/*
SortedlistRemove
description: removes the given data from the list
input: pointer to itertaor wish to remove
return: the next iterator
time complexity: O(1)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistRemove(sorted_iter_t where);

/*
SortedlistSize
description: counts the number of elements in the list
input: const pointer to list
return: number of elements in the list
time complexity: O(n)
space complexity: O(1)
*/
size_t SortedlistSize(const sortedlist_t *list);

/*
SortedlistGetData
description: get data from iterator
input: iterator to get the data from it
return: pointer to data
time complexity: O(1)
space complexity: O(1)
*/
void *SortedlistGetData(sorted_iter_t iter);

/*
SortedlistFind
description: find if data exist in a specific range [from, to) in the list
input: pointer to a sorted list, iterator to start from, iterator to end at, data to find.
return: iterator to matched data or the to iterator of to if data is not found
time complexity: O(n)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistFind(
    sortedlist_t *list,
    sorted_iter_t from, 
    sorted_iter_t to, 
    const void *param);

/*
SortedlistFindIf
description: find if data exist in a specific range [from, to) in the list
input: pointer to a sorted list, iterator to start from, iterator to end at, pointer to a function to match by, data to find.
return: iterator to matched data or the to iterator if data is not found
time complexity: O(n)
space complexity: O(1)
*/
sortedlist_iter_t SortedlistFindIf(
    sorted_iter_t from, 
    sorted_iter_t to, 
    int (*is_match)(const void *data,const void *param), 
    void *param
    );
    
/*
SortedlistIsSameIter
description: checks if 2 iterators are the same iterator
input: two iterators
return: 1 if same iterator, 0 if not
time complexity: O(1)
space complexity: O(1)
*/
int SortedlistIsSameIter(sorted_iter_t iter1, sorted_iter_t iter2);

/*
SortedlistIsEmpty
description: checks if list is empty
input: pointer to list
return: 1 if empty, 0 if not
time complexity: O(1)
space complexity: O(1)
*/
int SortedlistIsEmpty(const sortedlist_t *list);

/*
SortedlistPopFront
description: Pops an element from the head of the list
input: a pointer to the list
return: pointer to the data we popped
time complexity: O(1)
space complexity: O(1)
*/
void *SortedlistPopFront(sortedlist_t *list);

/*
SortedlistPopBack
description: Pops an element from the end of the list
input: a pointer to the list 
return: pointer to the data we popped
time complexity: O(1)   
space complexity: O(1)
*/
void *SortedlistPopBack(sortedlist_t *list);

/*
SortedlistMerge
description: merge 2 sorted lists of the same compare function. 
input: dest list, src list
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void SortedlistMerge(sortedlist_t *dest, sortedlist_t *src);

/*
SortedlistForEach
description: does an action on each element in the range [from, to). manipulation on data is undefined.
input: iter from, iter to, pointer to an action function, parameter for the action function.
return: last status returned by the action function.
time complexity: O(n)
space complexity: O(1)
*/
int SortedlistForEach(
    sorted_iter_t from, 
    sorted_iter_t to, 
    int (*action)(void *data, void *param), 
    void *param
    );

#endif /*__SORTEDLIST_H__*/
    

