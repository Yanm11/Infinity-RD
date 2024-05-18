#include <stdio.h> /* printf sizeof fopen fwrite fread fclose */
#include <stdlib.h> /* exit */
#include "students.h"

void SaveStudent(student_t *student, char *file_name)
{
	FILE *fb;
	
	fb = fopen(file_name,"wb");
	
	if (NULL == fb)
	{
		printf("error with file name\n");
		exit(-1);
	}
	
	fwrite(student, sizeof(student_t), 1, fb);
	
	fclose(fb);
} 


void LoadStudent(student_t *student, char *file_name)
{
	FILE *fb;
	
	fb = fopen(file_name,"rb");
	
	if (NULL == fb)
	{
		printf("error with file name\n");
		exit(-1);
	}
	
	fread(student, sizeof(student_t), 1, fb);
	
	fclose(fb);
}
