#include <assert.h> /* assert */
#include <stdlib.h> /* maloc free */
#include <stdio.h> /* printf */
#include <math.h>

#include "heap.h"
#include "dvector.h"

#define FAILED -1
#define RIGHT_CHILD(position) (2 * position + 1)
#define LEFT_CHILD(position) (2 * position)
#define PARENT(position) (position % 2 == 0 ? position / 2 : (position - 1) / 2)
#define INDEX(position) (position - 1)
#define CONVERT(ptr) (*(void**)ptr)
#define START_CAPACITY 10
static dvector_t *GetDvector(const heap_t *heap);
static heap_compare_func_t GetCompare(const heap_t *heap);
static void HeapifyUp(heap_t *heap, size_t position);
static void Swap(size_t *address1, size_t *address2);
static void HeapifyDown(heap_t *heap, size_t position);
static size_t FindElement(dvector_t *dvector,
						  is_match_func_t is_match,
						  void *data);	  
/*static void PrintTreeLevel(heap_t *heap, int level, int max_width);*/
/*static int GetTreeHeight(heap_t *heap);*/
/*static void PrintTree(heap_t *heap);*/

struct heap
{
	dvector_t *dvector;
	heap_compare_func_t cmp_func;
};

/********************* API FUNCTIONS ********************/

heap_t *HeapCreate(heap_compare_func_t compare_func)
{
	heap_t *heap = NULL;
	size_t size_of_element = sizeof(size_t);
	size_t capacity = START_CAPACITY;
	
	assert(compare_func);
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if (NULL == heap)
	{
		return NULL;
	}
	
	heap->dvector =  DvectorCreate(capacity, size_of_element);
	if (NULL == heap->dvector)
	{
		free(heap);
		
		return NULL;
	}
	
	heap->cmp_func = compare_func;
	
	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);
	
	DvectorDestroy(GetDvector(heap));
	free(heap);
}

size_t HeapSize(const heap_t *heap)
{
	assert(heap);
	
	return DvectorSize(GetDvector(heap));
}

int HeapIsEmpty(const heap_t *heap)
{
	assert(heap);
	
	return (0 == HeapSize(heap));
}

int HeapPush(heap_t *heap, void *data)
{
	int status = 0;
	size_t position = 0;
	
	assert(heap);
	
	status = DvectorPushBack(GetDvector(heap), &data);
	if (0 != status)
	{
		return FAILED;
	}
	
	position = HeapSize(heap);
	
	/* only need to heapify if there are more than 1 element */
	if (1 < position)
	{
		HeapifyUp(heap, position);	
	}

	return status;	
}

void *HeapPeek(const heap_t *heap)
{
	assert(heap);
	
	return CONVERT(DvectorGetElement(GetDvector(heap), 0)	);
}

void HeapPop(heap_t *heap)
{
	dvector_t *dvector = NULL;
	size_t position_to_start = 1;
	size_t size = 0;
	
	assert(heap);
	
	dvector = GetDvector(heap);
	size = HeapSize(heap);

	/* swapping between the last and first element and then pop the last one */
	Swap(DvectorGetElement(dvector,0), DvectorGetElement(dvector, size - 1));
	DvectorPopBack(dvector);

	/* making sure to return the element we push up back to the right place */
	HeapifyDown(heap, position_to_start);
}

void *HeapRemove(heap_t *heap, is_match_func_t is_match, void *data_to_match)
{
	void *data = NULL;
	size_t index = 0;
	dvector_t *dvector = NULL;
	
	assert(heap);
	assert(is_match);
	
	dvector = GetDvector(heap);
	
	index = FindElement(dvector, is_match, data_to_match);
	if (HeapSize(heap) == index)
	{
		return NULL;
	}
	
	Swap(DvectorGetElement(dvector, HeapSize(heap) - 1), 
		 DvectorGetElement(dvector, index));
	
	data = CONVERT(DvectorGetElement(dvector, HeapSize(heap) - 1));
	
	DvectorPopBack(dvector);
	
	HeapifyDown(heap, index + 1);
	
	return data;
}
/********************* HELPER FUNCTIONS ********************/

static dvector_t *GetDvector(const heap_t *heap)
{
	assert(heap);
	
	return heap->dvector;
}

static heap_compare_func_t GetCompare(const heap_t *heap)
{
	assert(heap);
	
	return heap->cmp_func;
}

static void HeapifyUp(heap_t *heap, size_t position)
{
	size_t position_parent = PARENT(position);
	dvector_t *dvector = NULL;
	void *child = NULL;
	void *parent = NULL;
	
	assert(heap);
	
	dvector = GetDvector(heap);
	child =  DvectorGetElement(dvector, INDEX(position));
	parent =  DvectorGetElement(dvector, INDEX(PARENT(position)));
	
	
	/* while child is larger than parant AND parent isnt the root */
	while (0 < GetCompare(heap)(CONVERT(child), CONVERT(parent)) && 
		   1 < position_parent)
	{
		Swap(parent, child);
		
		position = position_parent;  
		position_parent = PARENT(position);
		
		child =  DvectorGetElement(dvector, INDEX(position));
		parent =  DvectorGetElement(dvector, INDEX(PARENT(position)));
	}
	
	/* check if its possible to swap last time between the root and the child */
	if (0 < GetCompare(heap)(CONVERT(child), CONVERT(parent)))
	{
		Swap(parent, child);
	}
}

static void HeapifyDown(heap_t *heap, size_t position)
{
	void *left_child = NULL;
	void *curr = NULL;
	
	size_t max_position = 0;
	size_t position_right = RIGHT_CHILD(position);
	size_t position_left = LEFT_CHILD(position);

	int already_swap_flag = 1;

	dvector_t *dvector = NULL;
	
	assert(heap);

	max_position = HeapSize(heap);	
	dvector = GetDvector(heap);
	curr =  DvectorGetElement(dvector, INDEX(position));
	
	/* check that left child is in range AND if we didnt swap the nodes */
	while (position_left <= max_position && already_swap_flag)
	{
		size_t start_position = position;
		left_child =  CONVERT(DvectorGetElement(dvector, INDEX(position_left)));
		already_swap_flag = 0;
		
		/* check first if right child is in range AND if its larger than curr */
		if (position_right <= max_position &&
			0 < GetCompare(heap)(CONVERT(DvectorGetElement(dvector,
												   INDEX(position_right))),
								 CONVERT(curr)))
		{
			position = position_right;
			already_swap_flag = 1;
		}
		/* 2 possible events 
		   1- right wasnt larger than current nd now we check if left is larger
		   than curr
		   2- right was larger than curr and now we chack if left is larger
		   than right to not brake the tree order */
		if (0 < GetCompare(heap)(left_child,
								 CONVERT(DvectorGetElement(dvector,
								 						   INDEX(position)))))
		{
			position = position_left;
			already_swap_flag = 1;
		}
		
		/* swapping between the correct values and go to next children */
		curr =  DvectorGetElement(dvector, INDEX(position));
		Swap(curr, DvectorGetElement(dvector, INDEX(start_position)));
		position_left = LEFT_CHILD(position);
		position_right = RIGHT_CHILD(position);
	}
}

static void Swap(size_t *address1, size_t *address2)
{
	size_t tmp = *address1;
	*address1 = *address2;
	*address2 = tmp;
}

static size_t FindElement(dvector_t *dvector,
						  is_match_func_t is_match,
						  void *data)
{
	size_t i = 0;
	size_t size = 0;
	
	assert(dvector);
	assert(is_match);
	
	size =  DvectorSize(dvector);
	
	for (; i < size; ++i)
	{
		if (is_match(CONVERT(DvectorGetElement(dvector, i)),data))
		{
			return i;
		}
	}
	
	return i;
}

/************** printing tree functions ************/
static int GetTreeHeight(heap_t *heap)
{
    size_t size = HeapSize(heap);
    return (int)ceil(log((double)(size + 1)) / log(2.0));
}

static void PrintTreeLevel(heap_t *heap, int level, int max_width)
{
    size_t size = HeapSize(heap);
    int start = (1 << level) - 1;
    int end = (1 << (level + 1)) - 1;
    int i;
    int spaces = max_width / (1 << level);
    int first_spaces = spaces / 2;

    for (i = 0; i < first_spaces; ++i)
    {
        printf("  ");
    }

    for (i = start; i < end && (size_t)i < size; ++i)
    {
        printf("%d", **(int**)(DvectorGetElement(heap->dvector, i)));
        if (i + 1 < end && (size_t)(i + 1) < size)
        {
            int j;
            for (j = 0; j < spaces; ++j)
            {
                printf("  ");
            }
        }
    }
    printf("\n");
}

static void PrintTree(heap_t *heap)
{
    int height = GetTreeHeight(heap);
    int max_width = (1 << (height - 1)) * 2;
    int level;
	
	printf("---------- tree ----------\n\n");
	
    for (level = 0; level < height; ++level)
    {
        PrintTreeLevel(heap, level, max_width);
    }
}


