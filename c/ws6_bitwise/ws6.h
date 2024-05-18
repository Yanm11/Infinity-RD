#ifndef __WS6__h_
#define __WS6__h_


#include <stdio.h>

typedef unsigned int u_int;

long Pow2(unsigned int x, unsigned int y);
int CheckPow2loop(u_int n);
int CheckPow2(u_int n);
int AddOne(int n);
int ThreeBitsOn(u_int n[], int size);
int ByteMirrorLoop(unsigned char c);
int  ByteMirror(unsigned char c);
int CheckNoIf1(unsigned char n);
int CheckNoIf2(unsigned char n);
int CheckNoIf3(unsigned char n);
int Div16(u_int n);
int Swap(u_int *n1, u_int *n2);
int CountBitsLoop(int n);
int CountBits(int n);
int FloatPrint();

#endif







