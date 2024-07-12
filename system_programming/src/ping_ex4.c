#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

static volatile int g_flag = 0;
static volatile pid_t g_pid = 0;

/*Signal handler function */
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;
	
    g_flag = 1;
	g_pid = siginfo->si_pid;
}

int main(void)
{
	struct sigaction sa = {0};
	
	sa.sa_sigaction = handle_sigusr1;
	sa.sa_flags = SA_SIGINFO;
	 
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	printf("pid: %d\n", getpid());
	
	while (1)
	{
		if (g_flag)
		{
			g_flag = 0;
			
			printf("Ping\n");
			sleep(1);
			if (kill(g_pid, SIGUSR2) == -1)
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
