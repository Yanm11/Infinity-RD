#include <assert.h> /* assert */
#include <stdlib.h> /* malloc free*/
#include <stdio.h> /* printf */
#include "avl.h"

#define NUM_CHILDREN 2
#define LEFT 0
#define RIGHT 1

typedef struct node
{
	void *data;
	struct node *children[NUM_CHILDREN];
	struct node *parent;
	size_t hight;
} node_t;

struct avl
{
	node_t *root;
	avl_cmp_func_t cmp_func;
};

static node_t *CreateNode(void *data, node_t *parent);
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
							  
static void ChangeChildOfParentNode(node_t *node, node_t *change_to, int direction);
static void UpdateParentOfChild(node_t *node, node_t *update_to);
static void CopyNode(node_t *dest, node_t *src);
static node_t *LeftMostRightNode(node_t *left_node);
static int WhichChild(node_t *node);
static node_t *RemoveNode(node_t *node);
static int CountChildren(node_t *node);
static node_t *FindAndUpdate(node_t *node, avl_cmp_func_t cmp_func, void *data);

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
			tree->root = CreateNode(data, NULL);
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

static node_t *CreateNode(void *data, node_t *parent)
{
	node_t *node = (node_t*)malloc(sizeof(node_t));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->parent = parent;
	node->children[LEFT] = NULL;
	node->children[RIGHT] = NULL;
	node->hight = 1;
	
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
	
	new_node = CreateNode(data, node);
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
	printf("node to remove: %d, node we at: %d\n", *(int*)data, *(int*)GetData(node));
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

static void CopyNode(node_t *dest, node_t *src)
{
	assert(dest);
	assert(src);
	
	dest->data = GetData(src);
	dest->children[RIGHT] = GoToChild(src, RIGHT);
	dest->children[LEFT] = GoToChild(src, LEFT);
}

static void UpdateParentOfChild(node_t *node, node_t *update_to)
{
	assert(node);
	
	if(NULL != GoToChild(node, LEFT))
	{
		GoToChild(node,LEFT)->parent = update_to;
	}
			
	if(NULL != GoToChild(node, RIGHT))
	{
		GoToChild(node,RIGHT)->parent = update_to;
	}
}

static void ChangeChildOfParentNode(node_t *node, node_t *change_to, int direction)
{
	assert(node);
	
	node->parent->children[direction] = change_to;
}

static node_t *LeftMostRightNode(node_t *left_node)
{
	assert(left_node);
	
	if (NULL == GoToChild(left_node, RIGHT))
	{
		
		return left_node;
	}
	
	return LeftMostRightNode(GoToChild(left_node, RIGHT));
}

static int WhichChild(node_t *node)
{
	assert(node);
	
	if (GoToChild(node->parent, LEFT) == node)
	{
		return LEFT;	
	}
	
	return RIGHT;
}

static node_t *FindAndUpdate(node_t *node, avl_cmp_func_t cmp_func, void *data)
{
	int result = 0;
	int dir_to_move = 0;
	
	assert(cmp_func);
	
	if (NULL == node)
	{
		return NULL;
	}
	printf("node to remove: %d, node we at: %d\n", *(int*)data, *(int*)GetData(node));
	
	result = cmp_func(GetData(node), data);
	
	/* if 1 then RIGHT if 0 then LEFT */
	dir_to_move = result < 0;
	
	if (0 == result)
	{
		return RemoveNode(node);
	}
	
	node->children[dir_to_move] = FindAndUpdate(GoToChild(node, dir_to_move),
											    cmp_func,
											    data);
											  										  
	return node;
	
}

static node_t *RemoveNode(node_t *node)
{
	int num_children = 0;
	
	assert(node);
	
	num_children = CountChildren(node);
	
	if (0 == num_children)
	{
		return NULL;
	}
	else if (1 == num_children)
	{
		int dir_to_move = (NULL != GoToChild(node, RIGHT)) ? RIGHT : LEFT;
		
		return GoToChild(node, dir_to_move);
	}
	else
	{
		node_t *replaced_node = LeftMostRightNode(GoToChild(node, LEFT));
		
		SetChildOfNode(replaced_node, GoToChild(node,LEFT), LEFT);
		
		SetChildOfNode(replaced_node, GoToChild(node,RIGHT), RIGHT);
	}
}

static int CountChildren(node_t *node)
{
	assert(node);
	
	if (NULL != GoToChild(node, LEFT) && NULL != GoToChild(node, RIGHT))
	{
		return 2;
	}
	
	else if (NULL == GoToChild(node, LEFT) && NULL == GoToChild(node, RIGHT))
	{
		return 0;
	}
	
	return 1;
}


















