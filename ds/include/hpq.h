#ifndef __HPQ_H__
#define __HPQ_H__

#include <stddef.h> /*size_t*/

typedef struct hpq hpq_t;


/*
Description: typedef to pointer function that compares two arguments
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching:
    positive if first argument is larger,
    zero if they equal
    negative if the second argument is larger.
*/
typedef int (*hpq_compare_func_t)(const void*, const void*);

/*
Description: typedef to pointer function that checks if the two arguments are a match
Params: (void *, void *) two elements to compare
Return Value: int that represent the status of the matching, non-zero for a match, 0 for not match
*/
typedef int (*hpq_match_func_t)(const void*, const void*);


/*
PQCreate
description: create PriorityQCreate
input: nothing
return: a pointer to a priority queue, if failed NULL
time complexity: O(1)
space complexity: O(1)
*/
hpq_t *HPQCreate(hpq_compare_func_t cmp_func);

/*
PQDestroy
description: free priority queue
input: pointer to priority queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void HPQDestroy(hpq_t *queue);

/*
PQEnqueue
description: Adds new element to the queue according to its priority - the priority range is -20 - 19, the lower the number the higher its priority.
input: pointer to priority queue, priority of item, pointer to data
return: success status: 0 success, otherwise failure
time complexity: O(n)
space complexity: O(1)
*/
int HPQEnqueue(hpq_t *queue, void *data);

/*
PQDequeue
description: remove the highest priority
input: queue
return: void* to dequeued data  
time complexity: O(1)
space complexity: O(1)
*/
void *HPQDequeue(hpq_t *queue);

/* 
PQPeek
description: Peek at the highest priority element without removing it.
Input:  Pointer to the priority queue.
return: the highest priority element data, - If the queue is empty, undefined
Time Complexity: O(1)
Space Complexity: O(1)
 */
void *HPQPeek(const hpq_t *queue);


/*
PQIsEmpty
description: check if priority queue is empty
input: pointer to priority queue
return: 1 if priority queue is empty otherwise 0
time complexity: O(1)
space complexity: O(1)
*/
int HPQIsEmpty(const hpq_t *queue);


/*
PQSize
description: return the priority queue size
input: pointer to priority queue
return: priority queue size
time complexity: O(n)
space complexity: O(1)
*/
size_t HPQSize(const hpq_t *queue);

/*
PQClear
description: remove all elements in priority queue
input: pointer to priority queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void HPQClear(hpq_t *queue);

/*
PQErase
description: remove specific elements from priority queue
input: pointer to priority queue, a pointer to match function, and a pointer to a parameter
return: the erased data, and NULL if it didn't erase anything.
time complexity: O(n)
space complexity: O(1)
*/
void *HPQErase(hpq_t *queue, hpq_match_func_t is_match, void *param);


#endif /*__HPQ_H__*/

