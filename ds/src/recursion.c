#include <assert.h> /* assert */
#include <string.h> /* strncmp */

#include "recursion.h"
#include "stack.h"

static void InsertSorted(stack_t *stack, void *element);

int Fibonacci(int element_index)
{	
	assert(0 <= element_index);
	
	if (1 >= element_index)
	{
		return element_index;
	}
	
	return Fibonacci(element_index - 1) + Fibonacci(element_index - 2);
}

node_t *Flip(node_t *node)
{	
	node_t *node_head = NULL;
	
	assert(node);
	
	if (NULL == node->next)
	{
		return node; 
	}	
	
	node_head = Flip(node->next);
	node->next->next = node;
	node->next = NULL;
	
	return node_head;
}

size_t StrLen(const char *s)
{
	if ('\0' == *s)
	{
		return 0;
	}
	
	return StrLen(s + 1) + 1;
}

int StrCmp(const char *s1, const char *s2)
{
	if ((*s1 - *s2) || ('\0' == *s1) || ('\0' == *s2))
	{
		return *s1 -*s2;
	}

	return StrCmp(s1 + 1, s2 + 1);
}

char *StrCpy(char *dest, const char *src)
{
	if ('\0' == *src)
	{
		*dest = *src;
		
		return dest;
	}
	
	StrCpy(dest + 1, src + 1);
	*dest = *src;
	
	return dest;
}

char *StrCat(char *dest, const char *src)
{
	if ('\0' == *dest)
	{
		StrCpy(dest, src);
		
		return dest;
	}
	
	StrCat(dest + 1, src);

	return dest;
}

char *StrStr(const char *haystack, const char *needle)
{
	if ('\0' == *haystack || !strncmp(haystack, needle, StrLen(needle)))
	{
		return (char*)haystack;
	}
	
	return StrStr(haystack + 1, needle);
}

void SortStack(stack_t *stack)
{
	int element = 0;
	
	assert(stack);
	
	if(StackIsEmpty(stack))
	{
		return;
	}
	
	element = *(int*)StackPeek(stack);
	StackPop(stack);
	
	SortStack(stack);
	
	InsertSorted(stack, &element);
}

static void InsertSorted(stack_t *stack, void *element)
{
	int curr_peek = 0;
	
	assert(stack);
	
	if (StackIsEmpty(stack) || *(int*)element < *(int*)StackPeek(stack))
	{
		StackPush(stack, element);
		
		return;
	}
	
	curr_peek = *(int*)StackPeek(stack);
	StackPop(stack);
	InsertSorted(stack, element);
	StackPush(stack, &curr_peek);
}






