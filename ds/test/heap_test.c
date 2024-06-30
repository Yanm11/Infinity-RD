#include <stdio.h> /* printf */
#include <assert.h> /* assert */
	
#include "heap.h"
void TestCreateDestroy(void);
void TestSize(void);
void TestIsEmpty(void);
void TestPush(void);
/*void TestFind(void);*/
/*void TestForEach(void);*/
/*void TestRemove(void);*/

static int checker = 0;

int Compare(const void *data,const void *params)
{	
	assert(data);
	assert(params);
	
	return (*(int *)data - *(int *)params);
}

int is_match(void *data1, void *data2)
{	
	assert(data1);
	assert(data2);
	
	return *(int*)data1 == *(int*)data2;
}

int main(void)
{
	TestCreateDestroy();
	TestSize();
	TestIsEmpty();
	TestPush();
/*	TestFind();*/
/*	TestForEach();*/
/*	TestRemove();*/
	
	if (checker)
	{
		printf("In Total Failed %d Tests\n", checker);
		return 0;
	}
	
	printf("\nPASSED ALL TESTS!!!!!\n");
	
	return 0;
}

void TestCreateDestroy(void)
{
	heap_t *heap = HeapCreate(&Compare);
	if (NULL == heap)
	{
		printf("FAILED TestCreateDestroy\n");
		++checker;
		
		return;
	}
	
	HeapDestroy(heap);
	
	printf("PASSED TestCreateDestroy!!\n");
}

void TestSize(void)
{
	size_t size = 0;
	heap_t *heap = HeapCreate(&Compare);
	
	size = HeapSize(heap);
	
	if (0 != size)
	{
		printf("FAILED TestSize\n");
		++checker;
		
		return;
	}
	
	HeapDestroy(heap);
	
	printf("PASSED TestSize!!\n");
}

void TestIsEmpty(void)
{
	heap_t *heap = HeapCreate(&Compare);
	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};
	size_t i = 0;
	size_t size_arr = sizeof(arr) / sizeof(int);
	
	if (!HeapIsEmpty(heap))
	{
		printf("FAILED TestIsEmpty\n");
		++checker;
		
		return;
	}

/*	for (; i < size_arr; ++i)*/
/*	{*/
/*		AVLInsert(avl, arr + i);*/
/*	}*/
/*	*/
/*	if (AVLIsEmpty(avl))*/
/*	{*/
/*		printf("FAILED TestIsEmpty2\n");*/
/*		++checker;*/
/*		*/
/*		return;*/
/*	}*/
/*	*/
	HeapDestroy(heap);
	
	printf("PASSED TestIsEmpty!!\n");
}

void TestPush(void)
{
	size_t size_heap = 0;
	heap_t *heap = HeapCreate(&Compare);
	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};
	size_t i = 3;
	size_t size_arr = sizeof(arr) / sizeof(int);
	
	/* insert 20 */
	HeapPush(heap, arr);
	
	size_heap = HeapSize(heap);
	
	if (1 != size_heap)
	{
		printf("FAILED TestPush\n");
		++checker;
		
		return;
	}
	
	/* insert 15 */
	HeapPush(heap, arr + 1);
	
	/* insert 30 */
	HeapPush(heap, arr + 2);
	
	size_heap = HeapSize(heap);
	
	if (3 != size_heap)
	{
		printf("FAILED TestPush2\n");
		++checker;
		
		return;
	}
	
	if (arr[2] != *(int*)HeapPeek(heap))
	{
		printf("FAILED TestPush3\n");
		++checker;
		
		return;
	}
	
	for (; i < size_arr; ++i)
	{
		HeapPush(heap, arr + i);
	}
	
	size_heap = HeapSize(heap);
	
	if (size_heap != size_arr)
	{
		printf("FAILED TestPush4\n");
		++checker;
		
		return;
	}
	
	HeapDestroy(heap);
	
	printf("PASSED TestPush!!\n");
}

/*void TestFind(void)*/
/*{*/
/*	avl_t *avl = AVLCreate(&Compare);*/
/*	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};*/
/*	size_t i = 0;*/
/*	size_t size_arr = sizeof(arr) / sizeof(int);*/
/*	int elem_not_in_avl = 100;*/
/*	*/
/*	for (; i < size_arr; ++i)*/
/*	{*/
/*		AVLInsert(avl, arr + i);*/
/*	}*/
/*	*/
/*	for (i = 0; i < size_arr; ++i)*/
/*	{*/
/*		if (arr[i] != *(int*)AVLFind(avl, arr + i))*/
/*		{*/
/*			printf("FAILED TestFind\n");*/
/*			++checker;*/
/*			*/
/*			return;*/
/*		}*/
/*	}*/
/*	*/
/*	if (NULL != AVLFind(avl, &elem_not_in_avl))*/
/*	{*/
/*		printf("FAILED TestFind2\n");*/
/*		++checker;*/
/*		*/
/*		return;*/
/*	}*/
/*	*/
/*	AVLDestroy(avl);*/
/*	*/
/*	printf("PASSED TestFind!!\n");*/
/*}*/

/*void TestForEach(void)*/
/*{*/
/*	avl_t *avl = AVLCreate(&Compare);*/
/*	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};*/
/*	size_t i = 0;*/
/*	size_t size_arr = sizeof(arr) / sizeof(int);*/
/*	int params = 100;*/
/*	*/
/*	for (; i < size_arr; ++i)*/
/*	{*/
/*		AVLInsert(avl, arr + i);*/
/*	}*/
/*	*/
/*	printf("Test ForEach:(should print elements in accending order)\n[");*/
/*	if (0 != AVLForEach(avl, &PrintElements, &params))*/
/*	{*/
/*		printf("FAILED TestForEach\n");*/
/*		++checker;*/
/*		*/
/*		return;*/
/*	}*/
/*	printf("]\n");*/
/*	*/
/*	AVLDestroy(avl);*/
/*	*/
/*	printf("PASSED TestForEach!!\n");*/
/*}*/

/*void TestRemove(void)*/
/*{*/
/*	avl_t *avl = AVLCreate(&Compare);*/
/*	int arr[] = {20, 15, 30, 10, 5, 12, 7, 6, 25, 35, 40, 37, 39, 11};*/
/*	size_t i = 0;*/
/*	size_t size_arr = sizeof(arr) / sizeof(int);*/
/*	*/
/*	for (; i < size_arr; ++i)*/
/*	{*/
/*		AVLInsert(avl, arr + i);*/
/*	}*/
/*	*/
/*	for (i = 0; i < size_arr; ++i)*/
/*	{*/
/*		AVLRemove(avl, arr + i);*/
/*	}*/
/*	*/
/*	if (0 != AVLCount(avl))*/
/*	{*/
/*		printf("FAILED TestRemove\n");*/
/*		++checker;*/
/*		*/
/*		return;*/
/*	}*/
/*	*/
/*	printf("PASSED TestRemove!!\n");*/
/*}*/
