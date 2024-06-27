#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time_t */
#include <string.h> /* strcpy strcmp */

#include "hashtable.h"

#define NUM_PERSONS 30
#define MAX_NAME_LENGTH 50


typedef struct person
{
	size_t id;
	char *first_name;
	char *last_name;
	int gender; /* 1 - male 0 - femeale */
	short hight;
} person_t;

void TestCreateDestroy(void);
void TestIsEmpty(void);
void TestSize(void);
void TestInsert(void);
void TestForEach(void);
void TestFind(void);
void TestRemove(void);
static person_t* CreatePersons(void);
static void free_persons(person_t *persons, int num_persons);
static size_t GetKey(person_t *person);

static int checker = 0;

static size_t Hash_function(void *key)
{
	size_t id = 0;
	size_t first_digit = 0;
	
	assert(key);
	
	id = *(size_t*)key;
	first_digit = id / 100000000;
	
	return first_digit;	
}

static int Compare(const void *key1, const void *key2)
{
	size_t key = 0;
	person_t *person2 = (person_t *)key2;

	assert(key1);
	assert(person2);
	
	key = *(size_t*)key1;
	
	return (key  == GetKey(person2));
}

static int Printfileds(void *data, void *params)
{
	person_t *person = (person_t*)data;
	
	assert(person);
	assert(params);
	
	printf("----- person -----\n");
	
	switch (*(int*)params) 
	{
	case 1:
		printf("ID: %ld\n", person->id);
	break;
	case 2:
		printf("First_Name: %s\n", person->first_name);
	break;
	case 3:
		printf("Last Name: %s\n", person->last_name);
	break;
	case 4:
		printf("Gender: %s\n", ((person->gender) ? "Male" : "Female"));
	break;
	case 5:
		printf("Hight: %d\n", person->hight);
	break;
	default:
		printf("ID: %ld\n", person->id);
		printf("First_Name: %s\n", person->first_name);
		printf("Last Name: %s\n", person->last_name);
		printf("Gender: %s\n", ((person->gender) ? "Male" : "Female"));
		printf("Hight: %d\n", person->hight);
	}
	
	printf("---------------\n\n");
	
	return 0;
}


int main(void)
{

	TestCreateDestroy();
	TestIsEmpty();
	TestSize();
	TestInsert();
	TestForEach();
	TestFind();
	TestRemove();
	
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
	size_t size = 10;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	
	printf("---------- TestCreateDestroy Start ----------\n");
	if (NULL == table)
	{
		printf("Failed TestCreateDestroy\n");
		 ++checker;
		 
		 return;
	}
	
	HashTableDestroy(table);
	
	printf("PASSED TestCreateDestroy\n");
	printf("------------------------------\n\n");
}

void TestIsEmpty(void)
{
	size_t size = 10;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	
	printf("---------- TestIsEmpty Start ----------\n");
	if (!HashTableIsEmpty(table))
	{
		printf("Failed TestIsEmpty\n");
		 ++checker;
		 
		 return;
	}
	
	HashTableDestroy(table);
	
	printf("PASSED TestIsEmpty\n");
	printf("------------------------------\n\n");
}

void TestSize(void)
{
	size_t size = 10;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	
	printf("---------- TestSize Start ----------\n");
	if (0 != HashTableSize(table))
	{
		printf("Failed TestSize\n");
		 ++checker;
		 
		 return;
	}
	
	HashTableDestroy(table);
	
	printf("PASSED TestSize\n");
	printf("------------------------------\n\n");
}

void TestInsert(void)
{
	size_t size = 10;
	size_t i = 0;
	size_t key = 0;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	person_t *persons = CreatePersons();
	int status = 0;
	
	printf("---------- TestInsert Start ----------\n");

	for (; i < NUM_PERSONS; ++i)
	{
		key = GetKey(persons);
		status = HashTableInsert(table, &key, persons);
		
		if (i + 1 != HashTableSize(table) || 0 != status)
		{
			printf("Failed TestInsert %ld\n", i);
			 ++checker;
		 
		 	return;
		}
		++persons;
	}
	
	if (HashTableIsEmpty(table))
	{
		printf("Failed TestInsert\n");
		 ++checker;
		 
		 return;
	}
	
	free_persons(persons - NUM_PERSONS, NUM_PERSONS);
	HashTableDestroy(table);
	
	printf("PASSED TestInsert\n");
	printf("------------------------------\n\n");
}

void TestForEach(void)
{
	size_t size = 10;
	size_t i = 0;
	size_t key = 0;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	person_t *persons = CreatePersons();
	int params = 1; 
	int status = 0;
	
	printf("---------- TestForEach Start ----------\n");

	for (; i < NUM_PERSONS; ++i)
	{
		key = GetKey(persons);
		status = HashTableInsert(table, &key, persons);
		
		if (i + 1 != HashTableSize(table) || 0 != status)
		{
			printf("Failed TestForEach %ld\n", i);
			 ++checker;
		 
		 	return;
		}
		++persons;
	}
	
	status = HashTableForEach(table, &Printfileds,&params);
	
	if (0 != status)
	{
		printf("Failed TestForEach\n");
		 ++checker;
	 
	 	return;
	}
	
	
	free_persons(persons - NUM_PERSONS, NUM_PERSONS);
	HashTableDestroy(table);
	
	printf("PASSED TestForEach\n");
	printf("------------------------------\n\n");
}

void TestFind(void)
{
	size_t size = 10;
	size_t i = 0;
	size_t key = 0;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	person_t *persons = CreatePersons();
	int status = 0;
	person_t *person = NULL;
	
	printf("---------- TestFind Start ----------\n");

	for (; i < NUM_PERSONS; ++i)
	{
		key = GetKey(persons);
		status = HashTableInsert(table, &key, persons);
		
		if (i + 1 != HashTableSize(table) || 0 != status)
		{
			printf("Failed TestFind %ld\n", i);
			 ++checker;
		 
		 	return;
		}
		++persons;
	}
	
	person = (person_t*)HashTableFind(table, &key);
	
	if (NULL == person || GetKey(person) != key)
	{
		printf("Failed TestFind\n");
		 ++checker;
	 
	 	return;
	}
	
	key = 1;
	person = (person_t*)HashTableFind(table, &key);
	
	if (NULL != person)
	{
		printf("Failed TestFind\n");
		 ++checker;
	 
	 	return;
	}
	
	free_persons(persons - NUM_PERSONS, NUM_PERSONS);
	HashTableDestroy(table);
	
	printf("PASSED TestFind\n");
	printf("------------------------------\n\n");
}

void TestRemove(void)
{
	size_t size = 10;
	size_t i = 0;
	size_t key = 0;
	hash_table_t *table = HashTableCreate(&Hash_function, &Compare, size);
	person_t *persons = CreatePersons();
	int status = 0;
	
	printf("---------- TestRemove Start ----------\n");

	for (; i < NUM_PERSONS; ++i)
	{
		key = GetKey(persons);
		status = HashTableInsert(table, &key, persons);
		
		if (i + 1 != HashTableSize(table) || 0 != status)
		{
			printf("Failed TestRemove %ld\n", i);
			 ++checker;
		 
		 	return;
		}
		++persons;
	}
	
	for (i = 0; i < NUM_PERSONS; ++i)
	{
		--persons;
		key = GetKey(persons);
		HashTableRemove(table, &key);
		
		if (NUM_PERSONS - (i + 1) != HashTableSize(table))
		{
			printf("Failed TestRemove %ld\n", i);
			 ++checker;
		 
		 	return;
		}
	}
	
	if (!HashTableIsEmpty(table))
	{
		printf("Failed TestRemove\n");
		 ++checker;
		 
		 return;
	}
	
	free_persons(persons, NUM_PERSONS);
	HashTableDestroy(table);
	
	printf("PASSED TestRemove\n");
	printf("------------------------------\n\n");
}

/************************** helper function ********************/

static person_t* CreatePersons(void)
{
    person_t* persons;
    int i;
    char* first_names[] = {"Yan", "Or", "Amit", "Yarden", "David"};
    char* last_names[] = {"Smith", "Johnson", "Williams", "Brown", "Jones"};
    int num_first_names = sizeof(first_names) / sizeof(first_names[0]);
    int num_last_names = sizeof(last_names) / sizeof(last_names[0]);

    /* Seed the random number generator */
    srand((unsigned int)time(NULL));

    /* Allocate memory for 30 persons */
    persons = (person_t*)malloc(NUM_PERSONS * sizeof(person_t));
    if (persons == NULL)
    {
        return NULL; /* Memory allocation failed */
    }

    for (i = 0; i < NUM_PERSONS; i++)
    {
        /* Generate random 9-digit ID */
        persons[i].id = (size_t)(100000000 + (rand() % 900000000));

        /* Allocate and copy random first name */
        persons[i].first_name = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
        if (persons[i].first_name == NULL)
        {
            /* Handle memory allocation failure */
            /* (In a real scenario, we should free previously allocated memory) */
            return NULL;
        }
        strcpy(persons[i].first_name, first_names[rand() % num_first_names]);

        /* Allocate and copy random last name */
        persons[i].last_name = (char*)malloc(MAX_NAME_LENGTH * sizeof(char));
        if (persons[i].last_name == NULL)
        {
            /* Handle memory allocation failure */
            /* (In a real scenario, we should free previously allocated memory) */
            return NULL;
        }
        strcpy(persons[i].last_name, last_names[rand() % num_last_names]);

        /* Randomly assign gender */
        persons[i].gender = rand() % 2;

        /* Randomly assign height between 150cm and 200cm */
        persons[i].hight = (short)(rand() % 51 + 150);
    }

    return persons;
}

static void free_persons(person_t *persons, int num_persons)
{
    int i;
    
    if (persons == NULL)
        return;

    for (i = 0; i < num_persons; i++)
    {
        free(persons[i].first_name);
        free(persons[i].last_name);
    }
    
    free(persons);
}

static size_t GetKey(person_t *person)
{
	assert(person);
	
	return person->id;
}


