#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hpq.h"

int compare_func(const void *a, const void *b) 
{
    return *(int *)b - *(int *)a;
}

int match_func(const void *a, const void *b) 
{
    return *(int *)a == *(int *)b;
}

void run_tests() 
{
    hpq_t *pq;
    int data1 = 5;
    int data2 = 10;
    int data3 = 1;
    int result;
    void *dequeued_data;
    void *peeked_data;
    size_t size;
    int is_empty;
    void *erased_data;

    pq = HPQCreate(compare_func);
    if (pq == NULL) 
    {
        printf("Test 1 failed\n");
        return;
    }

    result = HPQEnqueue(pq, &data1);
    if (result != 0) 
    {
        printf("Test 2 failed\n");
    }

    result = HPQEnqueue(pq, &data2);
    if (result != 0) 
    {
        printf("Test 3 failed\n");
    }

    result = HPQEnqueue(pq, &data3);
    if (result != 0) 
    {
        printf("Test 4 failed\n");
    }

    dequeued_data = HPQDequeue(pq);
    if (*(int *)dequeued_data != data3) 
    {
        printf("Test 5 failed\n");
    }

    peeked_data = HPQPeek(pq);
    if (*(int *)peeked_data != data1) 
    {
        printf("Test 6 failed\n");
    }

    is_empty = HPQIsEmpty(pq);
    if (is_empty != 0) 
    {
        printf("Test 7 failed\n");
    }

    size = HPQSize(pq);
    if (size != 2) 
    {
        printf("Test 8 failed\n");
    }

    HPQClear(pq);
    size = HPQSize(pq);
    if (size != 0) 
    {
        printf("Test 9 failed\n");
    }

    result = HPQEnqueue(pq, &data1);
    if (result != 0) 
    {
        printf("Test 10 failed\n");
    }

    erased_data = HPQErase(pq, match_func, &data1);
    if (*(int *)erased_data != data1) 
    {
        printf("Test 11 failed\n");
    }

    is_empty = HPQIsEmpty(pq);
    if (is_empty != 1) 
    {
        printf("Test 12 failed\n");
    }

    HPQDestroy(pq);

    printf("All tests passed\n");
}

int main() 
{
    run_tests();
    return 0;
}
