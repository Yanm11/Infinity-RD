#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

#define NUMBER_OF_CHARS 50

static volatile int g_flag = 0;
static volatile pid_t g_pid = 0;

/*Signal handler function */
void handle_sigusr2(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;
	
    g_flag = 1;
	g_pid = siginfo->si_pid;
}

int main(void)
{
	struct sigaction sa = {0};
	char pid_word[NUMBER_OF_CHARS] = {0};
	
	printf("enter ping PID: \n");
	fgets(pid_word, NUMBER_OF_CHARS, stdin);
	pid_word[strcspn(pid_word,"\n")] = '\0';
	
	sa.sa_sigaction = handle_sigusr2;
	sa.sa_flags = SA_SIGINFO;
	
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	kill((pid_t)atoi(pid_word), SIGUSR1);
	
	while (1)
	{
		if (g_flag)
		{
			g_flag = 0;
			
			printf("Pong\n\n");
			sleep(1);
			if (kill(g_pid, SIGUSR1) == -1)
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
	
	return 0;
}
