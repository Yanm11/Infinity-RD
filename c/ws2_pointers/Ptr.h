#ifndef __PTR_H__
#define __PTR_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void SwapInt(int *p1, int *p2);
int *ArrayCp(int array[], int size);
void PrintAddresses();
void swap2sizet(size_t *num1, size_t *num2);
void swap2sizetp(size_t **num1, size_t **num2);
int palindrome(char *str);
void RmEdg(char *str); 
void WhiteSpace(char *str);

#endif

