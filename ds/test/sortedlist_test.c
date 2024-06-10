#include <stdio.h> /* printf */

#include "sortedlist.h"


void TestSortedList();
static int CompareInt(const void *data1, const void *data2);
static int IsMatch(const void *data, const void *param);
static int PrintInt(void *data, void *param);

int main(void)
{
    TestSortedList();
    return 0;
}



static int CompareInt(const void *data1, const void *data2)
{
    return (*(int *)data1 - *(int *)data2);
}

static int IsMatch(const void *data, const void *param)
{
    return (*(int *)data == *(int *)param);
}

static int PrintInt(void *data, void *param)
{
	(void)param;
    printf("%d ", *(int *)data);
    return 0;
}

void TestSortedList()
{
    sortedlist_t *list = SortedlistCreate(CompareInt);
    sortedlist_t *list2 = NULL;
    sortedlist_iter_t iter;
    sortedlist_iter_t end;
    int data[] = {5, 1, 3, 4, 2};
    int size;
    int *popped_data;
    sortedlist_iter_t found_iter;
    int i;
    int checker = 0;

    /* Test SortedlistCreate and SortedlistIsEmpty */
    if (list && SortedlistIsEmpty(list))
    {
        printf("Test SortedlistCreate and SortedlistIsEmpty passed\n");
    }
    else
    {
        printf("Test SortedlistCreate and SortedlistIsEmpty failed\n");
        ++checker;
    }

    /* Test SortedlistInsert and SortedlistSize */
    for (i = 0; i < 5; ++i)
    {
        SortedlistInsert(list, &data[i]);
    }

    size = SortedlistSize(list);
    if (size == 5)
    {
        printf("Test SortedlistInsert and SortedlistSize passed\n");
    }
    else
    {
        printf("Test SortedlistInsert and SortedlistSize failed\n");
        ++checker;
    }

    /* Test SortedlistGetBegin and SortedlistGetEnd */
    iter = SortedlistGetBegin(list);
    end = SortedlistGetEnd(list);
    if (!SortedlistIsSameIter(iter, end))
    {
        printf("Test SortedlistGetBegin and SortedlistGetEnd passed\n");
    }
    else
    {
        printf("Test SortedlistGetBegin and SortedlistGetEnd failed\n");
        ++checker;
    }

    /* Test SortedlistNext and SortedlistPrev */
    iter = SortedlistNext(iter);
    if (*(int *)SortedlistGetData(iter) == 2)
    {
        printf("Test SortedlistNext passed\n");
    }
    else
    {
        printf("Test SortedlistNext failed\n");
        ++checker;
    }

    iter = SortedlistPrev(iter);
    if (*(int *)SortedlistGetData(iter) == 1)
    {
        printf("Test SortedlistPrev passed\n");
    }
    else
    {
        printf("Test SortedlistPrev failed\n");
        ++checker;
    }

    /* Test SortedlistFind */
    iter = SortedlistGetBegin(list);
    found_iter = SortedlistFind(list, iter, end, &data[2]);
    if (*(int *)SortedlistGetData(found_iter) == 3)
    {
        printf("Test SortedlistFind passed\n");
    }
    else
    {
        printf("Test SortedlistFind failed\n");
        ++checker;
    }

    /* Test SortedlistFindIf */
    found_iter = SortedlistFindIf(iter, end, IsMatch, &data[3]);
    if (*(int *)SortedlistGetData(found_iter) == 4)
    {
        printf("Test SortedlistFindIf passed\n");
    }
    else
    {
        printf("Test SortedlistFindIf failed\n");
        ++checker;
    }

    /* Test SortedlistIsSameIter */
    iter = SortedlistNext(iter);
    if (SortedlistIsSameIter(iter, SortedlistPrev(SortedlistNext(iter))))
    {
        printf("Test SortedlistIsSameIter passed\n");
    }
    else
    {
        printf("Test SortedlistIsSameIter failed\n");
        ++checker;
    }

    /* Test SortedlistRemove */
    iter = SortedlistGetBegin(list);
    iter = SortedlistRemove(iter);
    if (*(int *)SortedlistGetData(iter) == 2)
    {
        printf("Test SortedlistRemove passed\n");
    }
    else
    {
        printf("Test SortedlistRemove failed\n");
        ++checker;
    }

    /* Test SortedlistPopFront */
    popped_data = (int *)SortedlistPopFront(list);
    if (*popped_data == 2)
    {
        printf("Test SortedlistPopFront passed\n");
    }
    else
    {
        printf("Test SortedlistPopFront failed\n");
        ++checker;
    }

    /* Test SortedlistPopBack */
    popped_data = (int *)SortedlistPopBack(list);
    if (*popped_data == 5)
    {
        printf("Test SortedlistPopBack passed\n");
    }
    else
    {
        printf("Test SortedlistPopBack failed\n");
        ++checker;
    }

    /* Test SortedlistMerge */
    list2 = SortedlistCreate(CompareInt);
    for (i = 0; i < 5; ++i)
    {
        SortedlistInsert(list2, &data[i]);
    }
    
    SortedlistMerge(list, list2);
    
    if (SortedlistSize(list) == 7)
    {
        printf("Test SortedlistMerge passed\n");
    }
    else
    {
        printf("Test SortedlistMerge failed\n");
        ++checker;
    }

    /* Test SortedlistForEach */
    iter = SortedlistGetBegin(list);
    printf("SortedlistForEach elements: ");
    SortedlistForEach(iter, end, PrintInt, &i);
    printf("\n");

    /* Test SortedlistDestroy */
    SortedlistDestroy(list);
    SortedlistDestroy(list2);
    printf("Test SortedlistDestroy passed\n");
    
    if (0 == checker)
    {
    	printf("PASSED ALL TESTS!!!!!!! \n");
    }
    else
    {
    	printf("FAILED %d TESTS\n", checker);
    }
}



