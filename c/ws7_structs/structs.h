#ifndef __STRUCTS_H__
#define __STRUCTS_H__

typedef void (*func_ptr)();

typedef struct any_element
{
	void *element;
	func_ptr add;
	func_ptr print;
	func_ptr clean;
} any_element_t;

typedef struct arr_element
{
	int *array_int;
	int size;
}arr_element_t;

void AddInt(int *ptr_int, int num);
void AddFloat(float *ptr_float, int num);
void AddString(char **ptr, int num);
void AddElem(arr_element_t *elem, int num);
void PrintInt(int *ptr);
void PrintFloat(float *ptr);
void PrintString(char **ptr);
void PrintElem(arr_element_t *elem);
void Clean(char **ptr);
void CleanElem(arr_element_t *elem);
void DoNothing();

#endif
