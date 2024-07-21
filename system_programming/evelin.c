/*
Requirements: Compile with: cc -pthread (link against real-time library, librt)
Description: this program mimics the advanced features of a System V Semaphore for IPC (for inter-process synchronization)
, using POSIX Semaphore methods.
(creates a semaphore of a given name, and allows manipulation of it from the command line.)
CLI Arguments: 
*/

#include <semaphore.h>        /* POSIX semaphores functions */
#include <fcntl.h>            /* oflag of sem_open, for O_constants*/
#include <stdio.h>            /* perror */
#include <assert.h>           /* assert */
#include <stdlib.h>           /* atoi */
#include <string.h>           /* strcspn, strtok */

#define ASCII_RANGE 128
#define INPUT_BUFFER_MAX 100

typedef enum status
{
	COMMAND_FAILURE = -1,
	INPUT_FAILURE = -2,
	SUCCESS = 0,
	EXIT = 1
}status_e;

typedef struct command_params
{
	char command;
	int num;
}command_params_t;

typedef status_e (*action_func)(sem_t* sem, int num);


static action_func g_prog_actions[ASCII_RANGE] = {0}; /*a LUT of the program actions */
int g_was_init = 0; /* was commands LUT init? */
int g_undo = 0; /* set to 0< to increment when undone, 0> to decrement */


/*******************************************************************************
                               FUNCTIONS DECLARATIONS
*******************************************************************************/
static status_e SemIncrement(sem_t *sem, int num);
static status_e SemDecrement(sem_t *sem, int num);
static status_e SemView(sem_t *sem, int num);
static status_e SemExit(sem_t *sem, int num);
static status_e DoNothing(sem_t *sem, int num);

static void InitProgActions(void);
static void GetUserCommands(command_params_t *command_params);
/*******************************************************************************
                                      MAIN
*******************************************************************************/

int main(int argc, char *argv[])
{
	status_e status = SUCCESS;
	sem_t *sem = NULL;
	command_params_t command_params = {0};

	if (!g_was_init) /* init commands LUT */
	{
		InitProgActions();
	}

/* Check for correct semaphore name */
	if (argc < 2) /* No name parameter was passed */
	{
		perror("No semaphore was named. Exiting.\n");
		return INPUT_FAILURE;
	}

	if (NULL == sem) /* Create named semaphore */
	{
		sem = sem_open(argv[1], O_CREAT | O_EXCL); // if you put o_creat additional 2 arguments need to be passed (mode and initial value)
		if (NULL == sem)
		{
			perror("Semaphore with this name already exists. Exiting.\n");
			return INPUT_FAILURE;
		}
	}

/* Run semaphore commands*/
	while (SUCCESS == status)
	{	
		command_params.num = 0;
		command_params.command = 0;
	
		/* Get commands from user */
		GetUserCommands(&command_params);
			/* Run the required command*/
		g_prog_actions[(int)command_params.command](sem, command_params.num); // run forever becuase you dont actually change status
	}

	if (EXIT == status)
	{
		return SUCCESS;
	}

	return status;
}


/*******************************************************************************
                         SEM MANIPULATION FUNCTIONS
*******************************************************************************/

static status_e SemIncrement(sem_t *sem, int num)
{
	status_e status = SUCCESS;
	assert(NULL != sem);

	while (0 != num) /* increment sem x times */
	{
		status = sem_post(sem);
		if (SUCCESS!= status) /* COMMAND_FAILUREs unrelated to sem value */
		{
			perror("Couldn't increment the semaphore\n");

			return COMMAND_FAILURE;
		}
		--num;
	}
	return status;
}

/* Decrement the value by num*/
static status_e SemDecrement(sem_t *sem, int num)
{
	int status = SUCCESS;
	assert(NULL != sem);

	while (0 != num) /* decrement sem x times */
	{
		status = sem_wait(sem); /* sem_wait handles 'race conditions' */
		if (SUCCESS != status) /* COMMAND_FAILUREs unrelated to sem value */
		{
			perror("Couldn't decrement the semaphore\n"); 

			return COMMAND_FAILURE;
		}
		--num;
	}
	return status;
}

static status_e SemView(sem_t *sem, int num)
{
	status_e status = SUCCESS;
	int sval = 0;
	(void)num;

	assert(NULL != sem);

	status = sem_getvalue(sem, &sval);
	if (SUCCESS != status) /* COMMAND_FAILUREs unrelated to sem value */
	{
		perror("Couldn't get the semaphore value\n"); 

		return COMMAND_FAILURE;
	}

	fprintf(stdout, "Sem value is: %d\n", sval);	

	return status;
}

static status_e SemExit(sem_t *sem, int num) /* run if proc exits sem_manipulation */
{
	(void)num;
	assert(NULL != sem);
	
	// not sure about the logic here gor undo  i think it should be opposite 
	// if i do D 3 undo the undo should be increment by 3 here you will decrement again by -3
	if (0 < g_undo)
	{
		SemIncrement(sem, g_undo);
	}
	else if (0 > g_undo)
	{
		SemDecrement(sem, g_undo); // g_undo here is minus and then it will run forever in the loop
	}

	sem_close(sem); /* release the semaphore */ // can fail
	g_undo = 0;
	fprintf(stdout, "Semaphore released and cleaned up. \n");

	return EXIT;
}

static status_e DoNothing(sem_t *sem, int num) /* for non-existing commands */
{
	(void)sem;
	(void)num;

	fprintf(stdout, "Unknown command, Try again.\n");

	return SUCCESS;
}

/*******************************************************************************
                               UTILITIES FUNCTIONS
*******************************************************************************/

static void InitProgActions(void)
{
	size_t i = 0;

	for (; i < ASCII_RANGE; ++i)
	{
		g_prog_actions[i] = &DoNothing;
	}

	g_prog_actions['D'] = &SemDecrement;
	g_prog_actions['d'] = &SemDecrement;

	g_prog_actions['I'] = &SemIncrement;
	g_prog_actions['i'] = &SemIncrement; 

	g_prog_actions['V'] = &SemView;
	g_prog_actions['v'] = &SemView;

	g_prog_actions['X'] = &SemExit;
	g_prog_actions['x'] = &SemExit; 
}

static void GetUserCommands(command_params_t *command_params)
{
	char command_str[INPUT_BUFFER_MAX] = {0};
	char *command_and_args[INPUT_BUFFER_MAX] = {0};
	char *command_str_rslt = NULL;
	char *token = NULL;
	size_t i = 0;

	/* Get commands str*/
	command_str_rslt = fgets(command_str, sizeof(command_str), stdin); // fgets can fail how do you handle it?
	if (NULL != command_str_rslt)
	{
		command_str[strcspn(command_str, "\n")] = '\0'; /*replace \n with \0*/

		/* Parse the string as command and args strings*/
		i = 0;
		token = strtok(command_str, " ");
		while(NULL != token)
		{
			command_and_args[i] = token;
			token = strtok(NULL, " ");
			++i;
		}
		command_and_args[i] = NULL; // seems unnaccary

		/* Parse the command and args as their data types */
		command_params->command = *(command_and_args[0]); /* get char command */
		if (1 < i)
		{
			command_params->num = atoi(command_and_args[1]); /* get num to I/D */
		}
		if ((2 < i) && (0 == strcmp(command_and_args[2], "undo")))
		{
			g_undo = command_params->num; /* get if undo */ /*set to pos or neg */

			if ('D' == command_params->command || 'd' == command_params->command) // look at exit
			{
				g_undo *= -1; 
			}
		}
	}
}

