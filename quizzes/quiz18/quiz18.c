#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct node 
{
	void *data;
	struct node *next;
} node_t;

node_t *HasLoop(node_t *head);

static node_t *CreateNode(void *data, node_t *next)
{
	node_t *ptr_node = (node_t*)malloc(sizeof(node_t));
	
	if (NULL == ptr_node)
	{
		return NULL;
	}
	
	ptr_node->data = data;
	ptr_node->next = next;
	
	return ptr_node;
}

int main(void)
{
	/* create data and node nulls for linked list */
	int data[] = {10,20,30,40};
	int n = 1;
	int checker = 0;
	node_t *head = NULL;
	node_t *second = NULL;
	node_t *third = NULL;
	node_t *tail = NULL;
	
	/* allocating memory and assaigning data and next nodes */
	tail = CreateNode(data + 3, NULL);
	third = CreateNode(data + 2, tail);
	second = CreateNode(data + 1, third);
	head = CreateNode(data, second);
	third->next = head;
	
	if (third != HasLoop(head))
	{
		printf("test1 failed\n");
		++checker;
	}
	else
	{
		printf("test1 passed\n");
	}
	
	if (second != ReturnNNodeFromLast(head, n+1))
	{
		printf("test2 failed\n");
		++checker;
	}
	else
	{
		printf("test2 passed\n");
	}
	
	if (head != ReturnNNodeFromLast(head, n+2))
	{
		printf("test3 failed\n");
		++checker;
	}
	else
	{
		printf("test3 passed\n");
	}
	
	if (0 < checker)
	{
		printf("failed %d tests\n", checker);
		return 0;
	}
	
	printf("passed all tests!\n");
	return 0;
	
	

}


node_t *HasLoop(node_t *head)
{
	node_t *node_first = NULL;
	node_t *node_second = NULL;
	
	assert(head);
	
	node_first = head->next;
	node_second = head;
	
	while (NULL != node_frist && NULL != node_first->next)
	{
		if (node_first == node_second)
		{
			return node_first;
		}
		
		node_first = node_first->next->next;
		node_second = node_second->next;
	}
	
	return NULL;
}

