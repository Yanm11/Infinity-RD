#include <stdio.h> /* printf */
#include <stdlib.h> /* malooc free */
#include <string.h> /* strcmp strcspn */
#include <unistd.h> /* fork */
#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* waitpd */

#define NUMBER_OF_CHARS 50

void SystemState(void);
void ForkState(void);
void GetInput(char *input);

int main(void)
{
    char state[NUMBER_OF_CHARS] = {0};
    char fork_word[] = "fork";
    char system_word[] = "system";

    
    printf("fork or system: ");
	fgets(state, NUMBER_OF_CHARS, stdin);
	state[strcspn(state,"\n")] = '\0';
	printf("\n");
   
	if (!strcmp(state, fork_word))
	{
		 ForkState();
	}
	else if (!strcmp(state, system_word))
	{
		SystemState();
	}
	else
	{
		printf("please enter either fork or system\n");
	}
	
	return 0;
}

void SystemState(void)
{
	char input[NUMBER_OF_CHARS] = {0};
    char exit_word[] = "exit";
    
    while (0 != strcmp(input, exit_word))
    {
		GetInput(input);
		
		system(input);
    }
}


void ForkState(void)
{
    char input[NUMBER_OF_CHARS] = {0};
    char *args[NUMBER_OF_CHARS] = {0};
    char *token = (char*)malloc(NUMBER_OF_CHARS);
    int arg_count = 0;
    char exit_word[] = "exit";
    pid_t pid = 0;
    
    GetInput(input);
    
    while (0 != strcmp(input, exit_word))
    {
		char input_copy[NUMBER_OF_CHARS] = {0};
		
    	arg_count = 0;
		
		strcpy(input_copy, input);
		token = strtok(input_copy, " ");

		while (token != NULL) 
		{
		    args[arg_count] = token;
		    token = strtok(NULL, " ");
		    ++arg_count;
		}
		
		args[arg_count] = NULL; 
		
		pid = fork();
		if (0 > pid) 
		{
			perror("fork failed");
	    	exit(EXIT_FAILURE);
		}
		else if (pid == 0) 
		{
	     	execvp(args[0], args);
	     	
	     	/* happen only when execvp fails */
	     	perror("execvp failed");
        	exit(EXIT_FAILURE);
		}
		else 
		{
			int status = 0;
	    	(void)waitpid(pid, &status, 0);
	    }
	    
	    GetInput(input);
    }
}

void GetInput(char *input)
{
	printf("\nwrite a command: ");
	fgets(input, NUMBER_OF_CHARS, stdin);
	input[strcspn(input,"\n")] = '\0';
	printf("\n");
}
