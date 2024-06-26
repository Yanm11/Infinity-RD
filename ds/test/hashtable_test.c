#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time_t */
#include <string.h> /* strcpy */
	
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
	person_t *person1 = (person_t *)key1;
	person_t *person2 = (person_t *)key2;

	assert(person1);
	assert(person2);
	
	return person1->id == person2->id;
}

static int Printfileds(void *data, void *params)
{
	person_t *person = (person_t*)data;
	
	assert(person);
	assert(params);
	
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
	}
	
	return 0;
}


int main(void)
{

	TestCreateDestroy();
	TestIsEmpty();
	TestSize();
	TestInsert();
	
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
	person_t *person = NULL;
	
	printf("---------- TestInsert Start ----------\n");

	for (; i < NUM_PERSONS; ++i)
	{
		int status = 0;
		person = persons + i;
		key = GetKey(person);
		status = HashTableInsert(table, &key, person);
		
		if (i + 1 != HashTableSize(table) || 0 != status)
		{
			printf("Failed TestInsert %ld\n", i);
			 ++checker;
		 
		 	return;
		}
	}
	
	
	free_persons(persons, NUM_PERSONS);
	HashTableDestroy(table);
	
	printf("PASSED TestInsert\n");
	printf("------------------------------\n\n");
}



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
        persons[i].id = (size_t)(rand() % 900000000 + 100000000);

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
