#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/*
QCreate
description: Creates a new queue_t instance. 
input: nothing
return: a pointer to the newly created queue
time complexity: O(1)
space complexity: O(1)
*/
queue_t *QCreate(void);

/*
QDestroy
description: Destroys queue
input: pointer to the queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void QDestroy(queue_t *queue);

/*
QEnqueue
description: add new element to the end of the queue.
input: a pointer to the queue
return: 0 success 1 faill
time complexity  O(1) 
space complexity:  O(1) 
*/
int QEnqueue(queue_t *queue, void *data);

/*
QDequeue
description: removes the first element.
input: a pointer to a queue
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void QDequeue(queue_t *queue);

/*
QSize
description: returns how many elements are in the vector
input: a pointer to the queue
return: number of elemnts in the queue
time complexity: O(n)
space complexity: O(1)
*/
size_t QSize(const queue_t *queue);

/*
QPeek
description: Show the first element in the queue
input: Queue
return: a pointer to the first data in the queue
time complexity: O(1)
space complexity: O(1)
*/
void *QPeek(const queue_t *queue);

/*
IsEmpty
description: Return 1 if queue is empty and 0 if not empty
input: a queue pointer
return: if empty return 1 else 0
time complexity: O(1)
space complexity: O(1)
*/
int QIsEmpty(const queue_t *queue);

/*
QAppend
description: concat 2 queues
input: head of the first queue and tail of the second
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void QAppend(queue_t *dest_queue, queue_t *src_queue);



#endif /*__QUEUE_H__*/

