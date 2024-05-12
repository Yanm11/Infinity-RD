#include <assert.h> /* assert */
#include "sllistex.h"


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
