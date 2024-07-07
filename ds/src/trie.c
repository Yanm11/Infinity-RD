/********************************** 
   Code by: Yan Meiri	
   Project: trie
   Date: 03/07/24
   Review by: Amit
   Review Date: 07/05/24
   Approved by: Amit
   Approval Date: 07/07/24
**********************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* maloc free */

#include "trie.h"

#define NUM_OF_CHILD 2
#define LEFT 0
#define RIGHT 1
#define INVALID_ADDRESS 0
#define FULL 1
#define EMPTY 0

typedef struct node node_t;

static node_t *GetRoot(const trie_t *trie);
static node_t *GetChild(node_t *node, size_t direction);
static node_t *GetParent(node_t *node);
static int GetIsFull(node_t *node);
static size_t GetHeight(trie_t *trie);
static node_t *CreateNode(node_t *parent);
static void PostOrderedDestroy(node_t *node);
static trie_status_e CreateRestOfAddress(node_t *node, 
									size_t bit_number,
									bitarr_t address,
									bitarr_t *out_param);
static node_t* FindNextLargerAddress(node_t *node, size_t *bit_number);
static void UpdateBranch(node_t *node);
static void UpdateNodeFull(node_t *node);
static void PreOrderedCount(node_t *node, size_t *counter);

struct node
{
	node_t *child[NUM_OF_CHILD];
	node_t *parent;
	int is_full;
	int is_leaf;
};

struct trie
{
	node_t *root;
	size_t height;	
};

/******* API FUNCTIONS ***********/

trie_t *TrieCreate(size_t height)
{
	trie_t *trie = (trie_t*)malloc(sizeof(trie_t));
	if (NULL == trie)
	{
		return NULL;
	}
	
	trie->root = CreateNode(NULL);
	if (NULL == GetRoot(trie))
	{
		free(trie);
		
		return NULL;
	}
	
	trie->height = height;
	
	return trie;
}

void TrieDestroy(trie_t *trie)
{
	assert(trie);
	
	PostOrderedDestroy(GetRoot(trie));
	
	free(trie);
}

trie_status_e TrieInsert(trie_t *trie, bitarr_t address, bitarr_t *out_param)
{
	unsigned char bit = 0;
	size_t bit_number = 0;
	node_t *node = NULL;
	trie_status_e status = TRIE_SUCCESS;
	
	assert(trie);
	assert(out_param);
	
	bit_number = GetHeight(trie);
	node = GetRoot(trie);
	/* the out param always start at 0 and later gain the right path */
	*out_param = 0;
	
	if (FULL == GetIsFull(node))
	{
		*out_param = INVALID_ADDRESS;
		
		return TRIE_FULL;
	}
	
	while (bit_number > 0)
	{
		bit = (address >> (bit_number - 1)) & 1 ;
		
		/* if the node doesnt exist yet */
		if (NULL == GetChild(node, bit))
		{
			status = CreateRestOfAddress(node, bit_number, address, out_param);
			bit_number = 0;
		}
		
		/* if the node exist */
		else
		{
			/* if node is empty */
			if (EMPTY == GetIsFull(GetChild(node, bit)))
			{
				*out_param = *out_param ^ (bit << (bit_number - 1));
				node = GetChild(node, bit);
				
				--bit_number;
			}
			/* if node is full */
			else if (FULL == GetIsFull(GetChild(node,bit)))
			{
				if (1 == bit)
				{
					node = FindNextLargerAddress(node, &bit_number);
				}
		    	/* if no available larger addres start from the begining */
				if (NULL == node)
				{
					bit_number = GetHeight(trie);
					address = 0;
					*out_param = 0;
					node = GetRoot(trie);
				}
				/* if bit was 0 we just go next to bit 1 
				   and if bit was 1 and not NULL after the function we will go
				   to the node we found and start from there */
				else
				{
					*out_param = *out_param ^ (1 << (bit_number - 1));
					address = *out_param;
					*out_param = *out_param & (~(1 << (bit_number - 1)));
					
				}
			}
		}
	}
	
	return status;
}

size_t TrieCount(const trie_t *trie)
{
	size_t count = 0;
	
	assert(trie);
	
	PreOrderedCount(GetRoot(trie), &count);
	
	return count;
}

trie_status_e TrieRemove(trie_t *trie, bitarr_t address)
{
	unsigned char bit = 0;
	size_t bit_number = 0;
	node_t *node = NULL;
	
	assert(trie);
	
	bit_number = GetHeight(trie);
	node = GetRoot(trie);
	
	while (bit_number > 0)
	{
		bit = (address >> (bit_number - 1)) & 1 ;
		
		if (NULL == GetChild(node, bit))
		{
			return TRIE_DOUBLE_FREE;
		}
		
		node = GetChild(node, bit);
		--bit_number;
	}

	node->is_full = EMPTY;
	
	UpdateBranch(node);
	
	GetParent(node)->child[bit] = NULL;
	free(node);
	
	return TRIE_SUCCESS;
}

/******* HELPER FUNCTIONS ***********/

static node_t *GetRoot(const trie_t *trie)
{
	assert(trie);
	
	return trie->root;
}

static size_t GetHeight(trie_t *trie)
{
	assert(trie);
	
	return trie->height;
}

static node_t *GetChild(node_t *node, size_t direction)
{
	assert(node);
	
	return node->child[direction];
}

static node_t *GetParent(node_t *node)
{
	assert(node);
	
	return node->parent;
}

static int GetIsFull(node_t *node)
{
	if (NULL == node)
	{
		return EMPTY;
	}
	
	return node->is_full;
}

static node_t *CreateNode(node_t *parent)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));;
	if (NULL == node)
	{
		return NULL;
	}
	
	node->child[0] = NULL;
	node->child[1] = NULL;
	node->parent = parent;
	node->is_full = EMPTY;
	node->is_leaf = 0;
	
	return node;
}

static void PostOrderedDestroy(node_t *node)
{
	if (!node)
	{
		return;
	}
	
	PostOrderedDestroy(GetChild(node, LEFT));
	PostOrderedDestroy(GetChild(node, RIGHT));
	free(node);
}

/* this function is called upon once a new path need to be created. since no 
   full node can be there we come to this function to create all the
   remaining path nececary to get to the end of the address */ 
static trie_status_e CreateRestOfAddress(node_t *node, 
							  		size_t bit_number,
							  		bitarr_t address,
							  		bitarr_t *out_param)
{
	unsigned char bit = 0;
	
	assert(node);
	assert(out_param);
		
	while (bit_number > 0)
	{
		bit = (address >> (bit_number - 1)) & 1 ;
		
		node->child[bit] = CreateNode(node);
		if (NULL == GetChild(node, bit))
		{
			*out_param = INVALID_ADDRESS;
		
			return TRIE_MEMORY_FALIURE;
		}
		/* updating the out_param with the correct path */
		*out_param = *out_param ^ (bit << (bit_number - 1));
		
		--bit_number;

		node = GetChild(node, bit);
	}
	
	node->is_full = FULL;
	node->is_leaf = 1;
	
	UpdateBranch(node);
	
	return TRIE_SUCCESS;
}

static void UpdateBranch(node_t *node)
{
	assert(node);
	
	node = GetParent(node);
	
	while (NULL != node)
	{
		if (NULL != GetChild(node,0) && NULL != GetChild(node, 1))
		{		
			UpdateNodeFull(node);
		}
		else
		{
			return;
		}
		
		node = GetParent(node);
	}
}

static void UpdateNodeFull(node_t *node)
{
	/* if both childs are full then so is the parent */
	if (FULL == GetIsFull(GetChild(node,0)) && 
		FULL == GetIsFull(GetChild(node,1)))
	{
		node->is_full = FULL;
	}
	/* if ot both childs are full then the parent is empty */
	else
	{
		node->is_full = EMPTY;
	}
}

static node_t* FindNextLargerAddress(node_t *node, size_t *bit_number)
{
	node_t *start_node = node;	
	
	assert(node);
	assert(bit_number);
	
	while (NULL != GetParent(node))
	{
		start_node = node;
		node = GetParent(node);
		++*bit_number;
		
		/* checking if a right path (larger address) exist */
		if (EMPTY == GetIsFull(GetChild(node, 1)) &&
			start_node != GetChild(node,1)) 
		{
			return node;
		}
	}
	
	return NULL;
}

static void PreOrderedCount(node_t *node, size_t *counter)
{
	if (!node)
	{
		return; 
	}
	/* only the leaf nodes at the proper height get this flag */
	if (1 == node->is_leaf)
	{
		++*counter;	
	}
	
	PreOrderedCount(GetChild(node, LEFT), counter);
	PreOrderedCount(GetChild(node, RIGHT), counter);
}





