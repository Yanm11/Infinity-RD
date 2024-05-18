#ifndef __WS3__h_
#define __WS3__h_

#define ROWS 4
#define COLS 4

void func(int array[ROWS][COLS], int arr[]);
int Josephus(int n);
void Memory(char **env, int num_env_var);
void ToLower(char *str);

extern char **environ;

#endif

