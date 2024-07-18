#include <string.h> /* strlen */
#include <stdio.h> /* printf */

#include "stack.h"

int CheckParentheses(char *str);

int main(void)
{
	char str1[50] = "{[(())]}([(({}))])";
	char str2[50] = "({{[[]]}}";
	char str3[50] = "(((((({{{{{[[[[]]]]}}}}})))))))";
	
	if (0 == CheckParentheses(str1))
	{
		printf("Balance\n");
		printf("passed test1\n");
	}
	else
	{
		printf("Not Balance\n");
	}
	
	if (0 == CheckParentheses(str2))
	{
		printf("Balance\n");
	}
	else
	{
		printf("Not Balance\n");
		printf("passed test2\n");
	}
	
	if (0 == CheckParentheses(str3))
	{
		printf("Balance\n");
	}
	else
	{
		printf("Not Balance\n");
		printf("passed test3\n");
	}
	
	return 0;
}

int CheckParentheses(char *str)
{
	stack_t *stack = StackCreate(strlen(str), sizeof(char));
	char lut[256] = {0};
	char open_parentheses = 0;
	
	lut[')'] = '(';
	lut[']'] = '[';
	lut['}'] = '{';
	
	if (NULL == stack)
	{
		return 1;
	}
	
	while ('\0' != *str)
	{
		if ('(' == *str || '[' == *str || '{' == *str)
		{
			StackPush(stack, str);
		}
		else
		{
			open_parentheses = 0;

			if (!StackIsEmpty(stack))
			{
				open_parentheses = *(char*)StackPeek(stack);			
			}
			
			if (open_parentheses == lut[(unsigned char)*str])
			{
				StackPop(stack);
			}
			else
			{
				StackDestroy(stack);
				
				return 1;
			}
		}
		
		++str;
	}
	
	if (!StackIsEmpty(stack))
	{
		StackDestroy(stack);
		
		return 1;
	}
	
	return 0;
}
