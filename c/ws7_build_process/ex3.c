#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "s.h"

int main()
{
	/* Test for StrCpy and StrNcmp */
	char s[] = "edewddkjih395ht95ht95ht9054hg950ghb590gb44628e";
	char *s2 = (char *) malloc(strlen(s) * sizeof(char));
	
	s2 = StrNcpy(s2, s, 15);
	
	printf("copied string: %s\n", s2);

	return 0;
}
