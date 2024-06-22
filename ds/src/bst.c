/********************************** 
   Code by: Yan Meiri	
   Project: Binary search Tree data structure
   Date: 10/06/24
   Review by: itay
   Review Date: 17/06/2024
   Approved by: 
   Approval Date: 
**********************************/
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "bst.h"

typedef struct node
{
	void *data;
	struct node *left;
	struct node *right;
	struct node *parent;
} node_t; 

struct bst
{
	node_t *root;
	bst_cmp_func_t cmp_func;
};

static bst_iter_t CreateNode(void *data, node_t *parent);
static node_t *GetRoot(bst_t *bst);
static node_t *Left(node_t *iter); 
static node_t *Right(node_t *iter);							  
static node_t *Parent(node_t *iter);
static bst_cmp_func_t GetCompare(bst_t *tree);
static int IsSameNode(node_t *node1, node_t *node2);
static void ChangeChildOfParentNode(node_t *node, node_t *change_to);
static int Count(void *data, void *param);
static void UpdateParentOfChild(node_t *node, node_t *update_to);
static void CopyNode(node_t *dest, node_t *src);
static void *GetData(node_t *node);

#define NODE_TO_ITER(node) ((bst_iter_t)node)
#define ITER_TO_NODE(iter) ((node_t*)iter)

/********************* API Functions **********************/

bst_t *BSTCreate(bst_cmp_func_t compare)
{
	bst_t *bst = NULL;
	
	assert(compare);
	
	bst = (bst_t*)malloc(sizeof(bst_t));
	if (NULL == bst)
	{
		return NULL;
	}
	
	bst->root = CreateNode(NULL, NULL);
	if (NULL == GetRoot(bst))
	{
		free(bst);
		
		return NULL;
	}
	
	bst->cmp_func = compare;
	
	return bst;
}

void BSTDestroy(bst_t *tree)
{
	node_t *node = NULL;
	
	assert(tree);
	
	node = ITER_TO_NODE(BSTBegin(tree));
	
	while (!BSTIsEmpty(tree))
	{
		/* check if there is still a right child to go to */
		if (NULL != Right(node))
		{
			node = Right(node);
			
			/* if there is we will traverse to the left most node */
			while(NULL != Left(node))
			{
				node = Left(node);
			}
		}
		/* if not then its the end and we can start to free the nodes */
		else
		{
			node_t *tmp_node = node;
			node = Parent(node);
			
			ChangeChildOfParentNode(tmp_node, NULL);
			
			free(tmp_node);
		}
	}
	
	free(GetRoot(tree));
	free(tree);
}

bst_iter_t BSTBegin(const bst_t *tree)
{
	node_t *node = NULL;
	
	assert(tree);
	
	node = GetRoot((bst_t*)tree);
	while(NULL != Left(node))
	{
		node = Left(node);
	}
	
	return NODE_TO_ITER(node);
}

bst_iter_t BSTEnd(const bst_t *tree)
{	
	assert(tree);
	
	return tree->root;	
}

bst_iter_t BSTPrev(bst_iter_t iter)
{	
	node_t *node = ITER_TO_NODE(iter);
	
	assert(iter);
	
	/* if there is still a left child to go to */
	if (NULL != Left(node))
	{
		node = Left(node);
		
		/* we traverse to the left most right child */
		while(NULL != Right(node))
		{
			node = Right(node);
		}
				
		return NODE_TO_ITER(node);
	}
	
	/* if there is no left childs to go to */ 
	/* we traverse up in the tree to find a right child node */	
	while (Right(Parent(node)) != node)
	{
		node = Parent(node);
	}
	
	return NODE_TO_ITER(Parent(node));
}

bst_iter_t BSTNext(bst_iter_t iter)
{	
	node_t *node = ITER_TO_NODE(iter);
	
	assert(node);
	
	/* find the left most right child node */
	if (NULL != Right(node))
	{
		node = Right(node);
		
		while (NULL != Left(node))
		{
			node = Left(node);
		}
		
		return NODE_TO_ITER(node);
	}
	/* if no right child exist we traverse up to find a left child node */
	while (Left(Parent(node)) != node)
	{
		node = Parent(node);
	}
	
	return NODE_TO_ITER(Parent(node));
}

void *BSTGetData(bst_iter_t iter)
{
	node_t *node = ITER_TO_NODE(iter);
	
	assert(iter);
	
	return GetData(node);
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	node_t *node = NULL;
	node_t *new_node = NULL;
	int compare_status = 0;
	
	assert(tree);
	assert(BSTIsSameIter(BSTEnd(tree), BSTFind(tree, data)));
	
	node = GetRoot(tree);

	/* traverse the tree to find the node where we can insert the new one */
	while ((NULL != Left(node) || 0 > compare_status) &&
		   (NULL != Right(node) || 0 <= compare_status))
	{		
		if (0 <= compare_status)
		{
			node = Left(node);
		}
		else if (0 > compare_status)
		{
			node = Right(node);
		}

		compare_status = GetCompare(tree)(GetData(node), data);
	}
	
	new_node = CreateNode(data, node);
	if (NULL == new_node)
	{
		return BSTEnd(tree); 
	}
	
	if (0 <= compare_status)
	{
		node->left = new_node;
	}
	else
	{
		node->right = new_node;
	}

	return NODE_TO_ITER(new_node);;
}

void *BSTRemove(bst_iter_t iter_to_remove)
{
	node_t *node_to_remove = ITER_TO_NODE(iter_to_remove);
	void *data = NULL;
	
	assert(iter_to_remove);
	
	data = GetData(node_to_remove);
	
	/* when the removed node doesn't have a left child */
	if(NULL == Left(node_to_remove))
	{
		node_t *right_node = Right(node_to_remove);
		
		/* when the remove node has only a right child */
		if (NULL != right_node)
		{
			/* swiching between the removed node and his right child */
			CopyNode(node_to_remove, right_node);
			UpdateParentOfChild(right_node, node_to_remove);
			
			free(right_node);
			
			return data;
		}
		
		/* when the removed node has no children */
		ChangeChildOfParentNode(node_to_remove, NULL);
		
		free(node_to_remove);
		
		return data;
	}
	/* when the removed node has a left child */
	else
	{
		/* we will replace the removed node with the previous node */ 
		node_t *prev_node = ITER_TO_NODE(BSTPrev(node_to_remove));
		
		node_to_remove->data = GetData(prev_node);

		ChangeChildOfParentNode(prev_node, Left(prev_node));
		UpdateParentOfChild(prev_node, Parent(prev_node));
		
		free(prev_node);
		
		return data;	
	}
}

int BSTIsEmpty(const bst_t *tree)
{
	node_t *node = NULL;
	
	assert(tree);
	
	node = GetRoot((bst_t*)tree);
	
	return (NULL == Left(node));
}


int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	return IsSameNode(ITER_TO_NODE(iter1), ITER_TO_NODE(iter2));
}

bst_iter_t BSTFind(const bst_t *tree, const void *data)
{
	node_t *node = NULL;
	int compare_status = 0;
	
	assert(tree);
	
	node = BSTBegin((bst_t*)tree);
	
	while (!BSTIsSameIter(NODE_TO_ITER(node), BSTEnd(tree)) && 0 >= compare_status)
	{
		compare_status = GetCompare((bst_t*)tree)(GetData(node), data);
		if (0 == compare_status)
		{
			return NODE_TO_ITER(node);
		}
		
		node = BSTNext(NODE_TO_ITER(node));
	}
	
	return BSTEnd(tree);
}

int BSTForEach(bst_t *tree, bst_action_func_t action, void* param)
{
	node_t *node = NULL;
	int status = 0;
	
	assert(tree);
	
	node = ITER_TO_NODE(BSTBegin(tree));
	
	while (!BSTIsSameIter(NODE_TO_ITER(node), BSTEnd(tree)))
	{
		status = action(GetData(node), param);
		
		node = ITER_TO_NODE(BSTNext(node));
	}
	
	return status;
}

size_t BSTSize(const bst_t *tree)
{
	size_t counter = 0;
	
	assert(tree);
	
	BSTForEach((bst_t*)tree, &Count, &counter);
	
	return counter;
}



/********************* Help Functions **********************/

static node_t *CreateNode(void *data, node_t *parent)
{
	node_t *node = (node_t *)malloc(sizeof(struct node));
	if (NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	
	return node;
}
static node_t *GetRoot(bst_t *bst)
{
	assert(bst);
	
	return bst->root;
}

static node_t *Left(node_t *node)
{
	assert(node);
	
	return node->left;
}

static node_t *Right(node_t *node)
{
	assert(node);
	
	return node->right;
}

static node_t *Parent(node_t *node)
{
	assert(node);
	
	return node->parent;
}

static void *GetData(node_t *node)
{
	assert(node);
	
	return node->data;
}

static bst_cmp_func_t GetCompare(bst_t *tree)
{
	assert(tree);
	
	return tree->cmp_func;
}

static int IsSameNode(node_t *node1, node_t *node2)
{
	return (node1 == node2);
}
static void ChangeChildOfParentNode(node_t *node, node_t *change_to)
{
	assert(node);
	
	if (Right(Parent(node)) == node)
	{
		Parent(node)->right = change_to;
	}
	else
	{
		Parent(node)->left = change_to;
	}
}

static int Count(void *data, void *param)
{
	(void)data;
	++*(size_t*)param;
	
	return 0;
}

static void UpdateParentOfChild(node_t *node, node_t *update_to)
{
	assert(node);
	
	if(NULL != node->left)
	{
		node->left->parent = update_to;
	}
			
	if(NULL != node->right)
	{
		node->right->parent = update_to;
	}
}

static void CopyNode(node_t *dest, node_t *src)
{
	assert(dest);
	assert(src);
	
	dest->data = src->data;
	dest->right = src->right;
	dest->left = src->left;
}






