#include <stdio.h> /* printf */
#include <assert.h> /* assert */
	
#include "calculator.h"

void TestCalc(void);


static int checker = 0;


int main(void)
{
	TestCalc();

	
	if (checker)
	{
		printf("In Total Failed %d Tests\n", checker);
		return 0;
	}
	
	printf("\nPASSED ALL TESTS!!!!!\n");
	
	return 0;
}

void TestCalc(void)
{
	const char *equation = "7+8";
	double expected_result = 15;
	double result = 0;
	e_status_t expected_status = CALC_SUCCESS;
	e_status_t status = 0;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 1\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n", status, expected_status);
		
		++checker;
	}
	else
  	{
  		printf("PASSED testcalc 1\n\n");
  	}
  	
  	equation = "8+8*3+-2^5";
	expected_result = 0;
	expected_status = CALC_SUCCESS;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 2\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n", status, expected_status);
		
		++checker;
	}
	else
  	{
  		printf("PASSED testcalc 2\n\n");
  	}
  	
	equation = "8+8*3-2^";
	expected_result = 0;
	expected_status = CALC_SYNTAX_ERROR;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 3\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
		
		++checker;
	}
	else
  	{
  		printf("PASSED testcalc 3\n\n");
  	}
  	
	equation = "2/0";
	expected_result = 0;
	expected_status = CALC_MATH_ERROR;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 4\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}
	else
  	{
  		printf("PASSED testcalc 4\n\n");
  	}
  	
	equation = "8++8*((3-2)*5)";
	expected_result = 48;
	expected_status = CALC_SUCCESS;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 5\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}	
    else
  	{
  		printf("PASSED testcalc 5\n\n");
  	}
  	 
	equation = "9-2)*5";
	expected_result = 0;
	expected_status = CALC_SYNTAX_ERROR;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 6\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}   
	else
  	{
  		printf("PASSED testcalc 6\n\n");
  	} 
  	
	equation = "(3-2)*5+ 5*(4+4+4";
	expected_result = 0;
	expected_status = CALC_SYNTAX_ERROR;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 7\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}  
	else
  	{
  		printf("PASSED testcalc 7\n\n");
  	}
  	
	equation = "4-3-2-1\n";
	expected_result = -2;
	expected_status = CALC_SUCCESS;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 8\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}
  	else
  	{
  		printf("PASSED testcalc 8\n\n");
  	}
  	
	equation = "4^3^2^1\n";
	expected_result = 262144;
	expected_status = CALC_SUCCESS;
	
	status = Calculate(equation, &result);
	
	if (expected_result != result || expected_status != status)
	{
		printf("Failed testcalc 9\n");
		printf("got result: %f\nexpected: %f\n", result, expected_result);
		printf("got status: %d\nexpected: %d\n\n", status, expected_status);
				
		++checker;
	}
	else
  	{
  		printf("PASSED testcalc 9\n\n");
  	}
}

