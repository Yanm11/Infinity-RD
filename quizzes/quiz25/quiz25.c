#include <stdio.h> /*printf */

void Foo(void);

int main(void)
{
	
	Foo();
	
	return 0;
}

void Foo(void)
{
	int *pi = NULL; /* add NULL */
	int a = 1; /* split the raws */
	int b = 2;
	int c = 3;
	const char *c_str = "abcd"; /* nothing */
	char *p_str = (char *)c_str; /* added asting */
	char arr_str[] = "abcd"; /* nothing */
	const char ch;/*?*/
	short *ps = NULL; /* brought it up */

	printf("%s\n", c_str + 1);/* print bcd */
	printf("%lu\n", sizeof(c_str)); /* print 8 */
	printf("%s\n", arr_str + 1);/* print bcd */
	printf("%lu\n", sizeof(arr_str));/* print 5 */
	printf("%s\n", p_str);/* print abcd */
	printf("%lu\n", sizeof(p_str));/* print 8 */

	printf("%lu\n", sizeof(*ps));/* print 2 */
	printf("%lu\n", sizeof(*pi));/* print 4 */

	pi = &c; /* switch rows */
	*pi = a;
	b = *pi; /* change from address to value */
	(void)b; /* added for no warning */
	
	/* remove the raw of changing a const str */
	printf("%s\n", c_str);/* print abcd */
	*(arr_str + 1) = '0';
	printf("%s\n", arr_str);/* print a0cd */
	/* remove the ++arr */
	printf("%s\n", arr_str + 1);/* print 0cd */

	p_str = (char*)&c + 3;
	*p_str = '1';
	printf("%d\n", c);/* print 822083585 */
	
	pi = (int*)&ch;
	*pi = 0;	
}
