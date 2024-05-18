#ifndef __WS5__h_
#define __WS5__h_

void Print(int x);

typedef void (*ptr_func)(int);
typedef struct print_me
{
  int i;
  ptr_func p;
} print_me;

int Ex1();


#define SIZE 5
#define line_size 100

static int FLAG = 1;
enum return_type{success};
typedef enum return_type (*ptr_func_v)(char *, char *);
typedef int (*ptr_func_i)(char *, char *, int);
typedef struct special
{
  char *s;
  ptr_func_i comp;
  ptr_func_v op;
}special_arr;


int StartProgram(char *name, special_arr arr[]);
int Compare(char *s1, char *s2, int len);
enum return_type Remove(char *file_name, char *line);
enum return_type Count(char *file_name, char *line);
enum return_type Exit(char *file_name, char *line);
enum return_type WriteStart(char *file_name, char *line);
enum return_type Write(char *file_name, char *line);



#endif
