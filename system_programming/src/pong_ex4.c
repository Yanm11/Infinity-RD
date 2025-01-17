/* approved by yarden */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /* printf */
#include <stdlib.h> /* EXIT_FAILURE exit */
#include <signal.h> /* sigemptyset sigaction */
#include <unistd.h>	/* sleep */
#include <sys/wait.h> /* waitpd pid_t */
#include <string.h> /* strcspn */

#define NUMBER_OF_CHARS 50

static volatile int g_flag = 0;
static volatile pid_t g_pid = 0;

/*Signal handler function */
void HandleSigusr2(int sig, siginfo_t *siginfo, void *context)
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
	
	sa.sa_sigaction = HandleSigusr2;
	sa.sa_flags = SA_SIGINFO;
	
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	/* sending the first signal */
	if (kill((pid_t)atoi(pid_word), SIGUSR1) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
	
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
