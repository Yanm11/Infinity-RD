#include <stdio.h> /* printf perror fgets fopen fseek fclose fputs remove*/
#include <stdlib.h> /* exit */
#include <string.h> /* strlen strncmp strcspn*/


#define SIZE 5


static int FLAG = 1;
typedef void (*ptr_func_v)(char *, char *);
typedef int (*ptr_func_i)(char *, char *, int);
typedef struct special
{
  char *s;
  ptr_func_i comp;
  ptr_func_v op;
}special_arr;


int StartProgram(char *name, special_arr arr[]);
int Compare(char *s1, char *s2, int len);
void Remove(char *file_name, char *line);
void Count(char *file_name, char *line);
void Exit(char *file_name, char *line);
void WriteStart(char *file_name, char *line);
void Write(char *file_name, char *line);


int main(void)
{
	char file_name[50];
	special_arr arr[SIZE] = {{"-remove", &Compare, &Remove},\
						     {"-count", &Compare, &Count}, \
					         {"-exit", &Compare, &Exit},\
					         {"<", &Compare, &WriteStart},\
					         {"", &Compare, &Write}};
	
	printf("write the name of a file\n");
	
	if (fgets(file_name,50 , stdin) == NULL)
	{
		perror("Error geting input");
		return(-1);
     }
    
    file_name[strcspn(file_name,"\n")] = 0;
    
	printf("start writing:\n");
	
	while (FLAG)
	{
		StartProgram(file_name, arr);
	}
	return 0;
}


int StartProgram(char *name, special_arr arr[])
{
	int i = 0;
	char line[100];

	if (fgets(line, 100, stdin) == NULL)
	{
		perror("Error getting input");
		return(-1);
     }
     
	line[strcspn(line,"\n")] = 0;
	
	for (; i < SIZE; i++)
	{
		if (arr[i].comp(line, arr[i].s,strlen(arr[i].s)) == 0)
		{
			arr[i].op(name, line);
			break;
		}
		else if (i == SIZE -1)
		{
			arr[i].op(name,line);
		}
	}
	return 0;
}


int Compare(char *s1, char *s2, int len)
{
	return strncmp(s1, s2, len);
}


void Remove(char *file_name, char *line)
{
	remove(file_name);
}


void Count(char *file_name, char *line)
{
	FILE *fp = fopen(file_name, "a+");
	int counter = 0;
	char raw[100];
	
	/* error handling */
	if (!fp)
	{
		printf("error with file");
		exit(0);
	}
	
	while (fgets(raw, 100, fp) != NULL)
	{
		++counter;
	}	
	printf("Number of lines written in the file is: %d\n", counter);
		
	fclose(fp);
}


void Exit(char *file_name, char *line)
{
	FLAG = 0;
}


void WriteStart(char *file_name, char *line)
{
	FILE *fp = fopen(file_name,"r+");
	
	/* error handling */
	if (!fp)
	{
		fp = fopen(file_name,"w+");
		if(!fp)
		{
			printf("error with file");
			exit(0);
		}
	}
	
	fseek(fp, 0L, SEEK_SET);
	++line;
	fputs(line,fp);
	fputs("\n",fp);
	fclose(fp);
}


void Write(char *file_name, char *line)
{
	FILE *fp = fopen(file_name,"a");
	
	/* error handling */
	if (!fp)
	{
		printf("error with file");
		exit(0);
	}
	fputs(line,fp);
	fputs("\n",fp);
	fclose(fp);		
}


























