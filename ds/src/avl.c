#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free*/
#include <stdio.h> /* printf */
#include "avl.h"

#define NUM_CHILDREN 2
#define LEFT 0
#define RIGHT 1
#define STARTING_HIGHT 1

typedef struct node
{
	void *data;
	struct node *children[NUM_CHILDREN];
	size_t hight;
} node_t;

struct avl
{
	node_t *root;
	avl_cmp_func_t cmp_func;
};

static node_t *CreateNode(void *data);
static node_t *GoToChild(node_t *node, int index);
static node_t *GoToRoot(avl_t *tree);
static void PostOrderedDestroy(node_t *node);
static void PreOrderedCount(node_t *node, size_t *counter);
static size_t GetHight(node_t *root);
static void *GetData(node_t *node);
static int FindAndInsert(node_t *node, void *data, avl_cmp_func_t cmp_func);
static int InsertNode(node_t *parent_node, int direction_to_insert, void *data);
static void SetChildOfNode(node_t *node,
							 node_t *child,
							 int direction_of_child);
static avl_cmp_func_t GetCompare(avl_t *tree);
static node_t *FindNode(node_t *node, avl_cmp_func_t cmp_func, void *data);
static int ForEachInOrder(node_t *node,
							  avl_action_func_t action,
							  void* params);
static node_t *PrevSuccessor(node_t *left_node);
static node_t *RemoveNode(avl_t *tree, node_t *node);
static node_t *FindAndRemove(avl_t *tree, node_t *node, void *data);

/********************* API FUNCTIONS ********************/

avl_t *AVLCreate(avl_cmp_func_t compare)
{
	avl_t *avl = NULL;
	
	assert(compare);
	
	avl = (avl_t*)malloc(sizeof(avl_t));
	if (NULL == avl)
	{
		return NULL;
	}
	
	avl->root = NULL;
	avl->cmp_func = compare;
	
	return avl;
}

void AVLDestroy(avl_t *tree)
{
	assert(tree);
	
	PostOrderedDestroy(GoToRoot(tree));
	
	free(tree);
}

size_t AVLCount(const avl_t *tree)
{
	size_t count = 0;
	
	assert(tree);
	
	PreOrderedCount(GoToRoot((avl_t*)tree), &count);
	
	return count;
}

size_t AVLHeight(const avl_t *tree)
{
	assert(tree);
	
	return GetHight(GoToRoot((avl_t*)tree));
}

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);
	
	return (GoToRoot((avl_t*)tree) == NULL);
}

int AVLInsert(avl_t *tree, void *data)
{
		assert(tree);
		
		/* if its the first element */
		if (NULL == GoToRoot(tree))
		{
			tree->root = CreateNode(data);
			if (NULL == tree->root)
			{
				return -1;
			}
			
			return 0;
		}
		
		return FindAndInsert(GoToRoot(tree), data, GetCompare(tree));
}

void *AVLFind(const avl_t *tree, const void *data)
{
	node_t *node = NULL;
	
	assert(tree);
	
	node = FindNode(GoToRoot((avl_t*)tree),
		   GetCompare((avl_t*)tree), 
		   (void*)data);
		   
	if (NULL == node)
	{
		return NULL;
	}
	
	return GetData(node);
}

int AVLForEach(avl_t *tree,
				 avl_action_func_t action,
				  void* params)
{
	assert(tree);
	assert(action);
	
	return ForEachInOrder(GoToRoot(tree), action, params);
}

void AVLRemove(avl_t *tree, void *data)
{
	assert(tree);
	
	tree->root = FindAndRemove(tree, GoToRoot(tree), data);
}


/********************* HELPER FUNCTIONS ********************/


static node_t *GoToChild(node_t *node, int index)
{
	assert(node);
	
	return node->children[index];
}

static node_t *GoToRoot(avl_t *tree)
{
	assert(tree);
	
	return tree->root;
}

static size_t GetHight(node_t *root)
{
	assert(root);
	
	return root->hight;
}

static void *GetData(node_t *node)
{
	assert(node);
	
	return node->data;
}

static avl_cmp_func_t GetCompare(avl_t *tree)
{
	assert(tree);
	
	return tree->cmp_func;
}

static void SetChildOfNode(node_t *node,
							 node_t *child,
							 int direction_of_child)
{
	assert(node);
	
	node->children[direction_of_child] = child;
}

static node_t *CreateNode(void *data)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	node->hight = STARTING_HIGHT;
	
	return node;
}

static void PostOrderedDestroy(node_t *node)
{
	if (!node)
	{
		return;
	}
	
	PostOrderedDestroy(GoToChild(node, LEFT));
	PostOrderedDestroy(GoToChild(node, RIGHT));
	free(node);
}

static void PreOrderedCount(node_t *node, size_t *counter)
{
	if (!node)
	{
		return; 
	}
	
	++*counter;
	
	PreOrderedCount(GoToChild(node, LEFT), counter);
	PreOrderedCount(GoToChild(node, RIGHT), counter);
}

static int FindAndInsert(node_t *node, void *data, avl_cmp_func_t cmp_func)
{
	int status_compare = cmp_func(GetData(node), data);
	
	/* direction will be 1 to go right and 0 to go left*/
	int direction_to_move = status_compare < 0;
	
	if (!GoToChild(node, direction_to_move))
	{
		return InsertNode(node, direction_to_move, data);
	}
	
	return FindAndInsert(GoToChild(node, direction_to_move), data, cmp_func);
}

static int InsertNode(node_t *node, int direction_to_insert, void *data)
{
	node_t *new_node = NULL;
	
	assert(node);
	
	new_node = CreateNode(data);
	if (NULL == new_node)
	{
		return -1;
	}
	
	SetChildOfNode(node, new_node, direction_to_insert);
	
	return 0;
}

static node_t *FindNode(node_t *node, avl_cmp_func_t cmp_func, void *data)
{
	int result = 0;
	int direction_to_move = 0;
	
	assert(cmp_func);
	
	if (NULL == node)
	{
		return NULL;
	}
	
	result = cmp_func(GetData(node), data);
	direction_to_move = result < 0;
	
	if (0 == result)
	{
		return node;
	}
	
	return FindNode(GoToChild(node, direction_to_move), cmp_func, data);	
}

static int ForEachInOrder(node_t *node,
							  avl_action_func_t action,
							  void* params)
{
	int status = 0;

	if (!node)
	{
		return status;
	}
	
	ForEachInOrder(GoToChild(node, LEFT), action, params);
	
	status = action(GetData(node), params);
	
	ForEachInOrder(GoToChild(node, RIGHT), action, params);
	
	return status;
}

static node_t *FindAndRemove(avl_t *tree, node_t *node, void *data)
{
	int result = 0;
	int dir_to_move = 0;
	
	assert(tree);
	
	if (NULL == node)
	{
		return NULL;
	}
	
	result = GetCompare(tree)(GetData(node), data);
	dir_to_move = result < 0;	/* if 1 then RIGHT if 0 then LEFT */
	
	if (0 == result)
	{
		return RemoveNode(tree,node);
	}
	
	node->children[dir_to_move] = FindAndRemove(tree,
												GoToChild(node, dir_to_move),
											    data);
											  										  
	return node;
	
}

static node_t *RemoveNode(avl_t *tree, node_t *node)
{
	node_t *replaced_node = NULL;
	void *new_data = NULL;
	int dir_to_move = 0;
	
	assert(tree);
	assert(node);
	
	/* 2 child nodes */
	if (NULL != GoToChild(node, LEFT) && NULL != GoToChild(node, RIGHT))
	{
		replaced_node = PrevSuccessor(GoToChild(node, LEFT));
		new_data = GetData(replaced_node);
		
		AVLRemove(tree, new_data);
		
		node->data = new_data;
		
		return node;
	}
	
	/* 0 or 1 child nodes */
	dir_to_move = (NULL != GoToChild(node, RIGHT)) ? RIGHT : LEFT;
		
	replaced_node =  GoToChild(node, dir_to_move);
	
	free(node);
	
	return replaced_node;

}

static node_t *PrevSuccessor(node_t *left_node)
{
	assert(left_node);
	
	if (NULL == GoToChild(left_node, RIGHT))
	{
		
		return left_node;
	}
	
	return PrevSuccessor(GoToChild(left_node, RIGHT));
}

















