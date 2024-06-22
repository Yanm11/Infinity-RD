#include <stdio.h> /* printf */
#include <stdlib.h> /* maloc free */
#include <assert.h> /* assert */
#include <string.h> /* strlen */

#include "recursion.h"

void TestFibonacci(void);
void TestFlip(void);
void TestStrLen(void);
void TestStrCmp(void);
void TestStrCpy(void);
void TestStrCat(void);
void TestStrStr(void);
void TestStack(void);

static node_t *CreateNode(void *data, node_t *next);

int main(void)
{
	TestFibonacci();
	TestFlip();
	TestStrLen();
	TestStrCmp();
	TestStrCpy();
	TestStrCat();
	TestStrStr();
	TestStack();
	
	return 0;
}

void TestFibonacci(void)
{
	int n = 26;
	int element = 0;
	
	element = Fibonacci(n);
	
	printf("element %d in Fibonnaci is %d\n", n, element);
}

void TestFlip(void)
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
	
	free(head);	
	free(second);
	free(third);
	free(tail);	
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

void TestStrLen(void)
{
	char *s = "123456789";
	
	if (strlen(s) != StrLen(s))
	{
		printf("didnt pass strlen test 1\nStrLen: %ld\n", StrLen(s));
		return;
	}
	
	s = "";
	if (strlen(s) != StrLen(s))
	{
		printf("didnt pass strlen test 2\nStrLen: %ld\n", StrLen(s));
		return;
	}
	
	s = "1";
	if (strlen(s) != StrLen(s))
	{
		printf("didnt pass strlen test 3\nStrLen: %ld\n", StrLen(s));
		return;
	}
	
	s = "12";
	if (strlen(s) != StrLen(s))
	{
		printf("didnt pass strlen test 4\nStrLen: %ld\n", StrLen(s));
		return;
	}
	
	s = "12345\012345";
	if (strlen(s) != StrLen(s))
	{
		printf("didnt pass strlen test 5\nStrLen: %ld\n", StrLen(s));
		return;
	}
	
	printf("Passed all test for strlen\n");
}

void TestStrCmp(void)
{
	char *s1 = "123456789";
	char *s2 = "123456789";
	
	if (strcmp(s1, s2) != StrCmp(s1, s2))
	{
		printf("didnt pass strcmp test 1\nStrCmp: %d\n", StrCmp(s1, s2));
		return;
	}
	
	s1 = "abc";
	s2 = "adb";
	if (!(strcmp(s1, s2) < 0) && !(StrCmp(s1, s2) < 0))
	{
		printf("didnt pass strcmp test 2\nStrCmp: %d\n", strcmp(s1, s2));
		return;
	}
	
	s1 = "abc";
	s2 = "ABC";
	if (!(strcmp(s1, s2) > 0) && !(StrCmp(s1, s2) > 0))
	{
		printf("didnt pass strcmp test 3\nStrCmp: %d\n", StrCmp(s1, s2));
		return;
	}
	
	s1 = "abcd";
	s2 = "abc";
	if (!(strcmp(s1, s2) > 0) && !(StrCmp(s1, s2) > 0))
	{
		printf("didnt pass strcmp test 4\nStrCmp: %d\n", StrCmp(s1, s2));
		return;
	}
	
	s1 = "abcdEfG";
	s2 = "abcdEfG";
	if (!(strcmp(s1, s2) == 0) && !(StrCmp(s1, s2) == 0))
	{
		printf("didnt pass strcmp test 5\nStrCmp: %d\n", StrCmp(s1, s2));
		return;
	}
	
	printf("Passed all test for strcmp\n");
}

void TestStrCpy(void)
{
	char dest[5];
	char *src = "1234";
	
	StrCpy(dest, src);
	if ((StrCmp(dest, src)))
	{
		printf("Failed strcpy test 1\nStrCpy: %s\n", dest);
		return;
	}
	
	src = "ASFR";
	StrCpy(dest, src);
	if ((StrCmp(dest, src)))
	{
		printf("Failed strcpy test 2\nStrCpy: %s\n", dest);
		return;
	}
	
	src = "";
	StrCpy(dest, src);
	if ((StrCmp(dest, src)))
	{
		printf("Failed strcpy test 3\nStrCpy: %s\n", dest);
		return;
	}
	
	src = "ASF";
	StrCpy(dest, src);
	if ((StrCmp(dest, src)))
	{
		printf("Failed strcpy test 4\nStrCpy: %s\n", dest);
		return;
	}
	
	
	printf("Passed all test for strcpy\n");
}

void TestStrCat(void)
{
	char dest[10];
	char *src = "12345";
	
	StrCpy(dest, src);

	StrCat(dest, "67");
	if ((StrCmp(dest, "1234567")))
	{
		printf("Failed strcat test 1\nStrCat: %s\n", dest);
		return;
	}
	
	StrCat(dest, "8");
	if ((StrCmp(dest, "12345678")))
	{
		printf("Failed strcat test 2\nStrCat: %s\n", dest);
		return;
	}
	
	StrCat(dest, "9");
	if ((StrCmp(dest, "123456789")))
	{
		printf("Failed strcat test 3\nStrCat: %s\n", dest);
		return;
	}
	
	
	printf("Passed all test for strcat\n");
}

void TestStrStr(void)
{
	char *haystack = "infinity159";
	char *needle = "159";

	if ((StrCmp(StrStr(haystack, needle), strstr(haystack, needle))))
	{
		printf("Failed strstr test 1\nStrstr: %s\n", StrStr(haystack, needle));
		return;
	}
	
	haystack = "abcdefg";
	needle = "g";
	if ((StrCmp(StrStr(haystack, needle), strstr(haystack, needle))))
	{
		printf("Failed strstr test 2\nStrstr: %s\n", StrStr(haystack, needle));
		return;
	}
	
	haystack = "abcdefg";
	needle = "8";
	if ((StrCmp(StrStr(haystack, needle), "\0")))
	{
		printf("Failed strstr test 3\nStrstr: %s\n", StrStr(haystack, needle));
		return;
	}
	
	
	printf("Passed all test for strstr\n");
}

void TestStack(void)
{
	size_t capacity = 100;
	size_t elem_size = 4;
	stack_t *stack_ptr = NULL;
	size_t i = 0;
	
	
	stack_ptr = StackCreate(capacity,elem_size);
	
	for (i = 0; i < capacity; ++i)
	{
		StackPush(stack_ptr, &i);
	}
	
	SortStack(stack_ptr);
	
	for (i = 0; i < capacity; ++i)
	{
		if (*(int*)StackPeek(stack_ptr) != (int)i)
		{
			printf("FAILED Stack test at i: %ld\nstack value: %d\n", i, *(int*)StackPeek(stack_ptr));
			return;
		}
		StackPop(stack_ptr);
	}
	
	StackDestroy(stack_ptr);

	printf("Passed all test for stack\n");
}


