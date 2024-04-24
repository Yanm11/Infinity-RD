#include <stdio.h>
#include <stdlib.h>

union numbers
{
	int i;
	float f;
	double d;
};

struct x
{
	int i;

	char c;

	double d;

	short s;
};

struct card
{
	unsigned int t;
};

int main(void)
{
	union numbers nums;
	struct x xes;
	struct card cards;
	printf("sizeof nums: %ld\nsizeof xes: %ld\nsizeof cards: %ld\n",sizeof(nums),sizeof(xes),sizeof(cards));
	return 0;
}
