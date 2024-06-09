#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


typedef struct node 
{
	void *data;
	struct node *next;
} node_t;

node_t *HasLoop(node_t *head);
void OpenLoop(node_t *head);

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
	int checker = 0;
	node_t *head = NULL;
	node_t *second = NULL;
	node_t *third = NULL;
	node_t *eleven = NULL;
	node_t *ten = NULL;
	node_t *nine = NULL;
	node_t *eight = NULL;
	node_t *seven = NULL;
	node_t *six = NULL;
	node_t *fith = NULL;
	node_t *forth = NULL;

	
	/* allocating memory and assaigning data and next nodes */
	eleven = CreateNode(data + 3, NULL);
	ten = CreateNode(data + 2, eleven);
	nine = CreateNode(data + 1, ten);
	eight = CreateNode(data + 1, nine);
	seven = CreateNode(data + 1, eight);
	six = CreateNode(data + 1, seven);
	fith = CreateNode(data + 1, six);
	forth = CreateNode(data + 1, fith);
	third = CreateNode(data + 1, forth);
	second = CreateNode(data + 1, third);
	head = CreateNode(data, second);
	
	ten->next = fith;
	if (NULL == HasLoop(head))
	{
		printf("test1 failed\n");
		++checker;
	}
	
	OpenLoop(head);
	if (NULL != ten->next)
	{
		printf("test1 failed\n");
		++checker;
	}
	
	

	
	printf("passed all tests!\n");
	return 0;
	
	

}


node_t *HasLoop(node_t *head)
{
	node_t *node_fast = NULL;
	node_t *node_slow = NULL;
	
	assert(head);
	
	node_fast = head->next;
	node_slow = head;
	
	while (NULL != node_fast && NULL != node_fast->next)
	{
		if (node_fast == node_slow)
		{
			return node_fast;
		}
		
		node_fast = node_fast->next->next;
		node_slow = node_slow->next;
	}
	
	return NULL;
}

void OpenLoop(node_t *head)
{
	node_t *node_loop = NULL;
	node_t *node_head = NULL;
	
	assert(head);
	
	node_loop = HasLoop(head);
	node_head = head;
	
	if (NULL == node_loop)
	{
		return;
	}
	
	while (node_loop->next != node_head)
	{	
		node_loop = node_loop->next;
		node_head = node_head->next;
	}
	
	node_loop->next = NULL;
}

