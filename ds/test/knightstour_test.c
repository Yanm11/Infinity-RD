#include <stdio.h> /* printf */
	
#include "knightstour.h"

#define POS_TO_X(position) ((position & 0xF0) >> 4)
#define POS_TO_Y(position) (position & 0x0F)

void TestBuildPosition(void);
void TestKnightsTour5x5(void);
void PrintPath(position_t *path);
static int checker = 0;

int main(void)
{
	TestBuildPosition();
	TestKnightsTour5x5();
	if (checker)
	{
		printf("In Total Failed %d Tests\n", checker);
		return 0;
	}
	
	printf("\nPASSED ALL TESTS!!!!!\n");
	
	return 0;
}

void TestBuildPosition(void)
{
	unsigned char x = 2;
	unsigned char y = 1;
	position_t pos =  BuildPosition(x,y);
	
	if (33 != pos)
	{
		printf("FAILED TestBuildPosition\npos: %c\n", pos);
		++checker;
		
		return;
	}
	
	x = 8;
	y = 8;
	pos = BuildPosition(x,y);
	
	if (136 != pos)
	{
		printf("FAILED TestBuildPosition\npos: %c\n", pos);
		++checker;
		
		return;
	}

	x = 1;
	y = 1;
	pos = BuildPosition(x,y);
	
	if (17 != pos)
	{
		printf("FAILED TestBuildPosition\npos: %c\n", pos);
		++checker;
		
		return;
	}
	printf("PASSED TestBuildPosition!!\n");
}

void TestKnightsTour5x5(void)
{
	unsigned char x = 1;
	unsigned char y = 3;
	position_t pos =  BuildPosition(x,y);
	position_t path[PATH_LENGTH] = {0};
	knights_tour_status_e status = 0;
	
/*	if (0 != pos)*/
/*	{*/
/*		printf("FAILED TestKnightsTour5x5\npos: %c\n", pos);*/
/*		++checker;*/
/*		*/
/*		return;*/
/*	}*/
	
	status = RunKnightsTour(path, pos, 0,0);
	
	if (SUCCESS != status)
	{
		printf("FAILED TestKnightsTour5x5\n");
		++checker;
		
		return;
	}
	
/*	PrintPath(path);*/
}

void PrintPath(position_t *path)
{
	int x = 0;
	int y = 0;
	int i = 0;
	
	for (; i < PATH_LENGTH; ++i)
	{
		x = POS_TO_X(path[i]);
		y = POS_TO_Y(path[i]);
		
		printf("index: %d\nx: %d\ny: %d\n\n",i,x,y);
	}
}
