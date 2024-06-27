#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <assert.h> /* assert */
#include <time.h> /* time_t */
#include <string.h> /* strcpy strcmp */
#include <ctype.h> /* strcpy strcmp */

#include "dict.h"

int main(void)
{
	SpellChecker("/usr/share/dict/words");
	
	return 0;
}
