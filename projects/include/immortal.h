#ifndef __IMMORTAL_H__
#define __IMMORTAL_H__

#define FAILED -1
#define SUCCESS 0
#define SEM_NAME "watchdog"
#define STARTING_VALUE_SEM 0
#define SEM_PERMITIONS (S_IRWXU | S_IRWXG | S_IRWXO)
#define INTERVAL_INDEX 1
#define REPS_INDEX 2
#define ENV_NAME "WD_PID"

#include <time.h> /* time_t */
#include <sys/wait.h> /*  pid_t */
#include <semaphore.h>

extern sem_t *g_semaphore_thread_2_wd;

void HandlerSig1(int sig);
void HandlerSig2(int sig);
void *Immortal(void *imortal_ptr);
pid_t CreateChildProcess(char *args[]);
void RaiseCounter(void *word);
void CheckIfAlive(void *args);
void CheckIfDNR(void *scheduler);
int MaskSignal(int sig, int sig_block);
int SignalInit(struct sigaction *sa, struct sigaction *sa_prev, int sig);
void SetEnvVarInt(const char *name, int value); 
size_t StrToSizeT(const char *str);
void CleanUp(hscheduler_t *scheduler, 
			 struct sigaction *sa_1_prev,
			 struct sigaction *sa_2_prev);
void *ErrorHandling(hscheduler_t *scheduler, 
				    struct sigaction *sa_1_prev,
				    struct sigaction *sa_2_prev);

#endif /*__IMMORTAL_H__ */