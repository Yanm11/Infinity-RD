#ifndef __EX1_H__
#define __EX1_H__

#include <stdio.h> /* printf */
#include <string.h> /* strlen */
#include <ctype.h> /* isalpha */

long StrInt(char *str, int base);
char *IntStr(char *str, int num, int base);
int ConvertCharInt(char *str, int base);
int ConvertIntChar(int num);

void CreateLUT(char *arr, size_t size);
void PrintOnly2Arr(char *arr1, char *arr2, char *arr3, size_t size1, size_t size2, size_t size3);

void CheckIfLitEnd();

#endif


	
