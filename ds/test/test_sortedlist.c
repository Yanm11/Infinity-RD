#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h> /* free() */

#include "sortedlist.h"

#define TESTNUM 16

static char failed_tests_print[300] = {'\0'};

static void AddFailedTest(const char *str);

static int TestInsert(void);
static int TestRemove(void);
static int TestGetData(void);
static int TestForEach(void);

static int TestSize(void);
static int TestBegin(void);
static int TestNext(void);
static int TestPrev(void);

static int TestEnd(void);
static int TestIsEmpty(void);
static int TestIsSameIter(void);
static int TestMerge(void);

static int TestFind(void);
static int TestFindIf(void);
static int TestPopBack(void);
static int TestPopFront(void);

struct cat
{
	char *name;
	char *favorite_food;
	int age;
};
	
int Compare(const void *data, const void *param)
{	
	return (*(int *)data - *(int *)param);
}

int CompareCats(const void *data, const void *param)
{	
	return (((struct cat *)data)->age - ((struct cat *)param)->age);
}

int FindFavoriteFood(const void *data, void *param)
{	
	return (strcmp(((struct cat *)data)->favorite_food, *(char **)param) == 0);
}


int Sum(void *data, void *param)
{	
	*(int *)param += *(int *)data;
	return (*(int *)param);
}

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestInsert();
	printf("Tested Insert\n");
	failed_tests_num += TestRemove();
	printf("Tested Remove\n");
	failed_tests_num += TestGetData();
	printf("Tested GetData\n");
	failed_tests_num += TestForEach();
	printf("Tested ForEach\n");
	
	failed_tests_num += TestSize();
	printf("Tested Size\n");
	failed_tests_num += TestBegin();
	printf("Tested Begin\n");
	failed_tests_num += TestNext();
	printf("Tested Next\n");
	failed_tests_num += TestPrev();
	printf("Tested Prev\n");
	
	failed_tests_num += TestEnd();
	printf("Tested End\n");
	failed_tests_num += TestIsEmpty();
	printf("Tested IsEmpty\n");
	failed_tests_num += TestIsSameIter();
	printf("Tested IsSameIter\n");
	failed_tests_num += TestMerge();
	printf("Tested Merge\n");
	
	failed_tests_num += TestFind();
	printf("Tested Find\n");
	failed_tests_num += TestFindIf();
	printf("Tested FindIf\n");
	failed_tests_num += TestPopFront();
	printf("Tested PopFront\n");
	failed_tests_num += TestPopBack();
	printf("Tested PopBack\n");
	
	
	if (failed_tests_num)
	{
		printf("%d out %d tests failed\nFailed tests:\n%s"
		, failed_tests_num, TESTNUM, failed_tests_print);
		return failed_tests_num;
	}
	
	printf("All Tests Passed!\n");
	
    return 0;
}

static void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}

static int TestInsert(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	size_t size = 0;
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	
	size = SortedlistSize(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != size || 2 != get_element)
	{
		AddFailedTest("TestInsert1\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestInsert2\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestInsert3\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestInsert4\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestRemove(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	size_t size = 0;
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	
	iter = SortedlistRemove(iter);
	size = SortedlistSize(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3 != size || 4 != get_element)
	{
		AddFailedTest("TestRemove\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	iter = SortedlistRemove(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestRemove\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestRemove\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	size = SortedlistSize(list);
	
	if (2 != size)
	{
		AddFailedTest("TestRemove\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistRemove(iter);
	
	size = SortedlistSize(list);
	
	if (0 != size)
	{
		AddFailedTest("TestRemove\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestGetData(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	
	get_element = *(int *)SortedlistGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestGetData\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestGetData\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestGetData\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestGetData\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestForEach(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	sortedlist_iter_t end = {0};
	int arr[4] = {10, 2, 3100, 4};
	int status = 0;
	int sum = 0;
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	end = SortedlistGetEnd(list);
	status = SortedlistForEach(iter, end, Sum, &sum);
	
	if (10 + 2 + 3100 + 4 != sum)
	{
		AddFailedTest("TestForEach\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	if (status != sum)
	{
		AddFailedTest("TestForEach\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestSize(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	size_t size = 0;
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	size = SortedlistSize(list);
	
	if (0 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* insert 10 */
	SortedlistInsert(list, arr);
	size = SortedlistSize(list);
	
	if (1 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	size = SortedlistSize(list);
	
	if (2 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	size = SortedlistSize(list);
	
	if (3 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	size = SortedlistSize(list);
	
	if (4 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	iter = SortedlistRemove(iter);
	size = SortedlistSize(list);
	
	if (3 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	size = SortedlistSize(list);
	
	if (2 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	size = SortedlistSize(list);
	
	if (1 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	size = SortedlistSize(list);
	
	if (0 != size)
	{
		AddFailedTest("TestSize\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestBegin(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;

	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetBegin(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetBegin(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetBegin(list);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SortedlistDestroy(list);
		return 1;
	}

	SortedlistDestroy(list);
	return 0;
}

static int TestNext(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;

	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetBegin(list);
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestNext\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestNext\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestNext\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistNext(iter);
	if (!SortedlistIsSameIter(iter, SortedlistGetEnd(list)))
	{
		AddFailedTest("TestNext\n");
		SortedlistDestroy(list);
		return 1;
	}

	SortedlistDestroy(list);
	return 0;
}

static int TestPrev(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;

	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestPrev\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestPrev\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestPrev\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistPrev(iter);
	if (!SortedlistIsSameIter(iter, SortedlistGetBegin(list)))
	{
		AddFailedTest("TestPrev\n");
		SortedlistDestroy(list);
		return 1;
	}

	SortedlistDestroy(list);
	return 0;
}

static int TestEnd(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;

	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestEnd\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestEnd\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestEnd\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistRemove(iter);
	iter = SortedlistGetEnd(list);
	iter = SortedlistPrev(iter);
	if (!SortedlistIsSameIter(iter, SortedlistGetBegin(list)))
	{
		AddFailedTest("TestEnd\n");
		SortedlistDestroy(list);
		return 1;
	}

	SortedlistDestroy(list);
	return 0;
}

static int TestIsEmpty(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[4] = {10, 2, 3100, 4};
	
	/* create linked list */
	list = SortedlistCreate(Compare);
	if (!SortedlistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty\n");
		SortedlistDestroy(list);
		return 1;
	}
	/* insert 10 */
	SortedlistInsert(list, arr);
	if (SortedlistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter = SortedlistGetBegin(list);
	iter = SortedlistRemove(iter);
	if (!SortedlistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestIsSameIter(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter1 = {0};
	sortedlist_iter_t iter2 = {0};
	int arr[4] = {10, 2, 3100, 4};
	

	
	/* create linked list */
	list = SortedlistCreate(Compare);
	
	/* insert 10 */
	SortedlistInsert(list, arr);
	/* insert 2 */
	SortedlistInsert(list, arr+1);
	/* insert 3100 */
	SortedlistInsert(list, arr+2);
	/* insert 4 */
	SortedlistInsert(list, arr+3);
	
	/* create an iterator for the HEAD */
	iter1 = SortedlistGetBegin(list);
	iter2 = SortedlistGetBegin(list);
	
	if (!SortedlistIsSameIter(iter1, iter2))
	{
		AddFailedTest("TestIsSameIter\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter2 = SortedlistNext(iter2);
	
	if (SortedlistIsSameIter(iter1, iter2))
	{
		AddFailedTest("TestIsSameIter\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	iter1 = SortedlistNext(iter1);
	
	if (!SortedlistIsSameIter(iter1, iter2))
	{
		AddFailedTest("TestIsSameIter\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestMerge(void)
{
	sortedlist_t *list1 = NULL;
	sortedlist_iter_t iter1 = {0};
	sortedlist_t *list2 = NULL;
	sortedlist_iter_t iter2 = {0};
	int arr[9] = {10, 2, 3100, 4, 17, 23, 100, 100, 5};
	size_t size = 0;
	
	list1 = SortedlistCreate(Compare);
	list2 = SortedlistCreate(Compare);
	
	SortedlistInsert(list1, arr);
	SortedlistInsert(list1, arr+1);
	SortedlistInsert(list1, arr+2);
	SortedlistInsert(list1, arr+3);
	SortedlistInsert(list2, arr+4);
	SortedlistInsert(list2, arr+5);
	SortedlistInsert(list2, arr+6);
	SortedlistInsert(list2, arr+7);
	SortedlistInsert(list2, arr+8);
	
	SortedlistMerge(list1, list2);
	
	size = SortedlistSize(list1);
	if (9 != size)
	{
		AddFailedTest("TestMerge\n");
		SortedlistDestroy(list1);
		SortedlistDestroy(list2);
		return 1;
	}
	
	size = SortedlistSize(list2);
	if (0 != size)
	{
		AddFailedTest("TestMerge\n");
		SortedlistDestroy(list1);
		SortedlistDestroy(list2);
		return 1;
	}
	
	iter1 = SortedlistGetBegin(list1);
	iter2 = SortedlistNext(iter1);
	
	for(; !SortedlistIsSameIter(iter2, SortedlistGetEnd(list1));
			iter2 = SortedlistNext(iter2), iter1 = SortedlistNext(iter1))
	{
		if (*(int *)SortedlistGetData(iter1) > *(int *)SortedlistGetData(iter2))
		{
			AddFailedTest("TestMerge\n");
			SortedlistDestroy(list1);
			SortedlistDestroy(list2);
			return 1;
		}
	}
	
	SortedlistDestroy(list1);
	SortedlistDestroy(list2);
	return 0;
}

static int TestFind(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	int arr[9] = {10, 2, 3100, 4, 17, 23, 100, 100, 5};
	int find = 23;
	int get_element = 0;
		
	list = SortedlistCreate(Compare);
	
	SortedlistInsert(list, arr);
	SortedlistInsert(list, arr+1);
	SortedlistInsert(list, arr+2);
	SortedlistInsert(list, arr+3);
	SortedlistInsert(list, arr+4);
	SortedlistInsert(list, arr+5);
	SortedlistInsert(list, arr+6);
	SortedlistInsert(list, arr+7);
	SortedlistInsert(list, arr+8);
	
	iter = SortedlistFind(list, SortedlistGetBegin(list),
							SortedlistGetEnd(list), &find);
	get_element = *(int *)SortedlistGetData(iter);
	
	if (find != get_element)
	{
		AddFailedTest("TestFind\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	find = 24;
	
	iter = SortedlistFind(list, SortedlistGetBegin(list),
							SortedlistGetEnd(list), &find);
	
	if (!SortedlistIsSameIter(iter, SortedlistGetEnd(list)))
	{
		AddFailedTest("TestFind\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestFindIf(void)
{
	sortedlist_t *list = NULL;
	sortedlist_iter_t iter = {0};
	struct cat honey = {0};
	struct cat garfield = {0};
	struct cat meshugah = {0};
	struct cat bentzi = {0};
	struct cat diana = {0};
	struct cat get_cat = {0};
	char *favorite_food = "garfield";
	
	honey.name = "honey";
	honey.favorite_food = "tuna";
	honey.age = 1;
	
	garfield.name = "garfield";
	garfield.favorite_food = "lasagna";
	garfield.age = 43;
	
	meshugah.name = "meshugah";
	meshugah.favorite_food = "garfield";
	meshugah.age = 7;
	
	bentzi.name = "bentzi";
	bentzi.favorite_food = "melafefon";
	bentzi.age = 12;
	
	diana.name = "diana";
	diana.favorite_food = "salmon";
	diana.age = 4;
	
	list = SortedlistCreate(CompareCats);
	
	SortedlistInsert(list, &honey);
	SortedlistInsert(list, &garfield);
	SortedlistInsert(list, &meshugah);
	SortedlistInsert(list, &bentzi);
	SortedlistInsert(list, &diana);
	
	iter = SortedlistFindIf(
    SortedlistGetBegin(list), SortedlistGetEnd(list),
     FindFavoriteFood, &favorite_food);
	
	get_cat = *(struct cat *)SortedlistGetData(iter);
	
	if (strcmp(get_cat.name, meshugah.name))
	{
		AddFailedTest("TestFindIf\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	favorite_food = "diana";
	
	iter = SortedlistFindIf(
    SortedlistGetBegin(list), SortedlistGetEnd(list),
     FindFavoriteFood, &favorite_food);
     
	if (!SortedlistIsSameIter(iter, SortedlistGetEnd(list)))
	{
		AddFailedTest("TestFindIf\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestPopBack(void)
{
	sortedlist_t *list = NULL;
	struct cat honey = {0};
	struct cat garfield = {0};
	struct cat meshugah = {0};
	struct cat bentzi = {0};
	struct cat diana = {0};
	struct cat get_cat = {0};
	size_t size = 0;
	
	honey.name = "honey";
	honey.favorite_food = "tuna";
	honey.age = 1;
	
	garfield.name = "garfield";
	garfield.favorite_food = "lasagna";
	garfield.age = 43;
	
	meshugah.name = "meshugah";
	meshugah.favorite_food = "garfield";
	meshugah.age = 7;
	
	bentzi.name = "bentzi";
	bentzi.favorite_food = "melafefon";
	bentzi.age = 12;
	
	diana.name = "diana";
	diana.favorite_food = "salmon";
	diana.age = 4;
	
	list = SortedlistCreate(CompareCats);
	
	SortedlistInsert(list, &honey);
	SortedlistInsert(list, &garfield);
	SortedlistInsert(list, &meshugah);
	SortedlistInsert(list, &bentzi);
	SortedlistInsert(list, &diana);
	
	get_cat = *(struct cat *)SortedlistPopBack(list);
	size = SortedlistSize(list);
	
	if (4 != size || 43 != get_cat.age)
	{
		AddFailedTest("TestPopBack\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopBack(list);
	size = SortedlistSize(list);
	
	if (3 != size || 12 != get_cat.age)
	{
		AddFailedTest("TestPopBack\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopBack(list);
	size = SortedlistSize(list);
	
	if (2 != size || 7 != get_cat.age)
	{
		AddFailedTest("TestPopBack\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopBack(list);
	size = SortedlistSize(list);
	
	if (1 != size || 4 != get_cat.age)
	{
		AddFailedTest("TestPopBack\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopBack(list);
	size = SortedlistSize(list);
	
	if (0 != size || 1 != get_cat.age)
	{
		AddFailedTest("TestPopBack\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}

static int TestPopFront(void)
{
	sortedlist_t *list = NULL;
	struct cat honey = {0};
	struct cat garfield = {0};
	struct cat meshugah = {0};
	struct cat bentzi = {0};
	struct cat diana = {0};
	struct cat get_cat = {0};
	size_t size = 0;
	
	honey.name = "honey";
	honey.favorite_food = "tuna";
	honey.age = 1;
	
	garfield.name = "garfield";
	garfield.favorite_food = "lasagna";
	garfield.age = 43;
	
	meshugah.name = "meshugah";
	meshugah.favorite_food = "garfield";
	meshugah.age = 7;
	
	bentzi.name = "bentzi";
	bentzi.favorite_food = "melafefon";
	bentzi.age = 12;
	
	diana.name = "diana";
	diana.favorite_food = "salmon";
	diana.age = 4;
	
	list = SortedlistCreate(CompareCats);
	
	SortedlistInsert(list, &honey);
	SortedlistInsert(list, &garfield);
	SortedlistInsert(list, &meshugah);
	SortedlistInsert(list, &bentzi);
	SortedlistInsert(list, &diana);
	
	get_cat = *(struct cat *)SortedlistPopFront(list);
	size = SortedlistSize(list);
	
	if (4 != size || 1 != get_cat.age)
	{
		AddFailedTest("TestPopFront\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopFront(list);
	size = SortedlistSize(list);
	
	if (3 != size || 4 != get_cat.age)
	{
		AddFailedTest("TestPopFront\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopFront(list);
	size = SortedlistSize(list);
	
	if (2 != size || 7 != get_cat.age)
	{
		AddFailedTest("TestPopFront\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopFront(list);
	size = SortedlistSize(list);
	
	if (1 != size || 12 != get_cat.age)
	{
		AddFailedTest("TestPopFront\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	get_cat = *(struct cat *)SortedlistPopFront(list);
	size = SortedlistSize(list);
	
	if (0 != size || 43 != get_cat.age)
	{
		AddFailedTest("TestPopFront\n");
		SortedlistDestroy(list);
		return 1;
	}
	
	SortedlistDestroy(list);
	return 0;
}






