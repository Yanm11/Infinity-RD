#include <stdio.h>
#include <assert.h>
int main(void)
{
	char const *str3 = "whatever";
	str3[1] = 'a';
	printf("%s", str3);
	return 0;
}
