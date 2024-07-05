#include <stdio.h> /* printf */
#include <assert.h> /* assert */
	
#include "trie.h"
#define DEPTH 6
void TestCreateDestroy(void);
void TestInsert(void);
void TestRemove(void);
static int TestInsertAMIT(void);
/*void TestCount(void);*/
/*void TestInsert(void);*/
/*void TestFind(void);*/
/*void TestForEach(void);*/
/*void TestRemove(void);*/

static int checker = 0;

int main(void)
{
	TestCreateDestroy();
	TestInsert();
	TestInsertAMIT();
	TestRemove();
/*	TestCount();*/
/*	TestInsert();*/
/*	TestFind();*/
/*	TestForEach();*/
/*	TestRemove();*/
	
	if (checker)
	{
		printf("In Total Failed %d Tests\n", checker);
		return 0;
	}
	
	printf("\nPASSED ALL TESTS!!!!!\n");
	
	return 0;
}

void TestCreateDestroy(void)
{
	size_t hight = 8;
	trie_t *trie = TrieCreate(hight);
	if (NULL == trie)
	{
		printf("FAILED TestCreateDestroy\n");
		++checker;
		
		return;
	}
	
	TrieDestroy(trie);
	
	printf("PASSED TestCreateDestroy!!\n");
}

void TestInsert(void)
{
	size_t hight = 8;
	size_t max_num_address = 256;
	trie_t *trie = TrieCreate(hight);
	size_t i = 0;
	bitarr_t new_address = 0;
	bitarr_t address = 0;
	trie_status_e status = SUCCESS;
	size_t count = 0;
	
	for (;i < max_num_address; ++i)
	{
		address = i;
		status = TrieInsert(trie, address, &new_address);
		if (status != SUCCESS || new_address != address)
		{
			printf("FAILED TestInsert %ld\n", i);
			++checker;
		
			return;
		}
	} 
	
	count = TrieCount(trie);
	
	address = 0;
	status = TrieInsert(trie, address, &new_address);
	if (count != 256 || status != TRIE_FULL || new_address != 0)
	{
		printf("FAILED TestInsert %ld\n", i);
		++checker;
	
		return;
	}
	
	++i;
	
	TrieDestroy(trie);

	trie = TrieCreate(hight);
	address = 0;
	status = TrieInsert(trie, address, &new_address);
	count = TrieCount(trie);
	if (count != 1 || status != SUCCESS || new_address != address)
	{
		printf("FAILED TestInsert %ld\n", i);
		++checker;
	
		return;
	}
	
	++i;
	
	address = 0;
	status = TrieInsert(trie, address, &new_address);
	count = TrieCount(trie);
	if (count != 2 || status != SUCCESS || new_address != 1)
	{
		printf("FAILED TestInsert %ld\n", i);
		++checker;
	
		return;
	}
	
	++i;
	
	address = 255;
	status = TrieInsert(trie, address, &new_address);
	count = TrieCount(trie);
	if (status != SUCCESS || new_address != 255)
	{
		printf("FAILED TestInsert %ld\n", i);
		++checker;
	
		return;
	}
	
	++i;
	
	address = 255;
	status = TrieInsert(trie, address, &new_address);
	count = TrieCount(trie);
	if (status != SUCCESS || new_address != 2)
	{
		printf("FAILED TestInsert %ld\n", i);
		++checker;
	
		return;
	}
	
	TrieDestroy(trie);
	printf("PASSED TestInsert!!\n");
}

static int TestInsertAMIT(void)
{
	trie_t *trie = NULL;
	trie_status_e status = SUCCESS;
	bitarr_t get_element = 0;
	bitarr_t address = 0;
	size_t count = 0;
	
	/*create trie*/
	trie = TrieCreate(DEPTH);
	
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if (7 != count || 0 != get_element || SUCCESS != status)
	{
		printf("failed TestInsert1\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert1\n");
	}
	address = 63;
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( 63 != get_element || SUCCESS != status)
	{
		printf("TestInsert2\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert2\n");
	}
	address = 62;
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( 62 != get_element || SUCCESS != status)
	{
		printf("TestInsert3\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert3\n");
	}
	
	/* check if TRIE_SUCCESSfully inserted even when the key is taken*/
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( SUCCESS != status || 1 != get_element)
	{
		printf("TestInsert4\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert4\n");
	}
	address = 40;
	/* check if TRIE_SUCCESSfully inserted the requested key*/
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( SUCCESS != status)
	{
		printf("TestInsert5\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert5\n");
	}
	/* check if existing keys can be found*/

	/* check if non-existing keys cannot be found*/

	address = 40;
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( SUCCESS != status || 41 != get_element)
	{
		printf("TestInsert8\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert6\n");
	}
	/* check if existing keys can be found*/

	address = 53;
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( SUCCESS != status || 53 != get_element)
	{
		printf("TestInsert10\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert7\n");
	}
	address = 53;
	status = TrieInsert(trie, address, &get_element);
	count = TrieCount(trie);
	if ( SUCCESS != status || 54 != get_element)
	{
		printf("TestInsert11\n");
		TrieDestroy(trie);
		return 1;
	}
	else
	{
		printf("passed TestInsert8\n");
	}
	TrieDestroy(trie);
	return 0;
}

void TestRemove(void)
{
	size_t hight = 8;
	size_t max_num_address = 256;
	trie_t *trie = TrieCreate(hight);
	size_t i = 0;
	bitarr_t new_address = 0;
	bitarr_t address = 0;
	trie_status_e status = SUCCESS;
	size_t count = 0;
	
	for (;i < max_num_address; ++i)
	{
		address = i;
		status = TrieInsert(trie, address, &new_address);
		if (status != SUCCESS || new_address != address)
		{
			printf("FAILED TestRemove %ld\n", i);
			++checker;
		
			return;
		}
	}
	
	status = TrieRemove(trie, 255);
	count = TrieCount(trie);
	if (status != SUCCESS ||  count != 255)
	{
		printf("FAILED TestRemove %ld\n", i);
		++checker;
	
		return;
	}
	++i;
	status = TrieRemove(trie, 255);
	count = TrieCount(trie);
	if (status != DOUBLE_FREE ||  count != 255)
	{
		printf("FAILED TestRemove %ld\n", i);
		++checker;
	
		return;
	}
	max_num_address = 255;
	for (;i < max_num_address; ++i)
	{
		address = i;
		status = TrieRemove(trie, address);
		if (status != SUCCESS || count != (255-i-1))
		{
			printf("FAILED TestRemove %ld\n", i + 300);
			++checker;
		
			return;
		}
	}
	
	TrieDestroy(trie);
	printf("PASSED TestRemove!!\n");
}
