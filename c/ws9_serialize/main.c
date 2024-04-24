#include <stdio.h> /* printf sizeof */
#include "students.h"

int test(student_t student1, student_t student2);

int main(void)
{
	real_t real_grades;
	humanistic_t humanistic_grades;
	grade_t grade;
	student_t gal;
	student_t yan;
	
	/* writing gals grades */
	real_grades.math = 90.0;
	real_grades.physics = 87.4;
	real_grades.cs = 85.6;
	real_grades.biology = 89.0;
	
	humanistic_grades.sociology = 85.6;
	humanistic_grades.psychology = 100.0;
	humanistic_grades.literature = 88.3;
	humanistic_grades.art = 100;
	
	grade.humanistics = humanistic_grades;
	grade.reals = real_grades;
	grade.sports = 56.8;
	
	gal.first_name = "Galgtrhgrthrhryh";
	gal.last_name = "Manor";
	gal.grades = grade;
	
	/* writing yans to check if they change */
	real_grades.math = 45;
	real_grades.physics = 45;
	real_grades.cs = 45;
	real_grades.biology = 45;
	
	humanistic_grades.sociology = 48;
	humanistic_grades.psychology = 84;
	humanistic_grades.literature = 48;
	humanistic_grades.art = 48;
	
	grade.humanistics = humanistic_grades;
	grade.reals = real_grades;
	grade.sports = 100.8;
	
	yan.first_name = "Ya";
	yan.last_name = "Meiri";
	yan.grades = grade;
	
	test(gal, yan);
	
	SaveStudent(&gal, "test.bin");
	LoadStudent(&yan, "test.bin");
	
	test(gal, yan);
	
	return 0;
}


int test(student_t student1, student_t student2)
{
	int result = 0;
	
	result += (student1.first_name == student2.first_name); 
	result += (student1.last_name == student2.last_name); 
	
	result += (student1.grades.reals.math == student2.grades.reals.math); 
	result += (student1.grades.reals.physics == student2.grades.reals.physics);
	result += (student1.grades.reals.cs == student2.grades.reals.cs);
	result += (student1.grades.reals.biology == student2.grades.reals.biology);
	
	result += (student1.grades.humanistics.sociology == student2.grades.humanistics.sociology);
	result += (student1.grades.humanistics.psychology == student2.grades.humanistics.psychology);
	result += (student1.grades.humanistics.literature == student2.grades.humanistics.literature);	
	result += (student1.grades.humanistics.art == student2.grades.humanistics.art);
	
	result += (student1.grades.sports == student2.grades.sports);
	
	if (result == 11)
	{
		printf("Pass the test all the fields match\n");
		return 0;
	}
	
	printf("Didn't pass the test some fields are not the same\n");
	return 0;
}
