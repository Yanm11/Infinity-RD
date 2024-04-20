#include <stdio.h>
int Flip(int n);

int main()
{
	int n;
	printf("The number you wish to flip: ");
	scanf("%d", &n);
	
	int x = Flip(n);
	
	printf("%d flipped is: %d\n",n,x);
	return 0;

}




int Flip(int n)
{
	int fliped = 0;
	
	while (n)
	{
		fliped *= 10;
		fliped += n % 10;
		n = n / 10;
	}
	
	return fliped;
}




/* psudocode 

the function will recive a number and will flip it numbers
ex: 1234 will become 4321


create a new variable to hold the new number
FOR LOOP until the old number is 0 
	modulo the old number by 10 and keep the reminder
	multiply the reminder by 10 times the number of loops
	add that to the new number
	divide the old number by 10
	repeat
END FOR LOOP

print new number 
*/


