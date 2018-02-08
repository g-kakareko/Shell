#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void expenv(char**, int);

int main ()
{
	return 0;
}

void expenv(char** args, int numargs)
{
	char str[255];
	int i = 0;
	for(i = 0; i < numargs; i++)
	{	
		if(args[i][0] == '$')
		{
			int j = 1;
			for(j = 1; j < strlen(args[i]); i++)
				str[j] = args[i][j];

			strcpy(args[i], getenv(str));
		}
	}
}
