#include <stdio.h> /* printf */
#include <assert.h> /* assert */
	
#include "avl.h"
void TestCreateDestroy(void);
void TestCount(void);
void TestIsEmpty(void);
void TestInsert(void);

static int checker = 0;

int Compare(const void *data,const void *params)
{	
	assert(data);
	assert(params);
	
	return (*(int *)data - *(int *)params);
}

int Sum(void *data, void *params)
{	
	*(int *)params += *(int *)data;
	return (*(int *)params);
}

int main(void)
{
	TestCreateDestroy();
	TestCount();
	TestIsEmpty();
	TestInsert();
	
	if (checker)
	{
		printf("In Total Failed %d Tests\n", checker);
		return 0;
	}
	
	printf("PASSED ALL TESTS!!!!!\n");
	
	return 0;
}

void TestCreateDestroy(void)
{
	avl_t *avl = AVLCreate(&Compare);
	if (NULL == avl)
	{
		printf("FAILED TestCreateDestroy\n");
		++checker;
		
		return;
	}
	
	AVLDestroy(avl);
	
	printf("PASSED TestCreateDestroy!!\n");
}

void TestCount(void)
{
	size_t size = 0;
	avl_t *avl = AVLCreate(&Compare);
	
	size = AVLCount(avl);
	
	if (0 != size)
	{
		printf("FAILED TestCount\n");
		++checker;
		
		return;
	}
	
	AVLDestroy(avl);
	
	printf("PASSED TestCount!!\n");
}

void TestIsEmpty(void)
{
	avl_t *avl = AVLCreate(&Compare);
	
	if (!AVLIsEmpty(avl))
	{
		printf("FAILED TestIsEmpty\n");
		++checker;
		
		return;
	}
	
	AVLDestroy(avl);
	
	printf("PASSED TestIsEmpty!!\n");
}

void TestInsert(void)
{
	size_t size_avl = 0;
	avl_t *avl = AVLCreate(&Compare);
	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};
	size_t i = 3;
	size_t size_arr = sizeof(arr) / sizeof(int);
	
	/* insert 20 */
	AVLInsert(avl, arr);
	
	size_avl = AVLCount(avl);
	
	if (1 != size_avl)
	{
		printf("FAILED TestInsert\n");
		++checker;
		
		return;
	}
	
	/* insert 15 */
	AVLInsert(avl, arr + 1);
	
	/* insert 30 */
	AVLInsert(avl, arr + 2);
	
	size_avl = AVLCount(avl);
	
	if (3 != size_avl)
	{
		printf("FAILED TestInsert\n");
		++checker;
		
		return;
	}
	
	for (; i < size_arr; ++i)
	{
		AVLInsert(avl, arr + i);
	}
	
	size_avl = AVLCount(avl);
	
	if (size_avl != size_arr)
	{
		printf("FAILED TestInsert\n");
		++checker;
		
		return;
	}
	
	AVLDestroy(avl);
	
	printf("PASSED TestInsert!!\n");
}
