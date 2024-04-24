#include <stdio.h> /* printf sizeof */
#include <stdlib.h> /* realloc free */
#include <string.h> /* strlen */
#include <assert.h> /* assert */
#include "students.h"

void SaveStudent(student_t *student, char *file_name)
{
	FILE *fb;
	
	fb = fopen(file_name,"wb");
	
	assert(NULL != fb);
	
	fwrite(student, sizeof(student_t), 1, fb);
	
	fclose(fb);
} 


void LoadStudent(student_t *student, char *file_name)
{
	FILE *fb;
	
	fb = fopen(file_name,"rb");
	
	assert(NULL != fb);
	
	fread(student, sizeof(student_t), 1, fb);
	
	fclose(fb);
}
