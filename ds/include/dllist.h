#ifndef __DLLIST_H__
#define __DLLIST_H__

#include <stddef.h> /*size_t*/

typedef struct dllist dllist_t;
typedef struct dllist_node *dllist_iter_t;
typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(const void *data, void *param);

/*
DllistCreate
description: create dllist
input: no input
return: a pointer to a doubly linked list
time complexity: O(1)
space complexity: O(1)
*/
dllist_t *DllistCreate(void);

/*
DllistDestroy
description: free dllist
input: pointer to doubly link list
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void DllistDestroy(dllist_t *list);

/*
DllistNext
description: moves iterator to next element
input: iterator
return: iterator of next element
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistNext(dllist_iter_t iter);

/*
DllistPrev
description: Return the previos iterator of the current iterator
input: iterator
return: a pointer to previos iterator
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistPrev(dllist_iter_t iter);

/*
DllistBegin
description: returns iterator to the first valid element of the list
input: pointer to list
return: iterator of first valid element
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistGetBegin(const dllist_t *list);

/*
DllistEnd
description: Return iterator to the end of the list, invalid iterator
input: pointer to list
return: invalid iterator
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistGetEnd(const dllist_t *list);

/*
DllistInsertBefore
description: inserts an element before an element
input: pointer to list, pointer to wanted data, iterator to the element
return: iterator to the added element if succeeded, tail if failed
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistInsertBefore(dllist_t *list, void *data, dllist_iter_t where);

/*
DllistRemove
description: removes the given iterator from the list
input: iterator to remove
return: next iterator
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistRemove(dllist_iter_t where);

/*
DllistSize
description: counts the number of elements in the list
input: const pointer to list
return: number of elements in the list
time complexity: O(n)
space complexity: O(1)
*/
size_t DllistSize(const dllist_t *list);

/*
Description: Set the data for specfic element in the list
Params: (iterator - where to set the new data and  new data) ,
Return Value: void 
Time Complexity: O(1)
Space: O(1)
*/
void DllistSetData(dllist_iter_t iterator, void* data);

/*
DllistGetData
description: get data from iterator
input: iterator to get the data from it
return: pointer to data
time complexity: O(1)
space complexity: O(1)
*/
void *DllistGetData(dllist_iter_t iter);

/*
DllistFind
description: find if data exist in a specific range [from, to) in the list
input: date to find, iterator to start from, iterator to end, function to match
return: iterator to matched data or the to iterator of the range if data is not found
time complexity: O(n)
space complexity: O(1)
*/
dllist_iter_t DllistFind(void *param, dllist_iter_t from, dllist_iter_t to, match_func_t is_match);

/*
DllistIterIsEqual
description: checks if 2 iterators are the same iterator
input: two iterators
return: 1 if same iterator, 0 if not
time complexity: O(1)
space complexity: O(1)
*/
int DllistIsSameIter(dllist_iter_t iter1, dllist_iter_t iter2);

/*
DllistIsEmpty
description: checks is list is empty
input: pointer to list
return: 1 if empty, 0 if not
time complexity: O(1)
space complexity: O(1)
*/
int DllistIsEmpty(const dllist_t *list);

/*
DllistForEach
description: does a certain action on a range [from, to) of data
input: itrator from, itrator to, a pointer to a function action and the param for that function.
return: returns the last return value from the function action
time complexity: O(n)
space complexity: O(1)
*/
int DllistForEach(dllist_iter_t from, dllist_iter_t to, action_func_t action, void *param);

/*
DllistSplice
description: Splice a range [from, to) of elements before element where
input: iterator from, iterator to, iterator where 
return: the iterator before where
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistSplice(dllist_iter_t where, dllist_iter_t from, dllist_iter_t to);

/*
DllistPushFront
description: Pushes an element in the begin of the list
input: a pointer to the list, pointer to data 
return: an iterator to the head of the list
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistPushFront(dllist_t *list, void *data);

/*
DllistPushBack
description: Pushes an element in the end of the list
input: a pointer to the list, pointer to data 
return: an iterator to the last element of the list
time complexity: O(1)
space complexity: O(1)
*/
dllist_iter_t DllistPushBack(dllist_t *list, void *data);

/*
DllistPopFront
description: Pops an element from the head of the list
input: a pointer to the list
return: pointer to the data we popped
time complexity: O(1)
space complexity: O(1)
*/
void *DllistPopFront(dllist_t *list);

/*
DllistPopBack
description: Pops an element from the end of the list
input: a pointer to the list 
return: pointer to the data we popped
time complexity: O(1)   
space complexity: O(1)
*/
void *DllistPopBack(dllist_t *list);

/*
DllistMultiFind
description: find all iterators in the range [from, to) that qualify with the is_match function with the given param.
input: an iter from, iter to, function match, data to check, output dllist
return: the number of matches, if failes -1
time complexity: O(n)   
space complexity: O(n)
*/
int DllistMultiFind(dllist_iter_t from, dllist_iter_t to, match_func_t is_match, void *param, dllist_t *output);

#endif /*__DLLIST_H__*/

