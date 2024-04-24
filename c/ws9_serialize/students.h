#ifndef __STUDENTS_H__
#define __STUDENTS_H__

typedef struct real
{
	float math;
	float physics;
	float cs;
	float biology;
} real_t;

typedef struct humanistic
{
	float sociology;
	float psychology;
	float literature;
	float art;
	
} humanistic_t;

typedef struct grade
{
	humanistic_t humanistics;
	real_t reals;
	float sports;
	
} grade_t;

typedef struct student
{
	char *first_name;
	char *last_name;
	grade_t grades;
} student_t;


void LoadStudent(student_t *student, char *file_name);
void SaveStudent(student_t *student, char *file_name);
#endif
