#include <stdio.h> /* printf */
	
#include "knightstour.h"

void TestBuildPosition(void);

static int checker = 0;

int main(void)
{
	TestBuildPosition();
	
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

