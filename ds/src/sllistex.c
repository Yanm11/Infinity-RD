#include <assert.h> /* assert */
#include <stddef.h> /* size_t */

#include "sllistex.h"

static size_t CountNodes(node_t *head);
static node_t *AdvanceNode(node_t *head, size_t count);

node_t *Flip(node_t *head)
{
	node_t *new_next = NULL;
	node_t *next_node = NULL; 
	node_t *current_node = NULL;
	
	assert (NULL != head);
	
	next_node = head->next;
	current_node = head;
	
	while (NULL != next_node)
	{
		new_next = next_node->next;
		next_node->next = current_node;
		current_node = next_node;
		next_node = new_next;
	}
	
	head->next = NULL;
	
	return current_node;
}

int HasLoop(const node_t *head)
{
	node_t *ptr_first = NULL;
	node_t *ptr_second = NULL;
	
	assert(NULL != head);
	
	ptr_first = head->next;
	ptr_second = (node_t*)head;
	
	while ((NULL != ptr_first) && (NULL != ptr_first->next))
	{
		if (ptr_first == ptr_second)
		{
			return 1;
		}
		
		ptr_first = ptr_first->next->next;
		ptr_second = ptr_second->next;
	}
	
	return 0;
}

node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	node_t *ptr_first = NULL;
	node_t *ptr_second = NULL;
	size_t count_first = 0;
	size_t count_second = 0;
	size_t diff = 0;
	
	assert(head_1);
	assert(head_2);
	
	ptr_first = head_1;
	ptr_second = head_2;
	
	count_first = CountNodes(head_1);
	count_second = CountNodes(head_2);
	
	if (count_first > count_second)
	{
		diff = count_first - count_second;
		ptr_first = AdvanceNode(ptr_first, diff);
	}
	else
	{
		diff = count_second - count_first;
		ptr_second = AdvanceNode(ptr_second, diff);
	}
	
	while (NULL != ptr_first) 
	{
		if (ptr_first == ptr_second)
		{
			return ptr_first;
		}
		ptr_first = ptr_first->next;
		ptr_second = ptr_second->next;
	}
	
	return NULL;
	
}

static size_t CountNodes(node_t *head)
{
	node_t *ptr_node = NULL;
	size_t count = 0;
	
	assert(head);
	
	ptr_node = head;
	while (NULL != ptr_node->next)
	{
		++count;
		ptr_node = ptr_node->next;
	}
	
	return count;
}

static node_t *AdvanceNode(node_t *head, size_t count)
{
	node_t *ptr_node = NULL;
	
	assert(head);
	
	ptr_node = head;
	while (0 < count)
	{
		ptr_node = ptr_node->next;
		--count;
	}
	
	return ptr_node;
}





