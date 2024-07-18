/* approved bt shahar marom */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <string.h> /* memcpy strcmp strcspn strtok */
#include <fcntl.h> /* O_CREAT */
#include <semaphore.h> /* sem_open sem_post sem_wait sem_getvalue sem_close */
#include <sys/stat.h> /* S_IRWXU */
#include <stdlib.h> /* atoi maloc free */
#include <assert.h> /* assert */

#define STARTING_VALUE_SEM 3
#define NUMBER_OF_CHARS 50
#define POSSIBLE_COMMAND_INPUT 4
#define ASCII_INPUTS  256
#define OPEN_ACCESS S_IRWXU

void GetInput(char *input);
void LutInit();
void DecrementSem(sem_t *semaphore, int number, char *undo);
void IncrementSem(sem_t *semaphore, int number, char *undo);
void ViewSem(sem_t *semaphore, int value, char *undo);
void Exit(sem_t *semaphore, int value, char *undo);
void Empty(sem_t *semaphore, int value, char *undo);
void UnLink(sem_t *semaphore, int value, char *undo);

typedef void (*sem_commands)(sem_t *semaphore, int value, char *undo);

int g_exit = 0;
int g_undo_by = 0;
char g_name[NUMBER_OF_CHARS] = {0};

/* lut for accessing commands functions */
static sem_commands arr_commands[ASCII_INPUTS] = {NULL};

int main(int argc, char *argv[])
{
	const char *delim = " ";
	char input[NUMBER_OF_CHARS] = {0};
	char *token = (char*)malloc(NUMBER_OF_CHARS);
	char *command_args[POSSIBLE_COMMAND_INPUT] = {0};
	size_t i = 0;
	sem_t *semaphore =  NULL;
	
	(void)argc;
	
	assert(argv[1]);
	
	/* assign the name to global name variable */
	memcpy(g_name, argv[1], NUMBER_OF_CHARS);
	
	/* create a semaphore and check it was successfully created */
	semaphore = sem_open(g_name, O_CREAT, OPEN_ACCESS, STARTING_VALUE_SEM);
	if (SEM_FAILED == semaphore)
	{
		perror("creating semaphore failed");
		exit(EXIT_FAILURE);
	}
	
	/* initializing the lut */
	LutInit();
	
	while (!g_exit)
	{
		/* get an input from the user */
		GetInput(input);
		
		/* restoring number and undo to defoult */
		command_args[1] = "0";
		command_args[2] = "not undo";
		
		/* spliting the input to tokens */
		token = strtok(input, delim);

		for (i = 0; i < POSSIBLE_COMMAND_INPUT && token != NULL; ++i)
		{
		    command_args[i] = token;
		    token = strtok(NULL, delim);
		}
		
		/* go to the specefied command in the lut*/
		arr_commands[*(unsigned char*)command_args[0]](semaphore,
													   atoi(command_args[1]),
											   		   command_args[2]);
	}
	
	free(token);
	
	return 0;
}


void GetInput(char *input)
{
	printf("\nwrite a command: ");
	
	if (fgets(input, NUMBER_OF_CHARS, stdin) == NULL) 
	{
		perror("geting input failed");
		exit(EXIT_FAILURE);
    }
    /* replacing the \n if there is one with \0 */
	input[strcspn(input,"\n")] = '\0';
}

void LutInit()
{
	size_t i = 0;
	
	for (; i < ASCII_INPUTS; ++i)
	{
		arr_commands[i] = &Empty;
	}
	
	/* assigning the command pointers to the right input */
	arr_commands['D'] = &DecrementSem;
	arr_commands['I'] = &IncrementSem;
	arr_commands['V'] = &ViewSem;
	arr_commands['X'] = &Exit;
	arr_commands['U'] = &UnLink;
}

void DecrementSem(sem_t *semaphore, int number, char *undo)
{
	int increment_by = number;
	
	assert(semaphore);
	
	/* check undo flag and do the opposite operation decr-plus incr-minus  */
	if (0 == strcmp("undo",undo))
	{
		g_undo_by += number;
	}
	
	while (0 < number)
	{
		if (-1 == sem_wait(semaphore))
		{
			perror("decrement failed");
			exit(EXIT_FAILURE);
		}
		
		--number;
	}
	
	printf("dencremented semaphore by %d\n", increment_by);
}

void IncrementSem(sem_t *semaphore, int number, char *undo)
{
	int increment_by = number;
	
	assert(semaphore);
	
	/* check undo flag and do the opposite operation decr-plus incr-minus  */
	if (0 == strcmp("undo",undo))
	{
		g_undo_by -= number;
	}
	
	while (0 < number)
	{
		if (-1 == sem_post(semaphore))
		{
			perror("increment failed");
			exit(EXIT_FAILURE);
		}
		
		--number;
	}
	
	printf("incremented semaphore by %d\n", increment_by);
}

void ViewSem(sem_t *semaphore, int value, char *undo)
{
	(void)undo;
	
	assert(semaphore);
	
	if (-1 == sem_getvalue(semaphore, &value))
	{
		perror("view failed");
		exit(EXIT_FAILURE);
	}
		
	printf("value of semaphore is: %d\n", value);
}

void Exit(sem_t *semaphore, int value, char *undo)
{
	(void)value;
	
	assert(semaphore);
	
	/* undo operations before exiting */	
	if (0 < g_undo_by)
	{
		IncrementSem(semaphore, g_undo_by, undo);
	}
	else if (0 > g_undo_by)
	{
		g_undo_by = (-1) * g_undo_by;
		DecrementSem(semaphore, g_undo_by, undo);
	}
	
	/* close the semaphore without unlinking */
	if (-1 == sem_close(semaphore))
	{
		perror("close failed");
		exit(EXIT_FAILURE);
	}
	
	/* exitng the loop */
	g_exit = 1;
	
	printf("exit the program thank you\n");
}

void UnLink(sem_t *semaphore, int value, char *undo)
{
	(void)value;
	
	assert(semaphore);
	
	/* undo operations before exiting */	
	if (0 < g_undo_by)
	{
		IncrementSem(semaphore, g_undo_by, undo);
	}
	else if (0 > g_undo_by)
	{
		g_undo_by = (-1) * g_undo_by;
		DecrementSem(semaphore, g_undo_by, undo);
	}
	
	/* unlink the semaphore */
	if (-1 == sem_unlink(g_name))
	{
		perror("unlink failed");
		exit(EXIT_FAILURE);
	}
	
	/* exitng the loop */
	g_exit = 1;
	
	printf("exit the program thank you\n");
}

void Empty(sem_t *semaphore, int value, char *undo)
{
	(void)undo;
	(void)value;
	(void)semaphore;
	
	printf("please enter a valid command...\n"
		   "D (decrement), I (increment), V (view), X (exit), U (unlink)\n");
}
















