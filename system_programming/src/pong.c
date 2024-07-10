#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */


/*Signal handler function */
void handle_sigusr2(int sig) 
{
	(void)sig;
    printf("Pong\n");
    sleep(1);
    kill(getppid(), SIGUSR1);
}

int main(void)
{
	struct sigaction sa = {0};

	sa.sa_handler = handle_sigusr2;
	
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	kill(getppid(), SIGUSR1);
	
	while (1)
	{
		pause();	
	}
	
	return 0;
}
