#ifndef __RC_H__
#define __RC_H__

#include <stddef.h> /*size_t*/

typedef struct node 
{
	void *data;
	struct node *next;
} node_t;

/*
Fibonacci
description: return the element from the fiboncacci seris
input: an index of the element
return: the value of the element
time complexity: O(n)
space complexity: O(1)
*/
int Fibonacci(int element_index);

/*
Flip
description: flip a given single linked list
input: the head of the list
return: the new head;
time complexity: O(n)
space complexity: O(1)
*/
node_t *Flip(node_t *node);

size_t StrLen(const char *s);
int StrCmp(const char *s1, const char *s2);
char *StrCpy(char *dest, const char *src);
char *StrCat(char *dest, const char *src);
char *StrStr(const char *haystack, const char *needle);


#endif /*__RC_H__*/
