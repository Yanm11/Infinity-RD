#ifndef __FSQ_H__
#define __FSQ_H__

#include <stddef.h> /* size_t */

typedef struct fsq fsq_t;

/*
FSQCreate
description: Creates a new fsq_t instance. 
input: size_t capacity
return: a pointer to the newly created queue if fail null
time complexity: O(1)
space complexity: O(1)
*/
fsq_t *FSQCreate(size_t capacity, size_t element_size);

/*
FSQDestroy
description: Destroys queue
input: pointer to the queue
return: nothing
time complexity: O(n)
space complexity: O(1)
*/
void FSQDestroy(fsq_t *queue);

/*
FSQEnqueue
description: add new element to the end of the queue.
input: a pointer to the queue
return: 0 success otherwise faill
time complexity  O(1) 
space complexity:  O(1) 
*/
int FSQEnqueue(fsq_t *queue, void *data);

/*
FSQDequeue
description: removes the first element.
input: a pointer to a queue
return: nothing
time complexity: O(1)
space complexity: O(1)
*/
void FSQDequeue(fsq_t *queue, void *dest);

#endif /*__FSQ_H__*/

