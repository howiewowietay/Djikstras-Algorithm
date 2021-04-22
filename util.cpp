#include <string.h>
#include <stdio.h>
#include "util.h"

int nextCommand(char* word)
{
	char c;
	int i, r_value;

     // printf("BGN nextWord\n");
    
	r_value = 0;
	c = getchar();
	while (c == ' ' || c == '\t' || c == '\n')
	{
		c = getchar();
	}

	i = 0;
	while (c != EOF)
	{
		if (c == ' ' || c == '\t' || c == '\n')
		{
			break;
		}
		r_value = 1;
		word[i] = c;
		i++;
		c = getchar();
	}
	word[i] = '\0';
	
	// printf("END nextWord\n");
    // r_value is 1 for successful reading
    // r_value is 0 for unsuccessful reading

	return r_value;
}
