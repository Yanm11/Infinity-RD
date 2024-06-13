#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "bst.h"

struct node
{
	void *data;
	struct node *left;
	struct node *right;
	struct node *parent;
}; 

struct bst
{
	bst_iter_t end;
	bst_cmp_func_t cmp_func;
};

static bst_iter_t CreateIter(void *data,
							  bst_iter_t left,
							  bst_iter_t right,
							  bst_iter_t parent);
static bst_iter_t Left(bst_iter_t iter); 
static bst_iter_t Right(bst_iter_t iter);							  
static bst_iter_t Parent(bst_iter_t iter);
static void ChangeChildOfParentIter(bst_iter_t iter, bst_iter_t change_to);
static int Count(void *data, void *param);
static void UpdateParentOfChild(bst_iter_t iter, bst_iter_t update_to);
static void CopyNode(bst_iter_t dest, bst_iter_t src);

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
	
	bst->end = CreateIter(NULL, NULL, NULL, NULL);
	if (NULL == bst->end)
	{
		free(bst);
		
		return NULL;
	}
	
	bst->cmp_func = compare;
	
	return bst;
}

void BSTDestroy(bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = Left(BSTEnd(tree));
	
	while (!BSTIsEmpty(tree))
	{
		BSTRemove(iter);
	}
	
	free(BSTEnd(tree));
	free(tree);
}

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = BSTEnd(tree);
	while(NULL != Left(iter))
	{
		iter = Left(iter);
	}
	
	return iter;
}

bst_iter_t BSTEnd(const bst_t *tree)
{	
	assert(tree);
	
	return tree->end;	
}

bst_iter_t BSTPrev(bst_iter_t iter)
{	
	assert(iter);
	
	/* if there is still a left child to go to */
	if (NULL != Left(iter))
	{
		iter = Left(iter);
		
		while(NULL != Right(iter))
		{
			iter = Right(iter);
		}
				
		return iter;
	}
	
	/* if there is no more left childs to go to */ 	
	while (Right(Parent(iter)) != iter)
	{
		iter = Parent(iter);
	}
	
	return Parent(iter);
}

bst_iter_t BSTNext(bst_iter_t iter)
{	
	assert(iter);
	
	/* check if node has a right child that does not have a left child */
	if (NULL != Right(iter))
	{
		iter = Right(iter);
		
		while (NULL != Left(iter))
		{
			iter = Left(iter);
		}
		
		return iter;
	}
	/* check if node is a left child of its parent */
	else
	{
		while (Left(Parent(iter)) != iter)
		{
			iter = Parent(iter);
		}
		
		return Parent(iter);
	}
}

void *BSTGetData(bst_iter_t iter)
{
	assert(iter);
	
	return iter->data;
}

bst_iter_t BSTInsert(bst_t *tree, void *data)
{
	bst_iter_t iter = NULL;
	bst_iter_t new_iter = NULL;
	int status = 0;
	
	assert(tree);
	assert(BSTEnd(tree) == BSTFind(tree, data));
	
	iter = BSTEnd(tree);
	new_iter = CreateIter(data, NULL, NULL, NULL);
	if (NULL == new_iter)
	{
		return iter; 
	}
	
	while ((NULL != Left(iter) || 0 > status) &&
		   (NULL != Right(iter) || 0 <= status))
	{		
		if (0 < status)
		{
			iter = Left(iter);
		}
		else if (0 > status)
		{
			iter = Right(iter);
		}
		else
		{
			iter = Left(iter);
		}
		status = tree->cmp_func(BSTGetData(iter), BSTGetData(new_iter));
	}
	
	new_iter->parent = iter;
	
	if (0 <= status)
	{
		iter->left = new_iter;
		
		return new_iter;
	}
	
	iter->right = new_iter;
	
	return new_iter;
}

void *BSTRemove(bst_iter_t iter_to_remove)
{
	bst_iter_t tmp_iter = NULL;
	void *data = NULL;
	
	assert(iter_to_remove);
	
	data = BSTGetData(iter_to_remove);
	
	if(NULL == Left(iter_to_remove))
	{
		tmp_iter = Right(iter_to_remove);
		if (NULL != tmp_iter)
		{
			CopyNode (iter_to_remove, tmp_iter);
			UpdateParentOfChild(tmp_iter, iter_to_remove);
			
			free(tmp_iter);
			
			return data;
		}
		
		ChangeChildOfParentIter(iter_to_remove, NULL);
		
		free(iter_to_remove);
		
		return data;
	}
	
	tmp_iter = Left(iter_to_remove);
	
	while (NULL != Right(tmp_iter))
	{
		tmp_iter = Right(tmp_iter);
	}
	
	iter_to_remove->data = BSTGetData(tmp_iter);

	ChangeChildOfParentIter(tmp_iter, Left(tmp_iter));
	UpdateParentOfChild(tmp_iter, Parent(tmp_iter));
	
	free(tmp_iter);
	
	return data;
}

int BSTIsEmpty(const bst_t *tree)
{
	bst_iter_t iter = NULL;
	
	assert(tree);
	
	iter = BSTEnd(tree);
	
	return ((NULL == Left(iter) && NULL == Right(iter)));
}


int BSTIsSameIter(bst_iter_t iter1, bst_iter_t iter2)
{
	assert(iter1);
	assert(iter2);
	
	return (iter1 == iter2);
}

bst_iter_t BSTFind(const bst_t *tree, const void *data)
{
	bst_iter_t iter = NULL;
	int status = 0;
	
	assert(tree);
	
	iter = BSTBegin(tree);
	
	while (!BSTIsSameIter(iter, BSTEnd(tree)) && 0 >= status)
	{
		status = tree->cmp_func(BSTGetData(iter), data);
		if (0 == status)
		{
			return iter;
		}
		
		iter = BSTNext(iter);
	}
	
	return BSTEnd(tree);
}

int BSTForEach(bst_t *tree, bst_action_func_t action, void* param)
{
	bst_iter_t iter = NULL;
	int status = 0;
	
	assert(tree);
	
	iter = BSTBegin(tree);
	
	while (!BSTIsSameIter(iter, BSTEnd(tree)))
	{
		status = action(BSTGetData(iter), param);
		
		iter = BSTNext(iter);
	}
	
	return status;
}

size_t BSTSize(const bst_t *tree)
{
	size_t count = 0;
	bst_t *new_tree = NULL;
	
	assert(tree);
	
	new_tree = (bst_t*)tree;
	
	BSTForEach(new_tree, &Count, &count);
	
	return count;
}



/********************* Help Functions **********************/

static bst_iter_t CreateIter(void *data,
							  bst_iter_t left,
							  bst_iter_t right,
							  bst_iter_t parent)
{
	bst_iter_t iter = (bst_iter_t)malloc(sizeof(struct node));
	if (NULL == iter)
	{
		return NULL;
	}
	
	iter->data = data;
	iter->left = left;
	iter->right = right;
	iter->parent = parent;
	
	
	return iter;
}

static bst_iter_t Left(bst_iter_t iter)
{
	assert(iter);
	
	return iter->left;
}

static bst_iter_t Right(bst_iter_t iter)
{
	assert(iter);
	
	return iter->right;
}

static bst_iter_t Parent(bst_iter_t iter)
{
	assert(iter);
	
	return iter->parent;
}

static void ChangeChildOfParentIter(bst_iter_t iter, bst_iter_t change_to)
{
	assert(iter);
	
	if (Right(Parent(iter)) == iter)
	{
		Parent(iter)->right = change_to;
	}
	else
	{
		Parent(iter)->left = change_to;
	}
}

static int Count(void *data, void *param)
{
	(void)data;
	++*(size_t*)param;
	
	return 0;
}

static void UpdateParentOfChild(bst_iter_t iter, bst_iter_t update_to)
{
	assert(iter);
	
	if(NULL != iter->left)
	{
		iter->left->parent = update_to;
	}
			
	if(NULL != iter->right)
	{
		iter->right->parent = update_to;
	}
}

static void CopyNode(bst_iter_t dest, bst_iter_t src)
{
	assert(dest);
	assert(src);
	
	dest->data = src->data;
	dest->right = src->right;
	dest->left = src->left;
}






























