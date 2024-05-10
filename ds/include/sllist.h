#ifndef __SLLIST_H__
#define __SLLIST_H__

#include <stddef.h> /* size_t */

typedef struct sllist sllist_t;
typedef struct sllist_node *sllist_iter_t;
typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(const void *data, void *param);

/*
SllistCreate
description: create sllist
input: no input
return: a pointer to a single linked list
time complexity: O(1)
space complexity: O(1)
*/
sllist_t *SllistCreate(void);   

/*
SllistDestroy
description: destroy the entire list
input: pointer to a list
return: nothing
time complexity: O(n) 
space complexity: O(1)
*/
void SllistDestroy(sllist_t *sllist);

/*
SllistNext
description: moves the iterator to next element
input: itrator
return: itrator
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistNext(sllist_iter_t iter);

/*
SllistBegin
description: return the head's iterator (pointer to first valid node)
input: a pointer to a sllist
return: head's iterator
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistBegin(const sllist_t *sllist);

/*
SllistEnd
description: Return the tail's iterator (pointer to last invalid node)
input: a pointer to a sllist
return: tail's iterator
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistEnd(const sllist_t *sllist);

/*
SllistInsertBefore
description: insert data before the index we currently on
input: a pointer to a sllist, pointer to data, itrator 
return: new itrator if failed itrator == NULL
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistInsertBefore(sllist_t *sllist, void *data, sllist_iter_t where);

/*
SllistRemove
description: removes the current iterator
input: iterator to remove
return: next iterator
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistRemove(sllist_iter_t where);

/*
SllistCount
description: return the count of nodes 
input: sllist 
return: size_t
time complexity:O(n) 
space complexity: O(1)
*/
size_t SllistCount(const sllist_t *sllist);

/*
SllistGetData
description: returns the data in specific iterator
input: an iterator
return: a void pointer that points to the data
time complexity: O(1)
space complexity: O(1) 
*/
void *SllistGetData(sllist_iter_t iterator);

/*
SllistSetData
description: modifies the data in specific iterator
input: an iterator and a pointer to the new data
return: the iterator with the new data
time complexity: O(1)
space complexity: O(1)
*/
sllist_iter_t SllistSetData(sllist_iter_t iterator, void *new_data);

/*
SllistFind
description: Finds if data exists in a specific range in a single linked list
input: data to find, iterator to start from, iterator end, function to match
return: iterator to the matched data or invalid iterator if data is not found
time complexity: O(n)
space complexity: O(1)
*/
sllist_iter_t SllistFind(void *param, sllist_iter_t from, sllist_iter_t to, match_func_t is_match);

/*
SllistIterIsEqual
description: check if two iterators are equal
input: pointers to two iterators
return: 1 equal 0 unequal
time complexity: O(1)
space complexity: O(1)
*/
int SllistIterIsEqual(sllist_iter_t iterator1, sllist_iter_t iterator2);

/*
SllistIsEmpty
description: check if a sllist is empty
input: sllist
return: 1 if empty, 0 if not empty
time complexity: O(1)
space complexity: O(1)
*/
int SllistIsEmpty(const sllist_t *sllist);

/*
SllistForEach
description: does a certain action on a range of data
input: itrator from, itrator to, a pointer to a function action and the param for that function.
return: the status the last executed action function
time complexity: O(n)
space complexity: O(1)
*/
int SllistForEach(sllist_iter_t from, sllist_iter_t to, action_func_t action, void *param);

#endif /*__SLLIST_H__*/ 
