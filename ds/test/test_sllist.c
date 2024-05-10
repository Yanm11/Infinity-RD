#include "sllist.h"
#include <stdio.h> /* printf */
#include <assert.h> /* assert */

/* Function to match data in the linked list */
int MatchInt(const void *data, void *param) 
{
    return *(int *)data == *(int *)param;
}

void TestCreateDestroy() 
{
    sllist_t *list = SllistCreate();
    assert(list != NULL);
    SllistDestroy(list);
}

void TestInsertRemove() 
{
    sllist_t *list = SllistCreate();
    int data1 = 10, data2 = 20;
    sllist_iter_t iter;

    iter = SllistInsertBefore(list, &data1, SllistEnd(list));
    assert(SllistGetData(iter) == &data1);

    iter = SllistInsertBefore(list, &data2, iter);
    assert(SllistGetData(iter) == &data2);
    assert(SllistCount(list) == 2);
    
    iter = SllistRemove(iter);
    assert(SllistGetData(iter) == &data1);
    
    iter = SllistRemove(iter);
    assert(SllistCount(list) == 0);

    SllistDestroy(list);
}

void TestFindSetData() 
{
    sllist_t *list = SllistCreate();
    int data1 = 10, data2 = 20, not_found = 30;
    sllist_iter_t iter1, iter2, found;

    iter1 = SllistInsertBefore(list, &data1, SllistEnd(list));
    assert(SllistGetData(iter1) == &data1); 

    iter2 = SllistInsertBefore(list, &data2, SllistEnd(list));
    assert(SllistGetData(iter2) == &data2); 

    found = SllistFind(&data2, SllistBegin(list), SllistEnd(list), MatchInt);
    assert(found != SllistEnd(list) && SllistGetData(found) == &data2);

    SllistSetData(iter1, &not_found);
    assert(*(int *)SllistGetData(iter1) == not_found);

    SllistDestroy(list);
}


void TestIsEmpty() 
{
    sllist_t *list = SllistCreate();
    int data;

    assert(SllistIsEmpty(list));
    
    data = 10;
    SllistInsertBefore(list, &data, SllistEnd(list));
    assert(!SllistIsEmpty(list));

    SllistDestroy(list);
}

/* Action function for SllistForEach test */
int IncrementData(void *data, void *param) 
{
    *(int*)data += *(int*)param;
    return 0; 
}

void TestIterativeNavigation() 
{
    sllist_t *list = SllistCreate();
    int data[] = {10, 20, 30};
    sllist_iter_t iter;
    int i, n;

   
    n = sizeof(data) / sizeof(data[0]);
    for (i = 0; i < n; i++) {
        SllistInsertBefore(list, &data[i], SllistEnd(list));
    }

    
    iter = SllistBegin(list);
    for (i = 0; i < n; i++) {
        assert(*(int *)SllistGetData(iter) == data[i]);
        iter = SllistNext(iter);
    }
    assert(SllistIterIsEqual(iter, SllistEnd(list))); 

    SllistDestroy(list);
}

void TestIterIsEqual() 
{
    sllist_t *list = SllistCreate();
    int data = 10;
    sllist_iter_t iter1, iter2;

    iter1 = SllistInsertBefore(list, &data, SllistEnd(list));
    iter2 = SllistNext(SllistBegin(list));

    assert(SllistIterIsEqual(iter1, iter2) == 0); 
    assert(SllistIterIsEqual(SllistEnd(list), SllistEnd(list))); 

    SllistDestroy(list);
}

void TestForEach() 
{
    sllist_t *list = SllistCreate();
    int data[] = {1, 2, 3};
    int increment = 1, i, n;
    sllist_iter_t iter;

   
    n = sizeof(data) / sizeof(data[0]);
    for (i = 0; i < n; i++)
    {
        SllistInsertBefore(list, &data[i], SllistEnd(list));
    }

   
    SllistForEach(SllistBegin(list), SllistEnd(list), IncrementData, &increment);

  
    iter = SllistBegin(list);
    for (i = 0; i < n; i++, iter = SllistNext(iter))
    {
    	int data2[] = {1, 2, 3};
        int expected = data2[i] + 1;
        int actual = *(int *)SllistGetData(iter);
        if (actual != expected)
        {
            printf("Failed at index %d: expected %d, got %d\n", i, expected, actual);
        }
        assert(actual == expected);
    }

    SllistDestroy(list);
}


void TestAll() 
{
    /* Call all test functions */
    TestCreateDestroy();
    TestInsertRemove();
    TestFindSetData();
    TestIsEmpty();
    TestIterativeNavigation();
    TestIterIsEqual();
    TestForEach();
    printf("All tests passed.\n");
}

int main(void) 
{
    TestAll();
    return 0;
}



