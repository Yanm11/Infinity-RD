#include <stdio.h> /* printf perror fgets fopen fseek fclose fputs remove*/
#include <stdlib.h> /* exit */
#include <string.h> /* strlen strncmp strcspn*/


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


int main(void)
{
	char file_name[line_size];
	special_arr arr[SIZE] = {{"-remove", &Compare, &Remove},\
						     {"-count", &Compare, &Count}, \
					         {"-exit", &Compare, &Exit},\
					         {"<", &Compare, &WriteStart},\
					         {"", &Compare, &Write}};
	
	printf("write the name of a file\n");
	
	if (fgets(file_name,line_size , stdin) == NULL)
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
	char line[line_size];

	if (fgets(line, line_size, stdin) == NULL)
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


enum return_type Remove(char *file_name, char *line)
{
	enum return_type result = success;
	remove(file_name);
	
	return result;
}


enum return_type Count(char *file_name, char *line)
{
	FILE *fp = fopen(file_name, "a+");
	int counter = 0;
	char raw[line_size];
	enum return_type result = success;
	
	/* error handling */
	if (!fp)
	{
		printf("error with file");
		exit(0);
	}
	
	while (fgets(raw, line_size, fp) != NULL)
	{
		++counter;
	}	
	printf("Number of lines written in the file is: %d\n", counter);
		
	fclose(fp);
	
	return result;
}


enum return_type Exit(char *file_name, char *line)
{
	enum return_type result = success;
	FLAG = 0;
	
	return result;
}


enum return_type WriteStart(char *file_name, char *line)
{
	enum return_type result = success;
	
	FILE *fp = fopen(file_name,"r+");
	FILE *cp = fopen("copy.txt","w");
	char raw[line_size];
	
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
	
	/* copy file */
	while (fgets(raw, line_size, fp) != NULL)
	{
		fputs(raw,cp);
	}
		
	fclose(cp);
	fclose(fp);
	
	fp = fopen(file_name,"w+");
	cp = fopen("copy.txt","r");
	
	++line;
	fputs(line,fp);
	fputs("\n",fp);
	
	/* copy file */
	while (fgets(raw, line_size, cp) != NULL)
	{
		fputs(raw,fp);
	}
	
	fclose(fp);
	fclose(cp);
	remove("copy.txt");

	return result;
}


enum return_type Write(char *file_name, char *line)
{
	enum return_type result = success;
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
		
	return result;
}


























