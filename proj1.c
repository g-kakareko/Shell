/**************************************
	
	Authors: 
	1)	Grzegorz Kakareko
	email: gk15b@my.fsu.edu
	2)	Jordan Camejo
	email: 
	3)	Grace Bunch
	email:  

**************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>

#define MAXCHAR 255  // Max length of a single line of code.

void my_setup();
void my_prompt();
char **my_parse (char *line);
void my_execute (char ** cmd);
void my_clean ();
char *my_read ();
char *parse_whitespace(char *line); 
char **parse_arguments(char *line);
char **resolve_paths(char **args);
char **expand_variables(char **args);
char *space_special_char(char *line, char speacial_char);

int arg_size;
int main()
{
            
    char *line;
	char **cmd;
    while (1) 
    {
    	my_setup();
		my_prompt();
		line = my_read();
		//printf("%s\n",line);
		cmd = my_parse(line);
		printf("------------- %s\n",line);
		//my_execute(cmd);
		//my_clean();

		//Setup
		//Print prompt
		//Read input
		//Transform input
		//Match against patterns
		//Execute command
		//Print results
		//Cleanup
	}

    return 0;
}

void my_setup() {}
void my_prompt() 
{
	//get username
  //printf(getenv("USER"));
  printf("%s",getenv("USER"));
  printf("%s","@");
 
  //get hostname
  char hostBuffer[256];
  int hostname;
  hostname=gethostname(hostBuffer, sizeof(hostBuffer));
  printf("%s",hostBuffer);

  printf(" :: ");
  //get absolute directory
  char cwd[1024];
  if(getcwd(cwd, sizeof(cwd))!= NULL)
    printf("%s",cwd);
  printf(" => ");
}


char **my_parse (char *line) 
{	
	// char *toParseStr = (char*)malloc(10);
	// printf("Enter string here: \n");
	// scanf("%s",toParseStr);
	// printf("%s\n",toParseStr);
	// free(toParseStr);
	// return NULL;
	char **args;
	char *clear_line;
	line = parse_whitespace(line);
	//line=clear_line;
	//printf("clear line: %s\n", line);
	args = parse_arguments(line);
	int i;
	for (i = 0; i < arg_size; ++i) 
        printf("%s\n", args[i]);
	args = expand_variables(args);
	// args = resolve_paths(args);
	return NULL;
}
//char **parse_whitespace(char *line) 
char *parse_whitespace(char *line) 
{
/**************************************
	Removing extra white spaces
***************************************/
	int i,x;
  	for(i=x=0; line[i]; ++i)
    	if(!isspace(line[i]) || (i>0 && !isspace(line[i-1])))
      		line[x++] = line[i];
  	line[x] = '\0';
/**************************************
	Adding extra white spaces for special characters
	Special characters include: |, <, >, &, $, ~
***************************************/
	line = space_special_char(line, '<');
	line = space_special_char(line, '>');
	line = space_special_char(line, '|');
	line = space_special_char(line, '&');
	line = space_special_char(line, '$');
	//printf("Final line: %s\n", line);

	return line;
}

char *space_special_char(char *line, char speacial_char)
{
	// int i,x;
 //  	for(i=x=0; line[i]; ++i)
 //    	if(line[i]==speacial_char)
 //    		printf("we have special char");
 //      		//line[x++] = line[i];
 //  	line[x] = '\0';
	int i;
	//for(i=0; i < strlen(line); i++)
  	for(i=0; line[i] != '\0'; i++)
  	{
    // if(line[i]=='|' || line[i] == '<' || line[i] == '>' || line[i]== '&' ||
    //    line[i]=='$' || line[i] == '~')
      if(line[i]==speacial_char)
      {
      	bool t1; // [i-1]
      	bool t2; // [i+1]
      	bool t3; // [i+1] and [i+1]
      	t1=line[i-1]!=' ';
      	t2=line[i+1]!=' ';
      	if(t1 && t2)
      	{
			char *new_line;
			new_line=(char*) malloc(MAXCHAR);

			int k;
			for(k=0; k < (i); k++)
			{
				new_line[k]=line[k];
			}
			new_line[i]=' ';
			new_line[i+1]=line[i];
			new_line[i+2]=' ';
			int j;
			//printf("%d\n", k);
			for(j=k; j < (strlen(line)); j++)
			{
				new_line[j+3]=line[j+1];
			}
			//line=new_line;
			new_line[j+3]='\0';
			line=new_line;
			//printf("%s\n","t1 && t2" );
			//printf("new_line: %s\n", new_line);	

      	}else if(t1)
      	{
      		char *new_line;
			new_line=(char*) malloc(MAXCHAR);

			int k;
			for(k=0; k < (i); k++)
			{
				new_line[k]=line[k];
			}
			new_line[i]=' ';
			new_line[i+1]=line[i];
			int j;
			for(j=k; j < (strlen(line)); j++)
			{
				new_line[j+2]=line[j+1];
			}
			new_line[j+2]='\0';
			line=new_line;
			//printf("%s\n","t1" );
			//printf("new_line: %s\n", new_line);

      	}else if(t2)
      	{
      		char *new_line;
			new_line=(char*) malloc(MAXCHAR);

			int k;
			for(k=0; k <= (i); k++)
			{
				new_line[k]=line[k];
			}
			new_line[i+1]=' ';
			int j;
			for(j=k; j < (strlen(line)); j++)
			{
				new_line[j+1]=line[j];
			}
			new_line[j+1]='\0';
			line=new_line;
			//printf("%s\n","t2" );
			//printf("new_line: %s\n", new_line);

      	}
      	}
      }
  	//printf("line: %s\n", line);
	return line;	
} 

char **parse_arguments(char *line)
{
	int i;
	int k=0;
	//for(i=0; line[i] != '\0'; i++)
	int d =strlen(line);
	//printf("Size: %d\n", d);
	//printf("Line in parse_arguments: %s\n", line);
  	for(i=0; i <strlen(line); i++)
  	{
  		//if((line[i]=' ') && (i!=0))
  		if(isspace(line[i]) && (i!=0))
  		{	
  			//printf("%s\n","We have space" );
  			if(!isspace(line[i-1]))
  			{
  				//printf("%s\n","We have space" );
  				k++;
  			}
  		}
  	}	
  	arg_size=k;
  	//printf("spaces: %d\n", k);
	char **vector_arg;
	vector_arg=(char**) malloc((k)*MAXCHAR);

//---------------------------
	//printf( "Tokens:\n" );
	char seps[] = " ";
	char *token;
    /* Establish string and get the first token: */
    token = strtok(line, seps );
    int j =0;
    vector_arg[j]=token;
    j++;
    while( token != NULL )
    {
        /* While there are tokens in "string" */
        //printf( " %s\n", token );
        /* Get next token: */
        token = strtok( NULL, seps );
		vector_arg[j]=token;
		j++;        
    }
    // for (i = 0; i < k; ++i) 
    //     printf("%s\n", vector_arg[i]);


	//return NULL;
	return vector_arg;
}

char **resolve_paths(char **args)
{
	return NULL;
}

char **expand_variables(char **args)
{
	/*
	$PATH
	$HOME
	$USER
	$SHELL
	$PWD
	*/
	int i;
	for (i = 0; i < arg_size; ++i) 
        printf("%s\n", args[i]);

	return NULL;
}

char *my_read () 
{
/**************************************
Function to et line of data from stdin
***************************************/ 

	// char *toParseStr = (char*)malloc(10);
	// printf("Enter string here: \n");
	// scanf("%s",toParseStr);
	// printf("%s\n",toParseStr);
	// free(toParseStr);
	// char *line = NULL;
 	// ssize_t bufsize = 0; // have getline allocate a buffer for us
 	// getline(&line, &bufsize, stdin);
	// char *line[MAXCHAR];
 	// fgets(line, MAXCHAR, stdin);
 	// printf("%s\n",line);
  	// return line;
 	
 	char *command;
 	command=(char*) malloc(MAXCHAR);
  	//int i;
 	fgets(command, MAXCHAR,stdin);
 	// printf("%s\n",command);
	return command;
}

void my_execute (char ** cmd) {

}

void my_clean () {}
