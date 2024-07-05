#include <assert.h> /* assert */
#include <stdlib.h> /* maloc free */

#include "trie.h"

#define SIZE 2
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
static size_t GetHight(trie_t *trie);
static node_t *CreateNode(node_t *paraent);
static void PostOrderedDestroy(node_t *node);
static trie_status_e CreateRestOfAddress(node_t *node, 
									size_t bit_number,
									bitarr_t address,
									bitarr_t *out_param);
static node_t* FindNextLargerAddress(node_t *node, size_t *bit_number);
static void UpdateBranch(node_t *node);
static void PreOrderedCount(node_t *node, size_t *counter);

struct node
{
	node_t *child[SIZE];
	node_t *paraent;
	int is_full;
	int is_leaf;
};

struct trie
{
	node_t *root;
	size_t hight;	
};

/******* API FUNCTIONS ***********/

trie_t *TrieCreate(size_t hight)
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
	
	trie->hight = hight;
	
	return trie;
}

void TrieDestroy(trie_t *trie)
{
	assert(trie);
	
	PostOrderedDestroy(GetRoot(trie));
	
	free(trie);
}

int TrieIsFull(const trie_t *trie)
{
	node_t *root = NULL;
	
	assert(trie);
	
	root = GetRoot(trie);
	
	return (NULL == GetChild(root, LEFT) && NULL == GetChild(root, RIGHT));
}

trie_status_e TrieInsert(trie_t *trie, bitarr_t address, bitarr_t *out_param)
{
	unsigned char bit = 0;
	size_t bit_number = 0;
	node_t *node = NULL;
	trie_status_e status = SUCCESS;
	
	assert(trie);
	assert(out_param);
	
	bit_number = GetHight(trie);
	node = GetRoot(trie);
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
					/* if no available larger addres start from the begining */
					if (NULL == node)
					{
						bit_number = GetHight(trie);
						address = 0;
						*out_param = 0;
						node = GetRoot(trie);
					}
					else
					{
						*out_param = *out_param ^ (1 << (bit_number - 1));
						address = *out_param;
						*out_param = *out_param & (~(1 << (bit_number - 1)));
					}
				}
				else
				{
					bit = 1;

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
	
	bit_number = GetHight(trie);
	node = GetRoot(trie);
	
	while (bit_number > 0)
	{
		bit = (address >> (bit_number - 1)) & 1 ;
		
		if (NULL == GetChild(node, bit))
		{
			return DOUBLE_FREE;
		}
		
		node = GetChild(node, bit);
		--bit_number;
	}

	node->is_full = EMPTY;
	
	UpdateBranch(node);
	
	GetParent(node)->child[bit] = NULL;
	free(node);
	
	return SUCCESS;
}

/******* HELPER FUNCTIONS ***********/

static node_t *GetRoot(const trie_t *trie)
{
	assert(trie);
	
	return trie->root;
}

static size_t GetHight(trie_t *trie)
{
	assert(trie);
	
	return trie->hight;
}

static node_t *GetChild(node_t *node, size_t direction)
{
	assert(node);
	
	return node->child[direction];
}

static node_t *GetParent(node_t *node)
{
	assert(node);
	
	return node->paraent;
}

static int GetIsFull(node_t *node)
{
	if (NULL == node)
	{
		return EMPTY;
	}
	
	return node->is_full;
}

static node_t *CreateNode(node_t *paraent)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));;
	if (NULL == node)
	{
		return NULL;
	}
	
	node->child[0] = NULL;
	node->child[1] = NULL;
	node->paraent = paraent;
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
		
			return MEMORY_FALIURE;
		}
		
		*out_param = *out_param ^ (bit << (bit_number - 1));
		
		--bit_number;

		node = GetChild(node, bit);
	}
	
	node->is_full = FULL;
	node->is_leaf = 1;
	
	UpdateBranch(node);
	
	return SUCCESS;
}

static void UpdateBranch(node_t *node)
{
	assert(node);
	
	node = GetParent(node);
	
	while (NULL != node)
	{
		/* if both childs are full then so is the parent */
		if (NULL != GetChild(node,0) && NULL != GetChild(node, 1))
		{		
			if (FULL == GetIsFull(GetChild(node,0)) && 
				FULL == GetIsFull(GetChild(node,1)))
			{
				node->is_full = FULL;
			}
		}
		else
		{
			return;
		}
		
		node = GetParent(node);
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
	if (1 == node->is_leaf)
	{
		++*counter;	
	}
	
	PreOrderedCount(GetChild(node, LEFT), counter);
	PreOrderedCount(GetChild(node, RIGHT), counter);
}





