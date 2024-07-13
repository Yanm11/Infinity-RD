/* approved by yarden */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_FAILURE exit */
#include <signal.h> /* sigemptyset sigaction */
#include <unistd.h>	/* sleep */
#include <sys/wait.h> /* waitpd pid_t */

void Loop(pid_t pid, int sig, const char print_word[]);

static volatile int g_flag = 0;

/*Signal handler function */
void HandleSigusr(int sig) 
{
	(void)sig;
	g_flag = 1;
}

int main(void)
{
	struct sigaction sa = {0};
	struct sigaction sa_prev = {0};
	pid_t pid = 0;
	
	sa.sa_handler = HandleSigusr;
	sa.sa_flags = 0; 
	sigemptyset(&sa.sa_mask); /* empty mask */

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	pid = fork();

	if (0 > pid) 
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) /*** CHILD ***/
	{
	 	Loop(getppid(), SIGUSR2, "Ping");
	}
	
	else /*** PARENT ***/
	{	
		/* return SIGUSR1 to defoult */
		if (sigaction(SIGUSR1, &sa_prev, NULL) == -1)
		{
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		/* handle SIGUSR2 */
		if (sigaction(SIGUSR2, &sa, NULL) == -1)
		{
			perror("sigaction");
			exit(EXIT_FAILURE);
		}
		
		/* initiate the ping pong */
		if (kill(pid, SIGUSR1) == -1)
		{
			perror("kill");
			exit(EXIT_FAILURE);
		}
		
		/* loop forever replying Pong to Ping */
		Loop(pid, SIGUSR1, "Pong\n");
	}
	
	return 0;
}


void Loop(pid_t pid, int sig, const char print_word[])
{
	while (1)
	{
		if (g_flag)
		{
			g_flag = 0;
			
			printf("%s\n", print_word);
			sleep(1);
			if (kill(pid, sig) == -1)
			{
				perror("kill");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			sleep(10);
		}
	}
}

