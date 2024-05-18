#include <stdio.h> /* printf perror fgets fopen fseek fclose fputs remove*/
#include <stdlib.h> /* exit */
#include <string.h> /* strlen strncmp strcspn*/

#include "ws5.h"

#define SIZE 5
#define line_size 100

int Ex1()
{
	print_me arr[10];
	int i = 0;
	for (;i < 10; i++)
	{
		arr[i].i = i;
		arr[i].p = &Print;
	}
	
	for (i = 0; i < 10; i++)
	{
		arr[i].p(arr[i].i);
	}
	
	return 0;
}

void Print(int x)
{
	printf("%d\n", x);
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
	(void)line;
	
	return result;
}


enum return_type Count(char *file_name, char *line)
{
	FILE *fp = fopen(file_name, "a+");
	int counter = 0;
	char raw[line_size];
	enum return_type result = success;
	
	(void)line;
	
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
	
	(void)file_name;
	(void)line;
	
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
