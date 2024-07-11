#include <stdio.h> /* printf() */
#include <string.h>  /* strcat() */
#include <stdlib.h> /* free() */
#include <assert.h>

#include "avl.h"

#define TESTNUM 7

static char failed_tests_print[300] = {'\0'};

static void AddFailedTest(const char *str);

static int TestInsert(void);
static int TestRemove(void);
static int TestForEach(void);
static int TestCount(void);

static int TestIsEmpty(void);
static int TestFind(void);
static int TestHeight(void);


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

int SumArray(int arr[], size_t len)
{	
	int sum = 0;
	size_t i = 0;
	for(; i < len; ++i)
	{
		sum += arr[i];
	}
	return sum;
}

int main(void)
{
	int failed_tests_num = 0;
	
	failed_tests_num += TestInsert();
	printf("Tested Insert\n");
	failed_tests_num += TestRemove();
	printf("Tested Remove\n");
	failed_tests_num += TestForEach();
	printf("Tested ForEach\n");
	failed_tests_num += TestCount();
	printf("Tested Count\n");
	

	failed_tests_num += TestIsEmpty();
	printf("Tested IsEmpty\n");
	failed_tests_num += TestFind();
	printf("Tested Find\n");
	failed_tests_num += TestHeight();
	printf("Tested Height\n");
	
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
	avl_t *tree = NULL;
	int arr[8] = {50, 40, 25, 70, 80, 60, 10, 100};
	int get_element = 0;
	size_t count = 0;
	int get_height = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	
	/*	insert 50 */
	AVLInsert(tree, arr);
	get_height = AVLHeight(tree);
	if (1 != get_height)
	{
		AddFailedTest("TestInsert1\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 40 */
	AVLInsert(tree, arr+1);
	get_height = AVLHeight(tree);
	if (2 != get_height)
	{
		AddFailedTest("TestInsert2\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 25, needs to rotate */
	AVLInsert(tree, arr+2);
	get_height = AVLHeight(tree);
	if (2 != get_height)
	{
		AddFailedTest("TestInsert3\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 70 */
	AVLInsert(tree, arr+3);	
	count = AVLCount(tree);
	if (4 != count)
	{
		AddFailedTest("TestInsert4\n");
		AVLDestroy(tree);
		return 1;
	}

	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestInsert5\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 80, needs to rotate */
	AVLInsert(tree, arr+4);
	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestInsert6\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 60, needs to rotate */
	AVLInsert(tree, arr+5);
	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestInsert7\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 10, needs to rotate */
	AVLInsert(tree, arr+6);
	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestInsert8\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 100 */
	AVLInsert(tree, arr+7);
	get_height = AVLHeight(tree);
	if (4 != get_height)
	{
		AddFailedTest("TestInsert9\n");
		AVLDestroy(tree);
		return 1;
	}

	count = AVLCount(tree);
	if (8 != count)
	{
		AddFailedTest("TestInsert10\n");
		AVLDestroy(tree);
		return 1;
	}

	AVLDestroy(tree);
	return 0;
}

static int TestRemove(void)
{
	avl_t *tree = NULL;
	int arr[15] = {10, 2, 3100, 4, 50, 30, 70, 40, 60, 35, 65, 7, 8, 9, 1};
	int get_height = 0;
	size_t count = 0;
	size_t loop_count = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	
	for(; loop_count < 15; ++loop_count)
	{
		AVLInsert(tree, arr+loop_count);
	}

	/*	remove 1 */
	AVLRemove(tree, arr + 14);
	count = AVLCount(tree);
	if (14 != count)
	{
		AddFailedTest("TestRemove1\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/*	remove 9 */
	AVLRemove(tree, arr + 13);
	/*	remove 8 */
	AVLRemove(tree, arr + 12);
	/*	remove 7 */
	AVLRemove(tree, arr + 11);
	/*	remove 2, needs to rotate */
	AVLRemove(tree, arr + 1);
	/*	remove 4, needs to rotate */
	AVLRemove(tree, arr + 3);
	/*	remove 10, needs to rotate */
	AVLRemove(tree, arr);
	
	count = AVLCount(tree);
	if (8 != count)
	{
		AddFailedTest("TestRemove2\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}


static int TestForEach(void)
{
	avl_t *tree = NULL;
	int arr[15] = {10, 2, 3100, 4, 50, 30, 70, 40, 60, 35, 65, 7, 8, 9, 1};
	int sum = 0;
	int status = 0;
	size_t count = 0;
	size_t loop_count = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	
	for(; loop_count < 15; ++loop_count)
	{
		AVLInsert(tree, arr+loop_count);
	}
	
	AVLRemove(tree, arr + 3);
	
	status = AVLForEach(tree, Sum, &sum);
	
	if (SumArray(arr, 15) - arr[3] != sum)
	{
		AddFailedTest("TestForEach\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}

static int TestCount(void)
{
	avl_t *tree = NULL;
	int arr[8] = {50, 40, 25, 70, 80, 60, 10, 100};
	int get_element = 0;
	size_t count = 0;
	int get_height = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	count = AVLCount(tree);
	if (0 != count)
	{
		AddFailedTest("TestCount1\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/*	insert 50 */
	AVLInsert(tree, arr);
	count = AVLCount(tree);
	if (1 != count)
	{
		AddFailedTest("TestCount2\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 40 */
	AVLInsert(tree, arr+1);
	count = AVLCount(tree);
	if (2 != count)
	{
		AddFailedTest("TestCount3\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 25, needs to rotate */
	AVLInsert(tree, arr+2);
	count = AVLCount(tree);
	if (3 != count)
	{
		AddFailedTest("TestCount4\n");
		AVLDestroy(tree);
		return 1;
	}

	/*	insert 70 */
	AVLInsert(tree, arr+3);	
	count = AVLCount(tree);
	if (4 != count)
	{
		AddFailedTest("TestCount5\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/* remove 25 */
	AVLRemove(tree, arr + 2);
	count = AVLCount(tree);
	if (3 != count)
	{
		AddFailedTest("TestCount6\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/* remove 50 */
	AVLRemove(tree, arr);
	count = AVLCount(tree);
	if (2 != count)
	{
		AddFailedTest("TestCount7\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/* remove 40 */
	AVLRemove(tree, arr + 1);
	count = AVLCount(tree);
	if (1 != count)
	{
		AddFailedTest("TestCount8\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/* remove 70 */
	AVLRemove(tree, arr + 3);
	count = AVLCount(tree);
	if (0 != count)
	{
		AddFailedTest("TestCount9\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}


static int TestIsEmpty(void)
{
	avl_t *tree = NULL;
	int arr[8] = {50, 40, 25, 70, 80, 60, 10, 100};
	int get_element = 0;
	size_t count = 0;
	int get_height = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);

	if (!AVLIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty1\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/*	insert 50 */
	AVLInsert(tree, arr);
	
	if (AVLIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty2\n");
		AVLDestroy(tree);
		return 1;
	}
	
	/*	remove 50 */
	AVLRemove(tree, arr);
	
	if (!AVLIsEmpty(tree))
	{
		AddFailedTest("TestIsEmpty3\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}

static int TestFind(void)
{
	avl_t *tree = NULL;
	int arr[15] = {10, 2, 3100, 4, 50, 30, 70, 40, 60, 35, 65, 7, 8, 9, 1};
	void *find_data = NULL;
	size_t count = 0;
	size_t loop_count = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	
	for(; loop_count < 14; ++loop_count)
	{
		AVLInsert(tree, arr+loop_count);
	}
	
	find_data = AVLFind(tree, arr+8);
	
	if (*(int *)find_data != arr[8])
	{
		AddFailedTest("TestFind1\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLRemove(tree, arr+8);
	
	find_data = AVLFind(tree, arr+8);
	
	if (find_data)
	{
		AddFailedTest("TestFind2\n");
		AVLDestroy(tree);
		return 1;
	}
	
	find_data = AVLFind(tree, arr+2);
	
	if (*(int *)find_data != arr[2])
	{
		AddFailedTest("TestFind3\n");
		AVLDestroy(tree);
		return 1;
	}
	
	find_data = AVLFind(tree, arr+14);
	
	if (find_data)
	{
		AddFailedTest("TestFind4\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}

static int TestHeight(void)
{
	avl_t *tree = NULL;
	int arr[16] = {10, 2, 3100, 4, 50, 30, 70, 40, 60, 35, 65, 7, 8, 9, 1, 300};
	int get_height = 0;
	size_t count = 0;
	size_t loop_count = 0;
	
	/*create tree*/
	tree = AVLCreate(Compare);
	get_height = AVLHeight(tree);
	if (0 != get_height)
	{
		AddFailedTest("TestHeight1\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLInsert(tree, arr);
	get_height = AVLHeight(tree);
	if (1 != get_height)
	{
		AddFailedTest("TestHeight2\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLInsert(tree, arr+1);
	get_height = AVLHeight(tree);
	if (2 != get_height)
	{
		AddFailedTest("TestHeight3\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLInsert(tree, arr+2);
	AVLInsert(tree, arr+3);
	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestHeight4\n");
		AVLDestroy(tree);
		return 1;
	}
	
	for(loop_count = 4; loop_count < 8; ++loop_count)
	{
		AVLInsert(tree, arr+loop_count);
	}
	
	get_height = AVLHeight(tree);
	if (4 != get_height)
	{
		AddFailedTest("TestHeight5\n");
		AVLDestroy(tree);
		return 1;
	}
	
	for(; loop_count < 16; ++loop_count)
	{
		AVLInsert(tree, arr+loop_count);
	}
	
	get_height = AVLHeight(tree);
	if (5 != get_height)
	{
		AddFailedTest("TestHeight6\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLRemove(tree, arr+15);
	AVLRemove(tree, arr+14);
	AVLRemove(tree, arr+13);
	AVLRemove(tree, arr+12);
	AVLRemove(tree, arr+11);
	
	get_height = AVLHeight(tree);
	if (4 != get_height)
	{
		AddFailedTest("TestHeight7\n");
		AVLDestroy(tree);
		return 1;
	}
	
	for(loop_count = 5; loop_count < 11; ++loop_count)
	{
		AVLRemove(tree, arr+loop_count);
	}
	
	get_height = AVLHeight(tree);
	if (3 != get_height)
	{
		AddFailedTest("TestHeight8\n");
		AVLDestroy(tree);
		return 1;
	}
	
	for(loop_count = 3; loop_count < 5; ++loop_count)
	{
		AVLRemove(tree, arr+loop_count);
	}
	
	get_height = AVLHeight(tree);
	if (2 != get_height)
	{
		AddFailedTest("TestHeight9\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLRemove(tree, arr+2);
	AVLRemove(tree, arr+1);
	
	get_height = AVLHeight(tree);
	if (1 != get_height)
	{
		AddFailedTest("TestHeight10\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLRemove(tree, arr);
	
	get_height = AVLHeight(tree);
	if (0 != get_height)
	{
		AddFailedTest("TestHeight11\n");
		AVLDestroy(tree);
		return 1;
	}
	
	AVLDestroy(tree);
	return 0;
}





