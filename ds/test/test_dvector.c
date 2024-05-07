#include <stdio.h> /*printf */
#include "dvector.h"


void test_DvectorCreate(void);
void test_DvectorPushBack(void);
void test_DvectorPopBack(void);
void test_DvectorShrink(void);
void test_DvectorReserve(void);
void test_DvectorSize(void);
void test_DvectorCapacity(void);
void test_DvectorGetElement(void);

int main(void) {
    test_DvectorCreate();
    test_DvectorPushBack();
    test_DvectorPopBack();
    test_DvectorShrink();
    test_DvectorReserve();
    test_DvectorSize();
    test_DvectorCapacity();
    test_DvectorGetElement();

    return 0;
}

void test_DvectorCreate(void) 
{
	dvector_t *vector = DvectorCreate(5, sizeof(int));
	if (vector != NULL) 
	{
		printf("DvectorCreate test passed\n");
	}
	else 
	{
		printf("DvectorCreate test failed\n");
	}
	DvectorDestroy(vector);
}

void test_DvectorPushBack(void) 
{
	dvector_t *vector = DvectorCreate(2, sizeof(int));
	int element = 10;
	if (DvectorPushBack(vector, &element) == 0 && *((int *)DvectorGetElement(vector, 0)) == 10) 
	{
		printf("DvectorPushBack test passed\n");
	} 
	else 
	{
		printf("DvectorPushBack test failed\n");
	}
	DvectorDestroy(vector);
}

void test_DvectorPopBack(void) 
{
	dvector_t *vector = DvectorCreate(2, sizeof(int));
	int element = 10;
	DvectorPushBack(vector, &element);
	DvectorPopBack(vector);
    if (DvectorSize(vector) == 0) 
    {
		printf("DvectorPopBack test passed\n");
	}
	else 
	{
		printf("DvectorPopBack test failed\n");
	}
	DvectorDestroy(vector);
}

void test_DvectorShrink(void) 
{
	dvector_t *vector = DvectorCreate(5, sizeof(int));
	int elements[5] = {1, 2, 3, 4, 5};
	int i;
	for (i = 0; i < 5; i++) 
	{
		DvectorPushBack(vector, &elements[i]);
    }
	DvectorPopBack(vector);
    if (DvectorShrink(vector) == 0 && DvectorCapacity(vector) == 4) 
    {
		printf("DvectorShrink test passed\n");
	} else 
	{
		printf("DvectorShrink test failed\n");
	}
	DvectorDestroy(vector);
}


void test_DvectorReserve(void) 
{
	dvector_t *vector = DvectorCreate(5, sizeof(int));
	if (DvectorReserve(vector, 10) == 0 && DvectorCapacity(vector) == 10) 
	{
		printf("DvectorReserve test passed\n");
	} 
	else 
	{
		printf("DvectorReserve test failed\n");
	}
	DvectorDestroy(vector);
}

void test_DvectorSize(void) {
    dvector_t *vector = DvectorCreate(5, sizeof(int));
    if (DvectorSize(vector) == 0) {
        printf("DvectorSize test passed\n");
    } else {
        printf("DvectorSize test failed\n");
    }
    DvectorDestroy(vector);
}

void test_DvectorCapacity(void) 
{
	dvector_t *vector = DvectorCreate(5, sizeof(int));
	if (DvectorCapacity(vector) == 5) 
	{
		printf("DvectorCapacity test passed\n");
	} 
	else 
	{
		printf("DvectorCapacity test failed\n");
	}
	DvectorDestroy(vector);
}

void test_DvectorGetElement(void) 
{
	dvector_t *vector = DvectorCreate(5, sizeof(int));
    int element = 10;
	DvectorPushBack(vector, &element);
	if (*((int *)DvectorGetElement(vector, 0)) == 10) 
	{
		printf("DvectorGetElement test passed\n");
	} 
	else 
	{
		printf("DvectorGetElement test failed\n");
	}
	DvectorDestroy(vector);
}

