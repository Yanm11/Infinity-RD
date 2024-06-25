#include <stdlib.h> /* malloc free size_t */
#include <string.h> /* strlen */
#include <math.h> /* pow */

#include "stack.h"
#include "calculator.h"

#define NUM_OF_STATE (sizeof(e_state_t))
#define NUM_OF_INPUTS (256)
#define CHAR_TO_UCHAR(c) ((unsigned char)c)
#define CHARP_TO_UCHAR(c) (*(unsigned char*)c)
#define DUMMY 11

/*init functions */
static void FSMInitialize(void);
static void OperatorInitialize(void);

/*handler functions */
static char *HandleNullTerminator(stack_t *operator_stack,
								 stack_t *digit_stack,
						   		 char *expression);
static char *HandleDigit(stack_t *operator_stack,
						stack_t *digit_stack,
						char *expression);
static char *HandleOperator(stack_t *operator_stack,
						   stack_t *digit_stack,
						   char *expression);
static char *HandleError(stack_t *operator_stack,
						stack_t *digit_stack,
						char *expression);
static char *HandleSpace(stack_t *operator_stack,
						 stack_t *digit_stack,
						 char *expression);
static char *HandleCloseParacentesis(stack_t *operator_stack,
						 			 stack_t *digit_stack,
						 			 char *expression);
static char *HandleOpenParacentesis(stack_t *operator_stack,
						 			stack_t *digit_stack,
						 			char *expression);
static char *HandlePow(stack_t *operator_stack,
					   stack_t *digit_stack,
					   char *expression);
static void ExecuteOperation(stack_t *operator_stack,
							 stack_t *digit_stack,
						   	 int priority);
static void ExecuteEquation(char operator, stack_t *digit_stack);
					   
/*operation functions */
static double PlusOperation(double num1, double num2);
static double SubOperation(double num1, double num2);
static double MultiOperation(double num1, double num2);
static double DivOperation(double num1, double num2);
static double PowOperation(double num1, double num2);
static double DummyOperation(double num1, double num2);
					   
typedef enum 
{
	ERROR,
    WAIT_DIGIT,
    WAIT_OPERATOR
} e_state_t;

typedef struct transition
{
    e_state_t next_state;
    char* (*handler)();
} transition_t;

typedef struct operator
{
    int priority;
    double (*operation)(double, double);
} operator_t;


/* LUT fsm and operator decleration */
static transition_t fsm[NUM_OF_STATE][NUM_OF_INPUTS];
static operator_t operators[NUM_OF_INPUTS];

/* global variables decleration */
static int FLAG = 1;
static e_status_t STATUS = CALC_SUCCESS;

/********************************* API FUNCTIONS *************************/
e_status_t Calculate(const char *expression, double *result)
{
	char *next_str = NULL;
	char dummy = (char)DUMMY;
	
	e_state_t current_state = WAIT_DIGIT;
	transition_t tranistion = {0};
	
	/* creating the 2 stacks */
	stack_t *operator_stack = StackCreate(strlen(expression),sizeof(char));
	stack_t *digit_stack = StackCreate(strlen(expression),sizeof(double));
	if (NULL == digit_stack || NULL == operator_stack)
	{
		return CALC_COMPUTER_ERROR;
	}

	assert(result);
	assert(expression);
	
	/* inserting the dummy operator */
	StackPush(operator_stack, &dummy);
	
	/* initializing the LUTs */
	FSMInitialize();
	OperatorInitialize();
	
	/* initializing the global variables */
	FLAG = 1;
	STATUS = CALC_SUCCESS;
	
	next_str = (char*)expression;

	while (FLAG)
	{
		tranistion = fsm[current_state][CHARP_TO_UCHAR(next_str)];
		current_state = tranistion.next_state;
		next_str = tranistion.handler(operator_stack, digit_stack, next_str);
	}
	
	*result = *(double*)StackPeek(digit_stack);
	
	StackDestroy(operator_stack);
	StackDestroy(digit_stack);
	
	return STATUS;
}

/********************************* INIT FUNCTIONS *************************/

static void FSMInitialize(void)
{
	size_t i = 0;
	size_t j = 0;
	size_t digits = 10;
	
	transition_t invalid_transition = {ERROR, HandleError};
	transition_t digit_transition = {WAIT_OPERATOR, HandleDigit};
	transition_t null_terminator_transition = {WAIT_OPERATOR,
											   HandleNullTerminator};
	transition_t space_transition = {WAIT_OPERATOR, HandleSpace};

	/* initialize the LUT for invalid inputs */
	for (; i < NUM_OF_STATE; ++i)
	{
		for (j = 0; j < NUM_OF_INPUTS; ++j)
		{
			fsm[i][j] = invalid_transition;
		}	
	}
	/* assigning the LUT for digits inputs */
	for (i = 0; i < digits; ++i)
	{
		fsm[WAIT_DIGIT][i + 48] = digit_transition;
	}
	
	/* assigning the LUT for operators inputs */
	fsm[WAIT_OPERATOR]['+'].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR]['+'].handler = HandleOperator;
	fsm[WAIT_DIGIT]['+'] = digit_transition;
		
	fsm[WAIT_OPERATOR]['-'].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR]['-'].handler = HandleOperator;
	fsm[WAIT_DIGIT]['-'] = digit_transition;
	
	fsm[WAIT_OPERATOR]['*'].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR]['*'].handler = HandleOperator;
	
	fsm[WAIT_OPERATOR]['/'].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR]['/'].handler = HandleOperator;
	
	fsm[WAIT_OPERATOR]['^'].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR]['^'].handler = HandlePow;
	
	fsm[WAIT_DIGIT]['('].next_state = WAIT_DIGIT;
	fsm[WAIT_DIGIT]['('].handler = HandleOpenParacentesis;
	
	fsm[WAIT_OPERATOR][')'].next_state = WAIT_OPERATOR;
	fsm[WAIT_OPERATOR][')'].handler = HandleCloseParacentesis;		
	
	/* assigning the LUT for special cases inputs */
	fsm[WAIT_DIGIT][' '] = space_transition;
	fsm[WAIT_DIGIT][' '].next_state = WAIT_DIGIT;
	fsm[WAIT_OPERATOR][' '] = space_transition;
	
	fsm[WAIT_OPERATOR]['\0'] = null_terminator_transition;
	
	fsm[WAIT_OPERATOR]['\n'] = space_transition;
}

static void OperatorInitialize(void)
{
	size_t i = 0;
	
	operator_t invalid_operator = {0, DummyOperation};
	
	/* initialize the LUT for invalid inputs */
	for (; i < NUM_OF_INPUTS; ++i)
	{
		operators[i] = invalid_operator;
	}	
	
	/* assigning the right operator handler for each operator */
	operators['('].priority = 4;
	operators['('].operation = DummyOperation;

	operators[')'].priority = 4;
	operators[')'].operation = DummyOperation;

	operators['+'].priority = 1;
	operators['+'].operation = PlusOperation;

	operators['-'].priority = 1;
	operators['-'].operation = SubOperation;

	operators['/'].priority = 2;
	operators['/'].operation = DivOperation;

	operators['*'].priority = 2;
	operators['*'].operation = MultiOperation;
	
	operators['^'].priority = 3;
	operators['^'].operation = PowOperation;
	
	operators[DUMMY].priority = -1;
	operators[DUMMY].operation = DummyOperation;
}

/********************************* HANDLER FUNCTIONS *************************/

static char *HandleError(stack_t *operator_stack,
						 stack_t *digit_stack,
						 char *expression)
{	
	double error_result = 0;
	
	assert(digit_stack);
	
	FLAG = 0;
	STATUS = CALC_SYNTAX_ERROR;
	
	StackPush(digit_stack, &error_result);
	
	(void)operator_stack;
	(void)expression;
	
	return NULL;
}

static char *HandleDigit(stack_t *operator_stack,
						stack_t *digit_stack,
						char *expression)
{	
	double number = 0;
	
	assert(digit_stack);
	assert(operator_stack);
	assert(expression);

	if ('+' == *expression && '+' == *(expression + 1))
	{
		return HandleError(operator_stack, digit_stack, expression);
	}
	
	number = strtod(expression, &expression);
	
	StackPush(digit_stack, &number);
	
	return expression;
}

static char *HandleOperator(stack_t *operator_stack,
					        stack_t *digit_stack,
					   		char *expression)
{
	unsigned char operator = 0;
	int priority_new = 0;
	
	assert(digit_stack);
	assert(operator_stack);
	assert(expression);
	
	operator = CHAR_TO_UCHAR(*expression);
	++expression;
	
	priority_new = operators[operator].priority;
	
	ExecuteOperation(operator_stack, digit_stack, priority_new);
	
	StackPush(operator_stack, &operator);
	
	return expression;
}

static void ExecuteOperation(stack_t *operator_stack,
							 stack_t *digit_stack,
						   	 int priority)
{
	char operator_peek = 0;
	int priority_peek = 0;
	
	assert(digit_stack);
	assert(operator_stack);
	
	priority_peek = operators[CHARP_TO_UCHAR(StackPeek(operator_stack))
							 ].priority;
	
	operator_peek = *(char*)StackPeek(operator_stack);
	
	/* stopoing when current priority is bigger than peek prirority and at '('*/
	while (priority <= priority_peek && 4 != priority_peek)
	{
		ExecuteEquation(operator_peek, digit_stack);
		StackPop(operator_stack);
		priority_peek = operators[CHARP_TO_UCHAR(StackPeek(operator_stack))
								 ].priority;
				 
		operator_peek = *(char*)StackPeek(operator_stack);
	}
}

static void ExecuteEquation(char operator, stack_t *digit_stack)
{	
	double num1 = 0;
	double num2 = 0;
	double result = 0;
	
	assert(digit_stack);
	
	num2 = *(double*)StackPeek(digit_stack);
	StackPop(digit_stack);
	num1 = *(double*)StackPeek(digit_stack);
	StackPop(digit_stack);
	
	result = operators[(unsigned char)operator].operation(num1, num2);
	StackPush(digit_stack, &result);
}

static char *HandleNullTerminator(stack_t *operator_stack,
								 stack_t *digit_stack,
						   		 char *expression)			
{	
	int priority = 0;
	 
	assert(digit_stack);
	assert(operator_stack);
	assert(expression);

	ExecuteOperation(operator_stack, digit_stack, priority);
	if ('(' == *(char*)StackPeek(operator_stack))
	{
		return HandleError(operator_stack, digit_stack, expression);
	}
	
	StackPop(operator_stack);
	
	FLAG = 0;
	
	return expression;
}

static char *HandleSpace(stack_t *operator_stack,
						 stack_t *digit_stack,
						 char *expression)
{
	assert(expression);
	
	(void)operator_stack;
	(void)digit_stack;
	
	return expression + 1;
}

static char *HandleOpenParacentesis(stack_t *operator_stack,
						 			stack_t *digit_stack,
						 			char *expression)
{
	assert(operator_stack);
	assert(digit_stack);
	assert(expression);
	
	StackPush(operator_stack, expression);
	
	return expression + 1;
}

static char *HandleCloseParacentesis(stack_t *operator_stack,
						 			 stack_t *digit_stack,
						 			 char *expression)
{
	assert(operator_stack);
	assert(digit_stack);
	assert(expression);
	
	ExecuteOperation(operator_stack, digit_stack, 0);
	if ('(' == *(char*)StackPeek(operator_stack))
	{
		StackPop(operator_stack);
		
		return expression + 1;		
	}
	
	return HandleError(operator_stack, digit_stack, expression);
	
}

static char *HandlePow(stack_t *operator_stack,
						 stack_t *digit_stack,
						 char *expression)
{
	assert(operator_stack);
	assert(digit_stack);
	assert(expression);
	
	ExecuteOperation(operator_stack, digit_stack, 4);
	
	StackPush(operator_stack, expression);
	
	return expression + 1;
}

/********************************* OPERATIONS FUNCTIONS *************************/
static double PlusOperation(double num1, double num2)
{
	return (num1 + num2);
}

static double SubOperation(double num1, double num2)
{	
	return (num1 - num2);
}

static double MultiOperation(double num1, double num2)
{	
	return (num1 * num2);
}

static double DivOperation(double num1, double num2)
{	
	if (0 == num2)
	{
		FLAG = 0;
		STATUS = CALC_MATH_ERROR;
		num2 = 1;
		num1 = 0;
	}
	
	return (num1 / num2);
}

static double PowOperation(double num1, double num2)
{	
	return pow(num1, num2);
}

static double DummyOperation(double num1, double num2)
{	
	(void)num1;
	(void)num2;
	
	FLAG = 0;
	STATUS = CALC_SYNTAX_ERROR;
	
	return 0;
}



