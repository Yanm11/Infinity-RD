#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

void Loop(pid_t pid, int sig, const char print_word[]);

static volatile int g_flag = 0;

/*Signal handler function */
void handle_sigusr2(int sig) 
{
	(void)sig;
	g_flag = 1;
}

int main(void)
{
	struct sigaction sa = {0};

	sa.sa_handler = handle_sigusr2;
	/* handle SIGUSR2 */
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	/* sent the first signal to start infinate loop */
	kill(getppid(), SIGUSR1);
	
	Loop(getppid(), SIGUSR1, "Pong\n");
	
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
