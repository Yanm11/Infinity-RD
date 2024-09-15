#include <stdio.h> /* printf */
#include <assert.h> /* assert*/ 
#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

#define WORD_SIZE sizeof(size_t)

typedef struct person
{
	char *name;
	unsigned int age;
	size_t num_of_kids;
}person_t;

void Swap(void *a, void *b, size_t size)
{
    char byte_buffer;
    char *byte_runner_a = a;
    char *byte_runner_b = b;
    size_t word_buffer;
    size_t *word_runner_a = a;
    size_t *word_runner_b = b;

    /* byte by byte swap */
    while (((size_t)byte_runner_a % WORD_SIZE) != 0) 
    {
        /* doing byte by byte */
        byte_buffer = *byte_runner_a;
        *byte_runner_a = *byte_runner_b;
        *byte_runner_b = byte_buffer;

        ++byte_runner_a;
        ++byte_runner_b;
        --size;
    }

    /* update word runners to new addresses */
    word_runner_a = (size_t*)byte_runner_a;
    word_runner_b = (size_t*)byte_runner_b;

    while (size > WORD_SIZE) 
    {
        word_buffer = *word_runner_a;
        *word_runner_a = *word_runner_b;
        *word_runner_b = word_buffer;

        ++word_runner_a;
        ++word_runner_b;
        size -= WORD_SIZE;
    }

    /* update the older byte runners */
    byte_runner_a = (char*)word_runner_a;
    byte_runner_b = (char*)word_runner_b;
    
    while (size > 0) 
    {
        byte_buffer = *byte_runner_a;
        *byte_runner_a = *byte_runner_b;
        *byte_runner_b = byte_buffer;

        ++byte_runner_a;
        ++byte_runner_b;
        --size;
    }
}

static void PrintPerson(person_t *person)
{
	printf("Name: %s, Age: %d, Number of kids: %ld\n", person->name, person->age, person->num_of_kids);
}


int main(void)
{
	person_t dan = {"Dan", 23, 3};
	person_t or = {"Or", 25, 1};
	
	PrintPerson(&dan);
	PrintPerson(&or);	
	
	Swap(&dan, &or, sizeof(person_t));
	
	PrintPerson(&dan);
	PrintPerson(&or);	
	
	return 0;

}
