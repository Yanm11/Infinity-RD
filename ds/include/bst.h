#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /*  size_t */

typedef struct node *bst_iter_t;
typedef struct bst bst_t;

/*
Description: typedef to pointer function that compare the two argument
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching:
   positive if the first argument is bigger,
   zero if they are equal
   negative if the second argument is bigger.
*/
typedef int (*bst_cmp_func_t)(const void *data, const void *new_data);

/*
Description: typedef of a pointer to function. The function performs an action on the passed data of list element  
Params: (void *, void *) first param - pointer to data in an element, second param - pointer to data sent by the user
Return Value: int that represent status. 0 for success , non 0 for failure
*/
typedef int (*bst_action_func_t)(void *data, void *param);

/*
BSTCreate
description: create a binary search tree
input: a pointer to a compare function 
return: the binary search tree struct
time complexity: O(1)
space complexity: O(1)
*/
bst_t *BSTCreate(bst_cmp_func_t compare);

/*
BSTDestroy
description: destroy all the elements in the tree
input: a binary search tree structer
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void BSTDestroy(bst_t *tree);

/*
BSTSize
description: return the number of elements in the tree
input: a binary search tree structer
return: number of elements in the binary search tree
time complexity: O(n)
space complexity: O(1)
*/
size_t BSTSize(const bst_t *tree);

/*
BSTIsEmpty
description: check if BST is empty
input: a BST structer
return: non-0 if empty, 0 if not empty
time complexity: O(1)
space complexity: O(1)
*/
int BSTIsEmpty(const bst_t *tree);

/*
BSTInsert
description: insert a new element to the BST
input: a BST and new data
return: Invalid iter on failure, Iter containing the new data on success
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
**Invalid iter is: 
*/
bst_iter_t BSTInsert(bst_t *tree, void *data);

/*
BSTRemove
description: remove an element from the tree
input: an iter to an element to be remove
return: the data of the element
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
*/
void *BSTRemove(bst_iter_t iter_to_remove);

/*
BSTGetBegin
description: The first element (valid) in the tree (can't do Prev to it)
input: a BST 
return: a valid iterrator for the first element (can't do Prev to it)
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
*/
bst_iter_t BSTBegin(const bst_t *tree);

/*
BSTGetEnd
description: The last element in the tree (can't do Next to it) a dummy
input: a BST 
return: an invalid iterrator (can't do Next to it)
time complexity: O(1)
space complexity: O(1)
*/
bst_iter_t BSTEnd(const bst_t *tree);

/*
BSTPrev
description: return the prevois element (smaller key)
input: an iterator to an element
return: an iter to the previous element
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
*/
bst_iter_t BSTPrev(bst_iter_t iter);

/*
BSTNext
description: return the next element (larger key)
input: an iter to the element
return: an iter to the next element 
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
*/
bst_iter_t BSTNext(bst_iter_t iter);

/*
BSTIsSameIter
description: check if one iter is the same an another
input: 2 iterators
return:  non-0 if same, 0 if not same
time complexity: O(1)
space complexity: O(1)
*/
int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2);

/*
BSTGetData
description: get the data from a certain element
input: an iterator
return: void pointer to the data
time complexity: O(1)
space complexity: O(1)
*/
void *BSTGetData(bst_iter_t iter);

/*
BSTFind
description: searches the tree for a certain element. 
input: a BST and data to search for
return: if exist will return a an iter to the element if not then an invalid iterator
time complexity: worst case: O(n), avg case:O(log n)
space complexity: O(1)
*/
bst_iter_t BSTFind(const bst_t *tree, const void *data);

/*
BSTForEach
description: does a certain action on all the tree(does not change the data it self)
input: tree to run over amd execute the action func 
return: the last status the action function returned
time complexity: O(n)
space complexity: O(1)
*/
int BSTForEach(bst_t *tree, bst_action_func_t action, void* param);


#endif /*__BST_H__*/

