
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc free */
#include <string.h> /* strlen strcpy */
#include <ctype.h> /* tolower */


void Memory(char **env, int num_env_var);
void ToLower(char *str);

extern char **environ;

int main()
{
	int num_env = 0;
	char **big_buffer = NULL;
	int i = 0;
	
	for(; environ[num_env] != 0; num_env++){}
	
	big_buffer = (char **) malloc(num_env * sizeof(char *));
	
	if (big_buffer == NULL)
	{
		free(big_buffer);
		return 1;
	}
	
	Memory(big_buffer, num_env);
	
	
	for (; i < num_env; i++)
	{
		strcpy(big_buffer[i], environ[i]);
		
		ToLower(big_buffer[i]);
		
		printf("%s \n", big_buffer[i]);
		
	}
	
	for (i = 0; i < num_env; i++)
	{
		free(big_buffer[i]);
	}
	
	free(big_buffer);
	
	return 0;
}


void Memory(char **buffer, int num_env_var)
{
	int i = 0;
	for(; i < num_env_var ; i++)
	{
		buffer[i] = (char *)malloc((strlen(environ[i])+1) * sizeof(char));
	
		if (buffer[i] == NULL)
		{
			--i;
			for (; i > 0; i--)
			{
				free(buffer[i]);
			}
			free(buffer);
		}
	}
}


void ToLower(char *str)
{
	char *ptr = str;
	
	while (*ptr)
	{
		*ptr = tolower(*ptr);
		++ptr;
	}
}










