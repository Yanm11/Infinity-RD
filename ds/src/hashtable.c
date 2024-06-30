#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <stdio.h> /* printf */
#include <math.h> /* math */

#include "dllist.h"
#include "hashtable.h"

#define ERROR 1
#define NO_CACHE 0
#define CACHE 1

static size_t GetBuckets(const hash_table_t *table);
static dllist_t **GetTable(const hash_table_t *table);
static hash_func_t GetHashFunc(const hash_table_t *table);
static hash_cmp_func_t GetHashComp(const hash_table_t *table);
static dllist_iter_t HashFindIter(const hash_table_t *table,
								  const void *key,
								  int *status,
								  int do_cache);
static size_t GetIndex(hash_table_t *table, void *key);
static int Caching(dllist_t *list, dllist_iter_t iter);	
static double AverageNumNodes(const hash_table_t *table);
		  
struct hash_table
{
	size_t buckets;
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
	
	table->buckets = hash_table_size;
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
	size = GetBuckets(table);
	
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
	size = GetBuckets(table);
	
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
	size_table = GetBuckets(table);
	
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
	
	iter = HashFindIter(table, key, &status, NO_CACHE);
	
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
	size_table = GetBuckets(table);
	
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
	
	iter = HashFindIter(table, key, &status, CACHE);
	
	if (status)
	{
		return NULL;
	}
	
	return DllistGetData(iter);
}

double HashTableLoad(const hash_table_t *table)
{
	assert(table);
	
	return ((double)HashTableSize(table) / GetBuckets(table));
}

double HashTableStandardDeviation(const hash_table_t *table)
{
	double mean_nodes = 0;
	double sd = 0;
	size_t buckets = 0;
	size_t i = 0;
	
	assert(table);
	assert(GetTable(table));
	
	mean_nodes = AverageNumNodes(table);
	buckets = GetBuckets(table);
	
	for (; i < buckets; ++i)
	{
		sd += pow((DllistSize(*(GetTable(table) + i)) - mean_nodes), 2);
	}
	
	sd = sqrt((sd / buckets));
	
	return sd;
}

/************************** HELPER FUNCTIONS ********************/

static size_t GetBuckets(const hash_table_t *table)
{
	assert(table);
	
	return table->buckets;
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
								  int *status,
								  int do_cache)
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
	
	if (do_cache && 0 == *status)
	{
		if(0 == Caching(list, iter))
		{
			return DllistGetBegin(list);
		}
	}
	
	return iter;
	
}

static size_t GetIndex(hash_table_t *table, void *key)
{
	assert(table);
	assert(GetTable(table));
	
	return GetHashFunc(table)(key) % GetBuckets(table);
}

static int Caching(dllist_t *list, dllist_iter_t iter)
{
	dllist_iter_t new_iter = NULL;
	
	assert(list);
	
	/* if iter is already at the begigng do nothing */
	if (DllistIsSameIter(DllistGetBegin(list), iter))
	{
		return 1;
	}
	
	new_iter = DllistPushFront(list, DllistGetData(iter));
	
	/* if insert to beging failed do nothing */
	if (DllistIsSameIter(DllistGetEnd(list), new_iter))
	{
		return 1;
	}
	
	DllistRemove(iter);
	
	return 0;
}

static double AverageNumNodes(const hash_table_t *table)
{
	assert(table);
	
	return (HashTableSize(table) / GetBuckets(table));
}
