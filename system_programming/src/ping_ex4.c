#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

/*Signal handler function */
void handle_sigusr1(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;
	
    printf("Ping\n");
    sleep(1);
    kill(siginfo->si_pid, SIGUSR2);
}

int main(void)
{
	struct sigaction sa = {0};
	
	sa.sa_sigaction= handle_sigusr1;
	sa.sa_flags = SA_SIGINFO;
	 
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	printf("pid: %d\n", getpid());
	
	
	while (1)
	{	
		pause();
	}
	
	return 0;
}
