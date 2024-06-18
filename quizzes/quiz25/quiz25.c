#include <stdio.h> /*printf */

void foo(void);

int main(void)
{
	
	foo();
	
	return 0;
}


void foo(void)
{
	int *pi = NULL;
	int a = 1;
	int b = 2;
	int c = 3;
	const char *c_str = "abcd";
	char *p_str = (char *)c_str;
	char arr_str[] = "abcd";
	const char ch;/*?*/
	short *ps = NULL;

	printf("%s\n", c_str + 1);/* print bcd */
	printf("%lu\n", sizeof(c_str)); /* print 8 */
	printf("%s\n", arr_str + 1);/* print bcd */
	printf("%lu\n", sizeof(arr_str));/* print 5 */
	printf("%s\n", p_str);/* print abcd */
	printf("%lu\n", sizeof(p_str));/* print 8 */

	printf("%lu\n", sizeof(*ps));/* print 2 */
	printf("%lu\n", sizeof(*pi));/* print 4 */

	pi = &c;
	*pi = a;
	b = *pi;
	(void)b;
	
	printf("%s\n", c_str);/* print abcd */
	*(arr_str + 1) = '0';
	printf("%s\n", arr_str);/* print a0cd */
	printf("%s\n", arr_str + 1);/* print 0cd */

	p_str = (char*)&c + 3;
	*p_str = '1';
	printf("%d\n", c);/* print 822083585 */
	
	pi = (int*)&ch;
	*pi = 0;	
}
