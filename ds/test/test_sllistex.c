#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include "sllistex.h"

void CallAllTests();
void TestFlip();
static node_t *CreateNode(void *data, node_t *next);
void TestLoop();


int main(void)
{
	CallAllTests();

	printf("All Tests PASSED!\n");

	return 0;
}

void CallAllTests()
{
	TestFlip();
	TestLoop();
}

void TestFlip()
{
	/* create data and node nulls for linked list */
	int data[] = {10,20,30,40};
	int i = 3;
	node_t *iter = NULL;
	node_t *head = NULL;
	node_t *second = NULL;
	node_t *third = NULL;
	node_t *tail = NULL;
	
	/* allocating memory and assaigning data and next nodes */
	tail = CreateNode(data + 3, NULL);
	third = CreateNode(data + 2, tail);
	second = CreateNode(data + 1, third);
	head = CreateNode(data, second);
	
	/* flip the linked list */
	iter = Flip(head);
	
	while (NULL != iter)
	{
		assert(*(int*)(iter->data) == data[i]);
		iter = iter->next;
		--i;
	}
	
	printf("Test Flip PASEED!\n");
	
	
}

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

void TestLoop()
{
	/* create data and node nulls for linked list */
	int data[] = {10,20,30,40};
	node_t *head = NULL;
	node_t *second = NULL;
	node_t *third = NULL;
	node_t *forth = NULL;
	
	/* allocating memory and assaigning data and next nodes */
	forth = CreateNode(data + 2, head);
	third = CreateNode(data + 2, forth);
	second = CreateNode(data + 1, third);
	head = CreateNode(data, second);
	forth->next = head;
	
	assert(HasLoop(head));
	printf("Test Loop PASEED!\n");	
}

