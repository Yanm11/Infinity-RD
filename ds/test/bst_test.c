#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h> /* free() */
#include <assert.h>

#include "bst.h"

#define TESTNUM 12

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
static int TestFind(void);


int Compare(const void *data,const void *param)
{	
	assert(data);
	assert(param);
	
	return (*(int *)data - *(int *)param);
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
	failed_tests_num += TestFind();
	printf("Tested Find\n");

	
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
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	size_t size = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the BEGIN */
	iter = BSTBegin(tree);
	
	size = BSTSize(tree);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != size || 2 != get_element)
	{
		AddFailedTest("TestInsert1\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestInsert2\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestInsert3\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestInsert4\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestRemove(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[15] = {10, 2, 3100, 4, 50, 30, 70, 40, 60, 35, 65, 32, 38, 67, 64};
	int get_element = 0;
	size_t size = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the HEAD */
	iter = BSTBegin(tree);
	
	get_element = *(int *)BSTRemove(iter);
	size = BSTSize(tree);
	
	if (3 != size || 2 != get_element)
	{
		AddFailedTest("TestRemove1\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTBegin(tree);
	iter = BSTNext(iter);
	get_element = *(int *)BSTRemove(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestRemove2\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTBegin(tree);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestRemove3\n");
		BSTDestroy(tree);
		return 1;
	}
	
	size = BSTSize(tree);
	
	if (2 != size)
	{
		AddFailedTest("TestRemove4\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTBegin(tree);
	BSTRemove(iter);
	
	size = BSTSize(tree);
	
	if (0 != size)
	{
		AddFailedTest("TestRemove5\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTInsert(tree, arr+4);
	BSTInsert(tree, arr+5);
	BSTInsert(tree, arr+6);
	BSTInsert(tree, arr+7);
	BSTInsert(tree, arr+8);
	BSTInsert(tree, arr+9);
	BSTInsert(tree, arr+10);
	BSTInsert(tree, arr+11);
	BSTInsert(tree, arr+12);
	BSTInsert(tree, arr+13);
	BSTInsert(tree, arr+14);
	
	iter = BSTFind(tree, arr+8);
	get_element = *(int *)BSTRemove(iter);
	if (60 != get_element)
	{
		AddFailedTest("TestRemove6\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTFind(tree, arr+4);
	get_element = *(int *)BSTRemove(iter);
	if (50 != get_element)
	{
		AddFailedTest("TestRemove6\n");
		BSTDestroy(tree);
		return 1;
	}
	
	size = BSTSize(tree);
	
	if (9 != size)
	{
		AddFailedTest("TestRemove5\n");
		BSTDestroy(tree);
		return 1;
	}
	
	
	BSTDestroy(tree);
	return 0;
}

static int TestGetData(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the BEGIN */
	iter = BSTBegin(tree);
	
	get_element = *(int *)BSTGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestGetData\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestGetData\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestGetData\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestGetData\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestForEach(void)
{
	bst_t *tree = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int status = 0;
	int sum = 0;
	
	/* create linked tree */
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	
	status = BSTForEach(tree, Sum, &sum);
	
	if (10 + 2 + 3100 + 4 != sum)
	{
		AddFailedTest("TestForEach\n");
		BSTDestroy(tree);
		return 1;
	}
	
	if (status != sum)
	{
		AddFailedTest("TestForEach\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestSize(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	size_t size = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	size = BSTSize(tree);
	if (0 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 10 */
	BSTInsert(tree, arr);
	size = BSTSize(tree);
	if (1 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 2 */
	BSTInsert(tree, arr+1);
	size = BSTSize(tree);
	if (2 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	size = BSTSize(tree);
	if (3 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 4 */
	BSTInsert(tree, arr+3);
	size = BSTSize(tree);
	if (4 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* create an iterator for the HEAD */
	iter = BSTBegin(tree);
	
	BSTRemove(iter);
	size = BSTSize(tree);
	
	if (3 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTBegin(tree);
	iter = BSTNext(iter);
	
	BSTRemove(iter);
	size = BSTSize(tree);
	if (2 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	size = BSTSize(tree);
	if (1 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTBegin(tree);
	
	BSTRemove(iter);
	size = BSTSize(tree);
	if (0 != size)
	{
		AddFailedTest("TestSize\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestBegin(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the BEGIN */
	iter = BSTBegin(tree);
	
	get_element = *(int *)BSTGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestBegin\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTBegin(tree);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestBegin\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTBegin(tree);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestBegin\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTBegin(tree);
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestBegin\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestNext(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the BEGIN */
	iter = BSTBegin(tree);
	
	get_element = *(int *)BSTGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestNext\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestNext\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTPrev(iter);
	iter = BSTPrev(iter);
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestNext\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTNext(iter);
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestNext\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestPrev(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the END */
	iter = BSTEnd(tree);
	iter = BSTPrev(iter);
	
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestPrev\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTPrev(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestPrev\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTPrev(iter);
	iter = BSTPrev(iter);
	iter = BSTNext(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestPrev\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTPrev(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestPrev\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestEnd(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	bst_iter_t iter1 = NULL;
	int arr[4] = {10, 2, 3100, 4};
	int get_element = 0;
	size_t loop_count = 0;
	
	/*create tree*/
	tree = BSTCreate(Compare);
	
	/* insert 10 */
	BSTInsert(tree, arr);
	/* insert 2 */
	BSTInsert(tree, arr+1);
	/* insert 3100 */
	BSTInsert(tree, arr+2);
	/* insert 4 */
	BSTInsert(tree, arr+3);
	
	/* create an iterator for the END */
	iter = BSTEnd(tree);
	iter1 = BSTBegin(tree);
	
	while(!BSTIsSameIter(iter, iter1))
	{
		++loop_count;
		iter1 = BSTNext(iter1);
	}
	
	if (4 != loop_count)
	{
		AddFailedTest("TestEnd1\n");
		BSTDestroy(tree);
		return 1;
	}
	
	iter = BSTPrev(iter);
	
	get_element = *(int *)BSTGetData(iter);
	
	if (3100 != get_element)
	{
		AddFailedTest("TestEnd2\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTEnd(tree);
	iter = BSTPrev(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestEnd3\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTEnd(tree);
	iter = BSTPrev(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (4 != get_element)
	{
		AddFailedTest("TestEnd4\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTEnd(tree);
	iter = BSTPrev(iter);
	get_element = *(int *)BSTGetData(iter);
	
	if (2 != get_element)
	{
		AddFailedTest("TestEnd5\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestIsEmpty(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};

	
	/*create tree*/
	tree = BSTCreate(Compare);
	if (!BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 10 */
	iter = BSTInsert(tree, arr);
	if (BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	if (!BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestIsSameIter(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};

	
	/*create tree*/
	tree = BSTCreate(Compare);
	if (!BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsSameIter\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 10 */
	iter = BSTInsert(tree, arr);
	if (BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsSameIter\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	if (!BSTIsEmpty(tree))
	{
		AddFailedTest("TestIsSameIter\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}

static int TestFind(void)
{
	bst_t *tree = NULL;
	bst_iter_t iter = NULL;
	int arr[4] = {10, 2, 3100, 4};

	
	/*create tree*/
	tree = BSTCreate(Compare);
	iter = BSTFind(tree, arr);
	if (!BSTIsSameIter(iter,BSTEnd(tree)))
	{
		AddFailedTest("TestFind\n");
		BSTDestroy(tree);
		return 1;
	}
	
	/* insert 10 */
	iter = BSTInsert(tree, arr);
	iter = BSTFind(tree, arr);
	if (10 != *(int *)BSTGetData(iter))
	{
		AddFailedTest("TestFind\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTRemove(iter);
	iter = BSTFind(tree, arr);
	if (!BSTIsSameIter(iter,BSTEnd(tree)))
	{
		AddFailedTest("TestFind\n");
		BSTDestroy(tree);
		return 1;
	}
	
	BSTDestroy(tree);
	return 0;
}







