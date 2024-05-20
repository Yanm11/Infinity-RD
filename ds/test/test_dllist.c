#include <stdio.h> /*printd*/
#include <stdlib.h> /*size_t*/

#include "dllist.h"

static int checker = 0;

void test_DllistCreate(void);
void test_BasicOperations(void);
void test_PushPop(void);

void test_DllistInsertBefore(void);
void test_DllistRemove(void);
void test_DllistFind(void);
void test_DllistForEachFind(void);
void test_DllistSplice(void);
void test_DllistMultiFind(void);

int isEqual(const void *data, void *param);
int Multipli(void *data, void *param);


int main(void) 
{
    test_DllistCreate();
    test_BasicOperations();
    test_PushPop();
    test_DllistForEachFind();
    test_DllistSplice();
    test_DllistMultiFind();

	if(checker == 0)
	{
    	printf("\nAll tests passed successfully!\n");
    }
    return 0;
}



void test_DllistCreate(void)
{
	dllist_t *list = DllistCreate();
	printf("\n----------\nTest Create start\n\n");
	if(list == NULL)
	{
		printf("DllistCreate test failed.\n");
		checker++;
	}
	printf("DllistCreate test passed.\n");
	DllistDestroy(list);
	printf("\nTest Create finished\n----------\n");
}



void test_BasicOperations(void)
{
	int arr[5] = {1,2,3,4,5};
	size_t i = 0;
	dllist_t *list = DllistCreate();
	dllist_iter_t head = DllistGetBegin(list);
	dllist_iter_t iter1 = NULL;
	dllist_iter_t iter2 = NULL;
	dllist_iter_t iter4 = NULL;
	dllist_iter_t iter5 = NULL;
	
	printf("\n----------\nTest Basic Operations start\n\n");
	
	if(1 == DllistIsEmpty(list))
	{
		printf("DllistIsEmpty test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistIsEmpty test failed.\n");
	}
	
	head = DllistInsertBefore(list, arr, head);
	if(1 == *(int *)DllistGetData(head))
	{
		printf("DllistInsertBefore test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistInsertBefore test failed.\n");
	}
	
	
	for(i = 1; i < 5; ++i)
	{
		DllistInsertBefore(list, arr+i, DllistGetEnd(list));
	}
	
	head = DllistGetBegin(list);
	for( i = 0; i < 5; ++i)
	{
		if(*(arr+i) != *(int *)DllistGetData(head))
		{
			checker++;
			printf("DllistGetData test failed.\n");
		}
		head = DllistNext(head);
	}
	
	if(0 == DllistIsEmpty(list))
	{
		printf("DllistIsEmpty test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistIsEmpty test 2 failed.\n");
	}

	if(5 == DllistSize(list))
	{
		printf("DllistSize test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistSize test failed.\n");
	}

	iter1 = DllistGetBegin(list);
	if(1 == *(int *)DllistGetData(iter1))
	{
		printf("DllistGetBegin test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistGetBegin test failed.\n");
	}
	
	iter5 = DllistGetEnd(list);
	iter4 = DllistPrev(iter5);
	if(5 == *(int *)DllistGetData(iter4))
	{
		printf("DllistGetEnd test passed.\n");
		printf("DllistPrev test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistGetEnd test failed.\n");
	}
	
	iter2 = DllistNext(iter1);
	if(2 == *(int *)DllistGetData(iter2))
	{
		printf("DllistPNext test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistGetEnd test failed.\n");
	}
	
	iter2 = DllistNext(iter2);
	iter4 = DllistPrev(iter4);
	iter4 = DllistPrev(iter4);
	if(1 == DllistIsSameIter(iter2, iter4))
	{
		printf("DllistIsSameIter test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistIsSameIter test failed.\n");
	}
	
	
	DllistRemove(DllistPrev(DllistGetEnd(list)));
	DllistRemove(DllistGetBegin(list));
	
	if(3 == DllistSize(list))
	{
		printf("DllistRemove test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistRemove test failed.\n");
	}
	
	DllistRemove(DllistGetBegin(list));
	DllistRemove(DllistGetBegin(list));
	DllistRemove(DllistGetBegin(list));
	
	if(1 == DllistIsEmpty(list))
	{
		printf("DllistIsEmpty test 3 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistIsEmpty test 3 failed.\n");
	}
	
	DllistDestroy(list);
	
	printf("\nTest Basic Operations finished\n----------\n");
}




void test_PushPop(void)
{
	dllist_t *list = DllistCreate();
	int a = 1, b = 2, c = 3, d = 4, e = 5;
	
	printf("\n----------\nTest Pop Push start\n\n");
	
	DllistPushFront(list, &a);
	if(1 == *(int *)DllistGetData(DllistGetBegin(list)))
	{
		printf("DllistPushFront test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPushFront test failed.\n");
	}
	
	DllistPushFront(list, &b);
	if(2 == *(int *)DllistGetData(DllistGetBegin(list)))
	{
		printf("DllistPushFront test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPushFront test 2 failed.\n");
	}
	
	DllistPushBack(list, &c);
	if(3 == *(int *)DllistGetData(DllistPrev(DllistGetEnd(list))))
	{
		printf("DllistPushBack test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPushBack test failed.\n");
	}
	
	DllistPushBack(list, &d);
	if(4 == *(int *)DllistGetData(DllistPrev(DllistGetEnd(list))))
	{
		printf("DllistPushBack test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPushBack test 2 failed.\n");
	}
	
	DllistPushFront(list, &e);
	if(5 == *(int *)DllistGetData(DllistGetBegin(list)))
	{
		printf("DllistPushFront test 3 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPushFront test 3 failed.\n");
	}
	
	
	
	if(5 == *(int *)DllistPopFront(list))
	{
		printf("DllistPopFront test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPopFront test failed.\n");
	}

	if(2 == *(int *)DllistPopFront(list))
	{
		printf("DllistPopFront test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPopFront test 2 failed.\n");
	}

	if(4 == *(int *)DllistPopBack(list))
	{
		printf("DllistPopBack test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPopBack test failed.\n");
	}

	if(3 == *(int *)DllistPopBack(list))
	{
		printf("DllistPopBack test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPopBack test 2 failed.\n");
	}
	
	if(1 == *(int *)DllistPopBack(list))
	{
		printf("DllistPopBack test 3 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistPopBack test 3 failed.\n");
	}
	
	if(0 != DllistSize(list))
	{
		++checker;
	}

	DllistDestroy(list);
	printf("\nTest Pop Push finished\n----------\n");
}



void test_DllistForEachFind(void)
{
	dllist_t *list = DllistCreate();
	int a = 1, b = 2, c = 3, d = 4, e = 5;
	int multi = 3;
	int to_find = 12;
	dllist_iter_t iter = NULL;
	DllistPushFront(list, &e);
	DllistPushFront(list, &d);
	DllistPushFront(list, &c);
	DllistPushFront(list, &b);
	DllistPushFront(list, &a);
	
	printf("\n----------\nTest Find and ForEach start\n\n");
	
	DllistForEach(DllistGetBegin(list), DllistGetEnd(list), Multipli, &multi);
	if(3 == *(int *)DllistGetData(DllistGetBegin(list)))
	{
		printf("DllistForEach test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistForEach test failed.\n");
	}
	
	if(15 == *(int *)DllistGetData(DllistPrev(DllistGetEnd(list))))
	{
		printf("DllistForEach test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistForEach test 2 failed.\n");
	}
	
	
	iter = DllistFind(&to_find, DllistGetBegin(list), DllistGetEnd(list), isEqual);
	if(12 == *(int *)DllistGetData(iter))
	{
		printf("DllistFind test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistFind test failed.\n");
	}
	
	DllistDestroy(list);
	printf("\nTest Find and ForEach finished\n----------\n");
}



void test_DllistSplice(void)
{
	dllist_t *list1 = DllistCreate();
	dllist_t *list2 = DllistCreate();
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7, h = 8;
	DllistPushFront(list1, &d);
	DllistPushFront(list1, &c);
	DllistPushFront(list1, &b);
	DllistPushFront(list1, &a);
	DllistPushFront(list2, &h);
	DllistPushFront(list2, &g);
	DllistPushFront(list2, &f);
	DllistPushFront(list2, &e);
	
	printf("\n----------\nTest Splice start\n\n");
	
	DllistSplice(DllistGetBegin(list1), DllistGetBegin(list2), DllistGetEnd(list2));
	
	if(5 == *(int *)DllistGetData(DllistGetBegin(list1)) && 8 == DllistSize(list1)
	 && 0 == DllistSize(list2) && 4 == *(int *)DllistGetData(DllistPrev(DllistGetEnd(list1))))
	{
		printf("DllistSplice test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistSplice test failed.\n");
	}
	
	DllistPushFront(list2, &f);
	if(6 == *(int *)DllistGetData(DllistGetBegin(list2)))
	{
		printf("DllistSplice test 2 passed.\n");
	}
	else
	{
		checker++;
		printf("DllistSplice test 2 failed.\n");
	}
	
	
	DllistDestroy(list1);
	DllistDestroy(list2);
	
	printf("\nTest Splice finished\n----------\n");
}




void test_DllistMultiFind(void)
{
	dllist_t *list = DllistCreate();
	dllist_t *output = DllistCreate();
	int a = 1, b = 2, c = 3, d = 4;
	int count = 0;
	DllistPushFront(list, &d);
	DllistPushFront(list, &c);
	DllistPushFront(list, &b);
	DllistPushFront(list, &a);
	DllistPushFront(list, &d);
	DllistPushFront(list, &c);
	DllistPushFront(list, &b);
	DllistPushFront(list, &a);
	DllistPushFront(list, &d);
	DllistPushFront(list, &c);
	DllistPushFront(list, &b);
	DllistPushFront(list, &a);
	
	printf("\n----------\nTest MultiFind start\n\n");
	
	count = DllistMultiFind(DllistGetBegin(list), DllistGetEnd(list), isEqual, &b, output);
	if(3 == count && 3 == DllistSize(output) && 2 == *(int *)DllistGetData(DllistGetBegin(output)))
	{
		printf("DllistMultiFind test passed.\n");
	}
	else
	{
		checker++;
		printf("DllistMultiFind test failed.\n");
	}

	DllistDestroy(list);
	DllistDestroy(output);
	
	printf("\nTest MultiFind finished\n----------\n");
}









int isEqual(const void *data, void *param)
{	
	return (*(int *)data == *(int *)param);
}


int Multipli(void *data, void *param)
{	
	return *(int *)data *= *(int *)param;;
}



