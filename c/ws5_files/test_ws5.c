#include <stdio.h>/* printf */
#include <string.h> 

#include "ws5.h"

#define SIZE 5
#define line_size 100

int main(void)
{
	char file_name[line_size];
	special_arr arr[SIZE] = {{"-remove", &Compare, &Remove},\
						     {"-count", &Compare, &Count}, \
					         {"-exit", &Compare, &Exit},\
					         {"<", &Compare, &WriteStart},\
					         {"", &Compare, &Write}};

	/* ex1 */
	Ex1();
	
	/* ex2 */	
	printf("write the name of a file\n");
	
	if (fgets(file_name,line_size , stdin) == NULL)
	{
		perror("Error geting input");
		return(-1);
     }
    
    file_name[strcspn(file_name,"\n")] = 0;
    
	printf("start writing:\n");
	
	while (FLAG)
	{
		StartProgram(file_name, arr);
	}
	
	return 0;
}

