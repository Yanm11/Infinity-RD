#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> /* waitpd pid_t */

#define NUMBER_OF_CHARS 50

/*Signal handler function */
void handle_sigusr2(int sig, siginfo_t *siginfo, void *context)
{
	(void)sig;
	(void)context;
    printf("Pong\n");
    sleep(1);
    kill(siginfo->si_pid, SIGUSR1);
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
		pause();	
	}
	
	return 0;
}
