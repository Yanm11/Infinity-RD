#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

pid_t g_pid = 0;

/*Signal handler function */
void handle_sigusr1(int sig) 
{
	(void)sig;
    printf("Ping\n");
    sleep(1);
    kill(g_pid, SIGUSR2);
}

int main(void)
{
	struct sigaction sa = {0};
	
	char *args[] = {"./bin/debug/pong", NULL};
	
	sa.sa_handler = handle_sigusr1;
	
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
    	perror("sigaction");
    	exit(EXIT_FAILURE);
	}
	
	g_pid = fork();
	
	printf("pid: %d\n", g_pid);
	
	if (0 > g_pid) 
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (g_pid == 0) 
	{
	 	execvp(args[0], args);
	 	
	 	/* happen only when execvp fails */
	 	perror("execvp failed");
		exit(EXIT_FAILURE);
	}
	
	while (1)
	{	
		pause();
	}
	
	return 0;
}
