#include <stdio.h>

#include "ws6.h"

int main(void)
{
	u_int n[] = {7, 8, 10, 11, 13, 15};
	u_int x = 15;
	u_int *n1 = &x;
	u_int y = 20;
	u_int *n2 = &y;
	
	/* test 1 */
	Pow2(20,5);
	/* test 2.1 */
	printf("%d\n",CheckPow2loop(2147483648));
	/* test 2.2 */
	printf("%d\n",CheckPow2(2147483648));
	/* test 3 */
	printf("%d -> %d\n", 1234, AddOne(1234));
	/* test 4 */
	ThreeBitsOn(n,6);
	/* test 5 */
	ByteMirrorLoop(3);
	/* test 5.2 */
	ByteMirror(3);
	/* test 6.1 */
	printf("%d\n", CheckNoIf1(34));
	/* test 6.2 */
	printf("%d\n", CheckNoIf2(34));
	/* test 6.3 */
	printf("%d\n", CheckNoIf3(211));	
	/* test 7 */
	printf("%d\n", Div16(49));
	/* test 8 */
	Swap(n1,n2);
	printf("%d %d\n",x,y);
	/* test 9.1 */
	printf("%d\n",CountBitsLoop(65535));
	/* test 9.2 */
	printf("%d\n",CountBits(65535));
	/* test 10 */
	FloatPrint();

	return 0;
}



