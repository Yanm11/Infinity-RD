#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

typedef struct node 
{
	void *data;
	struct node *next;
} node_t;

static node_t *CreateNode(void *data, node_t *next);
void TestIntersection();
node_t *Intersection(node_t *head1, node_t *head2);
void Separate(node_t *head1, node_t *head2);
static size_t CountNodes(node_t *head);



int main(void)
{
	TestIntersection();

	printf("All Tests PASSED!\n");

	return 0;
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


void TestIntersection()
{
	/* create data and node nulls for linked list */
	int data[] = {10,20,30,40};
	node_t *head = NULL;
	node_t *head2 = NULL;
	node_t *second = NULL;
	node_t *second2 = NULL;
	node_t *third = NULL;
	node_t *third2 = NULL;
	node_t *tail = NULL;
	node_t *forth = NULL;
	node_t *fifth = NULL;
	
	/* allocating memory and assaigning data and next nodes */
	tail = CreateNode(data + 3, NULL);
	third = CreateNode(data + 2, tail);
	second = CreateNode(data + 1, third);
	head = CreateNode(data, second);
	
	/* allocating memory and assaigning data and next nodes */
	fifth = CreateNode(data + 2, third);
	forth = CreateNode(data + 2, fifth);
	third2 = CreateNode(data + 2, forth);
	second2 = CreateNode(data + 1, third2);
	head2 = CreateNode(data, second2);
	
	assert(Intersection(head, head2) == second);
	printf("Test Intersection PASEED!\n");
	Separate(head, head2);
	assert(Intersection(head, head2) == NULL);
	printf("Test SEPARATION PASEED!\n");
	
	free(head);	
	free(head2);
	free(second);
	free(second2);
	free(third);
	free(third2);
	free(tail);
	free(forth);
	free(fifth);
}






node_t *Intersection(node_t *head1, node_t *head2)
{
	size_t node_number1 = 0;
	size_t node_number2 = 0;
	size_t node_to_move = 0;
	
	assert(head1);
	assert(head2);
	
	node_number1 = CountNodes(head1);
	node_number2 = CountNodes(head2);
	
	if (node_number1 > node_number2)
	{
		node_to_move = node_number1 - node_number2;
		while (0 < node_to_move)
		{
			head1 = head1->next;
			--node_to_move;
		}
	}
	else
	{
		node_to_move = node_number2 - node_number1;
		while (0 < node_to_move)
		{
			head2 = head2->next;
			--node_to_move;
		}
	}
	
	while (head1->next != head2->next) 
	{
		head1 = head1->next;
		head2 = head2->next;
	}
	
	if (NULL == head1->next)
	{
		return NULL;
	}
	
	return head1;
}

void Separate(node_t *head1, node_t *head2)
{
	node_t *node_before_intersection = NULL;
	
	assert(head1);
	assert(head2);
	
	node_before_intersection = Intersection(head1, head2);
	if (NULL == node_before_intersection)
	{
		return;
	}
	
	node_before_intersection->next = NULL;
}

static size_t CountNodes(node_t *head)
{
	size_t count = 0;
	
	assert(head);
	
	while (NULL != head->next)
	{
		++count;
		head = head->next;
	}
	
	return count;
}
