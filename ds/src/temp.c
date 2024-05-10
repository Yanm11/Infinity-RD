#include <stdio.h> /* printf() */
#include "sllist.h"

void TestInsertGetData(sllist_t *lst);




int isEqual(const void *data, void *param)
{	
	int a = *(int *)data;
	int b = *(int *)param;
	return (a == b);
}

int Multipli(void *data, void *param)
{	
	*(int *)data *= *(int *)param;
	return 0;
}


int main(void)
{
	sllist_t *lst = SllistCreate();
	TestInsert(lst);
	
	
	printf("All Tests Passed!\n");
	
    return 0;
}



void TestInsert(sllist_t *lst)
{
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	int get_element = 0;
	size_t count = 0;
	size_t checked_count = 0;
	iter = SllistBegin(lst);

	iter = SllistInsertBefore(lst, arr, iter);
	++checked_count;
	count = SllistCount(lst);
	get_element = *(int *)SllistGetData(iter);

	if (checked_count != count || arr[0] != get_element)
	{
		printf("Insert Test FAILED\n");
		return;
	}
	/* {1} */
	
	iter = SllistInsertBefore(lst, arr+1, iter);
	++checked_count;
	count = SllistCount(lst);
	get_element = *(int *)SllistGetData(iter);
	
	if (checked_count != count || arr[1] != get_element)
	{
		printf("Insert Test FAILED\n");
		return;
	}
	/* {2,1} */
	
	iter = SllistNext(iter);
	get_element = *(int *)SllistGetData(iter);
	
	if (arr[0] != get_element)
	{
		printf("Insert Test FAILED\n");
		return;
	}
	/* {2,1} */
	
	iter = SllistInsertBefore(lst, arr+2, iter);
	++checked_count;
	count = SllistCount(list);
	get_element = *(int *)SllistGetData(iter);
	
	if (checked_count != count || arr[2] != get_element)
	{
		printf("Insert Test FAILED\n");
		return;
	}
	/* {2,3,1} */
	
	iter = SllistEnd(lst);
	iter = SllistInsertBefore(lst, arr+3, iter);
	++checked_count;
	count = SllistCount(lst);
	get_element = *(int *)SllistGetData(iter);
	
	if (checked_count != count || arr[3] != get_element)
	{
		printf("Insert Test FAILED\n");
		return;
	}
	/* {2,3,1,4} */
	
	printf("Insert Test PASSED\n");
	printf("---------------------------\n");
	printf("GetData Test PASSED\n");
	printf("---------------------------\n");
}

int TestRemoveCount(sllist_t *lst)
{
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	int get_element = 0;
	size_t count = 4;
	size_t checked_count = 4;
	
	/* remove the second element */
	iter = SllistBegin(lst);
	iter = SllistNext(iter);
	iter = SllistRemove(iter);
	--checked_count;
	count = SllistCount(lst);
	get_element = *(int *)SllistGetData(iter);
	if (checked_count != count || arr[0] != get_element)
	{
		printf("Remove Test FAILED\n");
		return;
	}
	/* {2,1,4} */
	
	/* remove the first elem*/
	iter = SllistBegin(lst);
	iter = SllistRemove(iter);
	--checked_count;
	count = SllistCount(lst);
	get_element = *(int *)SllistGetData(iter);
	if (checked_count != count || arr[1] != get_element)
	{
		printf("Remove Test FAILED\n");
		return;
	}
	/* {1,4} */
	
	/* remove 4 */
	iter = SllistNext(iter);
	iter = SllistRemove(iter);
	--checked_count;
	count = SllistCount(lst);
	iter = SllistBegin(lst);
	get_element = *(int *)SllistGetData(iter);
	if (checked_count != count || arr[0] != get_element)
	{
		printf("Remove Test FAILED\n");
		return;
	}
	printf("Remove Test PASSED\n");
	printf("---------------------------\n");
	printf("Count Test PASSED\n");
	printf("---------------------------\n");
	
}

int TestSetData(sllist_t *lst)
{
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	int set_element = 11;
	int get_element = 0;

	/* create an iterator for the HEAD */
	iter = SllistBegin(lst);
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(lst, arr+1, iter);
	/* {2,1} */
		
	/* insert 3 before 1 */
	iter = Sllistend(iter);
	iter = SllistInsertBefore(lst, arr+2, iter);
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	iter = SllistBegin(list);
	iter = SllistSetData(iter, &set_element);
	get_element = *(int *)SllistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestSetData\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistNext(iter);
	iter = SllistSetData(iter, &set_element);
	get_element = *(int *)SllistGetData(iter);
	
	if (10 != get_element)
	{
		AddFailedTest("TestSetData\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistNext(iter);
	iter = SllistSetData(iter, &set_element);
	get_element = *(int *)SllistGetData(iter);
	if (10 != get_element)
	{
		AddFailedTest("TestSetData\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestForEach()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	sllist_iter_t end = NULL;
	int arr[4] = {1, 2, 3, 4};
	int status = 0;
	int get_element = 0;
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);

	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(list, arr+1, iter);
	/* HEAD -> 2 -> 1 -> TAIL */
		
	/* insert 3 before 1 */
	iter = SllistNext(iter);
	iter = SllistInsertBefore(list, arr+2, iter);
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	iter = SllistBegin(list);
	end = SllistEnd(list);
	status = SllistForEach(iter, end, Multipli, arr+3);
	
	iter = SllistBegin(list);
	get_element = *(int *)SllistGetData(iter);
	if (status || 8 != get_element)
	{
		AddFailedTest("TestForEach\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistNext(iter);
	get_element = *(int *)SllistGetData(iter);
	if (12 != get_element)
	{
		AddFailedTest("TestForEach\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistNext(iter);
	get_element = *(int *)SllistGetData(iter);
	if (4 != get_element)
	{
		AddFailedTest("TestForEach\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestCount()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	size_t count = 0;
	

	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);
	
	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	count = SllistCount(list);
	if (1 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(list, arr+1, iter);
	count = SllistCount(list);
	if (2 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	/* HEAD -> 2 -> 1 -> TAIL */
		
	/* insert 3 before 1 */
	iter = SllistNext(iter);
	iter = SllistInsertBefore(list, arr+2, iter);
	count = SllistCount(list);
	if (3 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	/* remove 1 */
	iter = SllistBegin(list);
	iter = SllistNext(iter);
	iter = SllistNext(iter);
	iter = SllistRemove(iter);
	count = SllistCount(list);
	if (2 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	/* HEAD -> 2 -> 3 -> TAIL */
	
	/* remove 2 */
	iter = SllistBegin(list);
	iter = SllistRemove(iter);
	count = SllistCount(list);
	if (1 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	/* HEAD -> 3 -> TAIL */
	
	/* remove 3 */
	iter = SllistBegin(list);
	iter = SllistRemove(iter);
	count = SllistCount(list);
	if (0 != count)
	{
		AddFailedTest("TestCount\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestBegin()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	int get_element = 0;
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);

	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(list, arr+1, iter);
	/* HEAD -> 2 -> 1 -> TAIL */
		
	/* insert 3 before 1 */
	iter = SllistNext(iter);
	iter = SllistInsertBefore(list, arr+2, iter);
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	iter = SllistBegin(list);
	get_element = *(int *)SllistGetData(iter);
	if (2 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SllistDestroy(list);
		return 1;
	}
	
	/* remove 2 */
	iter = SllistRemove(iter);
	/* HEAD -> 3 -> 1 -> TAIL */
	iter = SllistBegin(list);
	get_element = *(int *)SllistGetData(iter);
	if (3 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SllistDestroy(list);
		return 1;
	}
	/* remove 3 */
	iter = SllistRemove(iter);
	/* HEAD -> 1 -> TAIL */
	iter = SllistBegin(list);
	get_element = *(int *)SllistGetData(iter);
	if (1 != get_element)
	{
		AddFailedTest("TestBegin\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestNext()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	int get_element = 0;
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);

	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(list, arr+1, iter);
	/* HEAD -> 2 -> 1 -> TAIL */
		
	/* insert 3 before 1 */
	iter = SllistNext(iter);
	iter = SllistInsertBefore(list, arr+2, iter);
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	iter = SllistBegin(list);
	iter = SllistNext(iter);
	get_element = *(int *)SllistGetData(iter);
	if (3 != get_element)
	{
		AddFailedTest("TestNext\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistNext(iter);
	get_element = *(int *)SllistGetData(iter);
	if (1 != get_element)
	{
		AddFailedTest("TestNext\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestIsEmpty()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	int arr[4] = {1, 2, 3, 4};
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);
	
	if(!SllistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty1\n");
		SllistDestroy(list);
		return 1;
	}
	
	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	/* HEAD -> 1 -> TAIL */
	
	if(SllistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty2\n");
		SllistDestroy(list);
		return 1;
	}
	
	iter = SllistRemove(iter);
	
	if(!SllistIsEmpty(list))
	{
		AddFailedTest("TestIsEmpty3\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

int TestFind()
{
	sllist_t *list = NULL;
	sllist_iter_t iter = NULL;
	sllist_iter_t end = NULL;
	int arr[4] = {1, 2, 3, 4};
	int get_element = 0;
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter = SllistBegin(list);

	/* insert 1 */
	iter = SllistInsertBefore(list, arr, iter);
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter = SllistInsertBefore(list, arr+1, iter);
	/* HEAD -> 2 -> 1 -> TAIL */
		
	/* insert 3 before 1 */
	iter = SllistNext(iter);
	iter = SllistInsertBefore(list, arr+2, iter);
	/* HEAD -> 2 -> 3 -> 1 -> TAIL */
	
	iter = SllistBegin(list);
	end = SllistEnd(list);
	iter =  SllistFind(arr, iter, end, isEqual);
	get_element = *(int *)SllistGetData(iter);
	if (1 != get_element)
	{
		AddFailedTest("TestFind\n");
		SllistDestroy(list);
		return 1;
	}
	iter = SllistRemove(iter);
	
	iter = SllistBegin(list);
	end = SllistEnd(list);
	iter =  SllistFind(arr+2, iter, end, isEqual);
	get_element = *(int *)SllistGetData(iter);
	if (3 != get_element)
	{
		AddFailedTest("TestFind\n");
		SllistDestroy(list);
		return 1;
	}

	SllistDestroy(list);
	return 0;
}

int TestIsEqual()
{
	sllist_t *list = NULL;
	sllist_iter_t iter1 = NULL;
	sllist_iter_t iter2 = NULL;
	int arr[4] = {1, 2, 3, 4};
	
	/* create linked list */
	list = SllistCreate();

	/* create an iterator for the HEAD */
	iter1 = SllistBegin(list);

	/* insert 1 */
	iter1 = SllistInsertBefore(list, arr, iter1);
	/* HEAD -> 1 -> TAIL */
	
	/* insert 2 before 1 */
	iter1 = SllistInsertBefore(list, arr+1, iter1);
	/* HEAD -> 2 -> 1 -> TAIL */
	
	iter2 = SllistBegin(list);
	iter1 = SllistBegin(list);
	
	if (!SllistIterIsEqual(iter1, iter2))
	{
		AddFailedTest("TestIsEqual\n");
		SllistDestroy(list);
		return 1;
	}
	
	iter1 = SllistNext(iter1);
	
	if (SllistIterIsEqual(iter1, iter2))
	{
		AddFailedTest("TestIsEqual\n");
		SllistDestroy(list);
		return 1;
	}
	
	iter2 = SllistNext(iter2);
	
	if (!SllistIterIsEqual(iter1, iter2))
	{
		AddFailedTest("TestIsEqual\n");
		SllistDestroy(list);
		return 1;
	}
	
	SllistDestroy(list);
	return 0;
}

void AddFailedTest(const char *str)
{
	strcat(failed_tests_print, str);
}





































