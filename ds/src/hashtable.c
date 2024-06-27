#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */

#include "dllist.h"
#include "hashtable.h"

#define ERROR 1

static size_t GetSize(const hash_table_t *table);
static dllist_t **GetTable(const hash_table_t *table);
static hash_func_t GetHashFunc(const hash_table_t *table);
static hash_cmp_func_t GetHashComp(const hash_table_t *table);
static dllist_iter_t HashFindIter(const hash_table_t *table,
								  const void *key,
								  int *status);
static size_t GetIndex(hash_table_t *table, void *key);
							  
struct hash_table
{
	size_t size;
	hash_func_t hash_func;
	hash_cmp_func_t hash_comp;
	dllist_t **hash_table;
};

/************************** API FUNCTIONS ********************/

hash_table_t *HashTableCreate(hash_func_t hash_func,
							  hash_cmp_func_t cmp_func,
							  size_t hash_table_size)
{
	size_t i = 0;
	size_t size_of_malloc = sizeof(hash_table_t) +
							(hash_table_size * sizeof(dllist_t*));
	hash_table_t *table = NULL;
	dllist_t **dlist_table;
	
	assert(0 != hash_table_size);
	assert(hash_func);
	assert(cmp_func);
	
	table = (hash_table_t*)malloc(size_of_malloc);
	if (NULL == table)
	{
		return NULL;
	}
	
	table->hash_table = (dllist_t **)((char*)table + sizeof(hash_table_t));
	
	dlist_table = GetTable(table);
	
	/* creating and assigning dlist to each bucket */
	for (; i < hash_table_size; ++i)
	{
		dllist_t *dlist = DllistCreate();
		
		if (NULL == dlist)
		{
			/* if fail go back and free */
			for(i -= 1; i != 0; --i)
			{
				
				free(dlist_table);
				--dlist_table;
			}
			
			free(table);
			
			return NULL;
		}
	
		*dlist_table = dlist;
		
		++dlist_table;		
	}
	
	table->size = hash_table_size;
	table->hash_func = hash_func;
	table->hash_comp = cmp_func;
	
	return table;
}

void HashTableDestroy(hash_table_t *table)
{
	size_t i = 0;
	size_t size = 0;
	dllist_t **dlist_table = NULL;
	
	assert(table);
	assert(GetTable(table));
	
	dlist_table = GetTable(table);
	size = GetSize(table);
	
	for(; i < size; ++i)
	{
		DllistDestroy(*dlist_table);
		++dlist_table;
	}
	
	free(table);
}

int HashTableIsEmpty(const hash_table_t *table)
{
	size_t i = 0;
	size_t size = 0;
	dllist_t **dlist_table = NULL;
	
	assert(table);
	
	dlist_table = GetTable(table);
	size = GetSize(table);
	
	for (; i < size; ++i)
	{
		if (!DllistIsEmpty(*dlist_table))
		{
			return 0;
		}
		
		++dlist_table;
	}
	
	return 1;
}

size_t HashTableSize(const hash_table_t *table)
{
	size_t i = 0;
	size_t size_table = 0;
	size_t count = 0;
	dllist_t **dlist_table = NULL;
	
	assert(table);	
	
	dlist_table = GetTable(table);
	size_table = GetSize(table);
	
	for (; i < size_table; ++i)
	{
		count += DllistSize(*dlist_table);
		++dlist_table;
	}
	
	return count;
}

int HashTableInsert(hash_table_t *table, const void *key, void *data)
{
	size_t index = 0;

	dllist_t *list = NULL;
	dllist_iter_t iter = NULL;
	
	assert(table);
	assert(GetTable(table));
	assert(GetHashFunc(table));
	
	index = GetIndex(table,(void*)key);
	list = *(GetTable(table) + index);
	
	iter = DllistPushFront(list, data);
	
	return DllistIsSameIter(iter, DllistGetEnd(list));
}

void HashTableRemove(hash_table_t *table, const void *key)
{
	int status = 0;
	dllist_iter_t iter = NULL;
	
	assert(table);
	
	iter = HashFindIter(table, key, &status);
	
	if (status)
	{
		return;
	}
	
	DllistRemove(iter);
}

int HashTableForEach(hash_table_t *table,
					 hash_action_func_t action,
					 void *params)
{
	size_t i = 0;
	size_t size_table = 0;
	int status = 0;
	dllist_t **dlist_table = NULL;
	
	assert(table);
	assert(GetTable(table));
	assert(action);
	
	dlist_table = GetTable(table);
	size_table = GetSize(table);
	
	for (; i < size_table; ++i)
	{
		dllist_t *list = *dlist_table;
		
		printf("------bucekt %ld ------\n", i);
		
		status = DllistForEach(DllistGetBegin(list),
							   DllistGetEnd(list),
							   action,
							   params);
		
		if (0 != status)
		{
			return status;
		}
		
		++dlist_table;
	}
	
	return status;
	
}

void *HashTableFind(const hash_table_t *table, const void *key)
{
	int status = 0;
	dllist_iter_t iter = NULL;
	
	assert(table);
	
	iter = HashFindIter(table, key, &status);
	
	if (status)
	{
		return NULL;
	}
	
	return DllistGetData(iter);
}

/************************** HELPER FUNCTIONS ********************/

static size_t GetSize(const hash_table_t *table)
{
	assert(table);
	
	return table->size;
}

static dllist_t **GetTable(const hash_table_t *table)
{
	assert(table);
	
	return table->hash_table;
}

static hash_func_t GetHashFunc(const hash_table_t *table)
{
	assert(table);
	
	return table->hash_func;
}

static hash_cmp_func_t GetHashComp(const hash_table_t *table)
{
	assert(table);
	
	return table->hash_comp;
}

static dllist_iter_t HashFindIter(const hash_table_t *table,
								  const void *key,
								  int *status)
{
	size_t index = 0;
	dllist_t *list = NULL;
	dllist_iter_t iter = NULL;
	
	assert(table);
	assert(GetTable(table));
	assert(GetHashComp(table));
	assert(GetHashFunc(table));
	assert(status);
	

	index = GetIndex((hash_table_t*)table,(void*)key);
	list = *(GetTable(table) + index);
	
	iter = DllistFind((void*)key,
					  DllistGetBegin(list),
					  DllistGetEnd(list),
					  GetHashComp(table));
					  
	*status = DllistIsSameIter(iter, DllistGetEnd(list));
	
	return iter;
	
}

static size_t GetIndex(hash_table_t *table, void *key)
{
	assert(table);
	assert(GetTable(table));
	
	return GetHashFunc(table)(key) % GetSize(table);
}
