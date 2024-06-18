#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /*  size_t */

typedef struct avl avl_t;

/*
Description: typedef to pointer function that compare the two argument
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching:
   positive if the first argument is bigger,
   zero if they are equal
   negative if the second argument is bigger.
*/
typedef int (*avl_cmp_func_t)(const void *data, const void *new_data);

/*
Description: typedef of a pointer to function. The function performs an action on the passed data of list element  
Params: (void *, void *) first param - pointer to data in an element, second param - pointer to data sent by the user
Return Value: int that represent status. 0 for success , non 0 for failure
*/
typedef int (*avl_action_func_t)(void *data, void *param);

/*
AVLCreate
description: create a binary tree recursive
input: a pointer to a compare function 
return: the binary search tree struct
time complexity: O(1)
space complexity: O(1)
*/
avl_t *AVLCreate(avl_cmp_func_t compare);

/*
AVLDestroy
description: destroy all the elements in the tree
input: a binary search tree structer
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void AVLDestroy(avl_t *tree);

/*
AVLRemove
description: remove an element from the tree
input: tree and data to find and remove
return: status 0 for success otherwise fail
time complexity: worst case: O(log n), avg case:O(log n)
space complexity: O(1)
*/
int AVLRemove(avl_t tree, void *data_to_remove);

/*
AVLInsert
description: insert a new element to the avl
input: a avl and new data
return: status 0 for success otherwise fail
time complexity: worst case: O(log n), avg case:O(log n)
space complexity: O(1)
**Invalid iter is: 
*/
int AVLInsert(avl_t *tree, void *data);

/*
AVLHeight
description: the distance between the root and the most further leaf
input: a avl 
return: the distance
time complexity: worst case: O(log n), avg case:O(log n)
space complexity: O(1)
*/
size_t AVLHeight(const avl_t *tree);

/*
AVLSize
description: return the number of elements in the tree
input: a binary search tree structer
return: number of elements in the binary search tree
time complexity: O(log n)
space complexity: O(1)
*/
size_t AVLSize(const bst_t *tree);

/*
AVLIsEmpty
description: check if avl is empty
input: a avl structer
return: non-0 if empty, 0 if not empty
time complexity: O(1)
space complexity: O(1)
*/
int AVLIsEmpty(const avl_t *tree);

/*
AVLFind
description: searches the tree for a certain element. 
input: a avl and data to search for
return: status 0 for success otherwise fail
time complexity: worst case: O(log n), avg case:O(log n)
space complexity: O(1)
*/
int AVLFind(const avl_t *tree, const void *data);

/*
AVLForEach
description: does a certain action on all the tree(does not change the data it self)
input: tree to run over and execute the action func and a flag for what kind of traverse is desired(1,2,3 - pre, in, post order)
return: the last status the action function returned
time complexity: O(n)
space complexity: O(1)
*/
int AVLForEach(bst_t *tree, bst_action_func_t action, void* param, int flag);


#endif /*__AVL_H__*/

