#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time_t */
#include <string.h> /* strcpy strcmp */
#include <ctype.h> /* strcpy strcmp */

#include "hashtable.h"
#include "dict.h"

#define LINE_SIZE 256
#define SIZE 105000

void SpellChecker(char *file_name)
{
	size_t i = 0;
    FILE *fp = NULL;
	int status = 0;
	char *words[SIZE] = {0};
	char arr[LINE_SIZE] = {0};
	char str[LINE_SIZE];
	char *key = NULL;
	size_t size_hash = 1009;
	char *word = NULL;
	hash_table_t *table = HashTableCreate(&HashFuncDict,
										  &CompareWords,
										  size_hash);
	
	assert(file_name);
	
    fp = fopen(file_name, "r");
    if (fp == NULL) 
    {
        printf("The file is not opened. The program will now exit.\n");
        exit(0);
    }
	
	while (fgets(arr, LINE_SIZE, fp) != NULL)
	{
		arr[strcspn(arr,"\n")] = '\0';
		
		key = strdup(arr);
		
		status = HashTableInsert(table, key, key);
		if (0 != status)
		{
			printf("Failed insert\n");
		 
		 	return;
		}
		
		words[i] = key;
		++i;
	}

	printf("please write a word:\n");
	fgets(str, LINE_SIZE, stdin);
	str[strcspn(str,"\n")] = '\0';
	
	word = (char*)HashTableFind(table, str);
	
	if (NULL == word)
	{
		printf("word: '%s 'does NOT exist in the dictionary\n", str);
	}
	else
	{
		printf("word:' %s ' DOES exist in the dictionary\n", str);
	}
	
	for (i = 0; i < SIZE; ++i)
	{
		free(words[i]);
	}
	
	HashTableDestroy(table);
    fclose(fp);
}

static size_t HashFuncDict(void *key)
{
    char *word = NULL;
    size_t hash = 0;
    
    assert(key);
    
    word = (char*)key;
    
    if (word[0])  
    {
        char first = tolower(word[0]);
        char second = word[1] ? tolower(word[1]) : 'a';  
        
        hash = (first - 'a') * 26 + (second - 'a');
    }
    
    return hash;
}

static int CompareWords(const void *key1, const void *key2)
{
	char *word1 = (char*)key1;
	char *word2 = (char *)key2;

	assert(word1);
	assert(word2);
	
	return (0 == strcmp(word1, word2));
}

static char *strdup(const char *src)
{
    char *dst = malloc(strlen (src) + 1);
    
    if (dst == NULL)
    {
		return NULL;              
    }
    
    strcpy(dst, src);
                         
    return dst;                            
}
