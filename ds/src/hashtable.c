#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */

#include "dllist.h"
#include "hashtable.h"

#define ERROR 1

static size_t GetSize(const hash_table_t *table);
static dllist_t **GetTable(const hash_table_t *table);
static dllist_t *GetDlist(dllist_t **dlist_table, int index);
static hash_func_t GetHashFunc(const hash_table_t *table);

struct hash_table
{
	size_t size;
	hash_func_t hash_func;
	hash_cmp_func_t hash_comp;
	dllist_t **hash_table;
};

typedef struct hash_node
{
	void *value;
	void *key;
} hash_node_t;

hash_table_t *HashTableCreate(hash_func_t hash_func,
							  hash_cmp_func_t cmp_func,
							  size_t hash_table_size)
{
	size_t i = 0;
	size_t size_of_malloc = sizeof(hash_table_t) +
							(hash_table_size * sizeof(dllist_t*));
	
	hash_table_t *table = NULL;
	
	assert(0 != hash_table_size);
	assert(hash_func);
	assert(cmp_func);
	
	table = (hash_table_t*)malloc(size_of_malloc);
	if (NULL == table)
	{
		return NULL;
	}
	
	table->hash_table = (dllist_t **)((char*)table + sizeof(hash_table_t));
	
	for (; i < hash_table_size; ++i)
	{
		dllist_t *dlist = DllistCreate();
		
		if (NULL == dlist)
		{
			for(i -= 1; i != 0; --i)
			{
				free(table->hash_table + i);
			}
			
			free(table);
			
			return NULL;
		}
	
		*(table->hash_table + i) = dlist;		
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
	
	assert(table);
	
	size = GetSize(table);
	
	for(; i < size; ++i)
	{
		DllistDestroy(GetDlist(GetTable(table), i));
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
		if (!DllistIsEmpty(GetDlist(dlist_table,i)))
		{
			return 0;
		}
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
		count += DllistSize(GetDlist(dlist_table, i));
	}
	
	return count;
}

int HashTableInsert(hash_table_t *table, const void *key, void *data)
{
	size_t index = 0;
	int status = 0;
	
	dllist_t **dlist_table = NULL;
	dllist_t *list = NULL;
	dllist_iter_t iter = NULL;
	
	hash_node_t *data_node = (hash_node_t*)malloc(sizeof(hash_node_t));
	if (NULL == data)
	{
		return ERROR;
	}
	
	assert(table);
	assert(GetTable(table));
	assert(GetHashFunc(table));
		
	dlist_table = GetTable(table);
	data_node->value = data;
	data_node->key = (void*)key;
	
	index = GetHashFunc(table)((void*)key);
	list = GetDlist(dlist_table, index);
	
	iter = DllistInsertBefore(list, data_node, DllistGetBegin(list));
	status = DllistIsSameIter(iter, DllistGetEnd(list));
	
	return status;
}

void HashTableRemove(hash_table_t *table, const void *key)
{
	assert(table);	
}
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

static dllist_t *GetDlist(dllist_t **dlist_table, int index)
{
	assert(dlist_table);
	
	return *(dlist_table + index);
}

static hash_func_t GetHashFunc(const hash_table_t *table)
{
	assert(table);
	
	return table->hash_func;
}
