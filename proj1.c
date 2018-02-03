//Done by PhD candidate Grzegorz Kakareko
//Graduate Research Assistant
//Department of Civil & Environmental Engineering
//Florida State University
//College of Engineering
//2525 Pottsdamer Street, Tallahassee, FL 32310
//Email: gk15b@my.fsu.edu - Phone: +1-850-570-4683

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

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

int main()
{
    
    // struct Lines instruction_lines[MAXLINES];
    // int i;
    // i = 0;
    // int adr0=0;      
    // char *itr;
    // char line[MAXCHAR];
    // char label[MAXCHAR];
    // char instr[MAXCHAR];
    // char temspace[MAXCHAR];
    // while( fgets(line, MAXCHAR, stdin) != NULL )
    // sscanf(line, "%[^:]:\t%[^\n]", label, instr)==2       
    // strcpy(instruction_lines[i].labels,label);         
    char *line;
	char **cmd;
    while (1) 
    {
    	my_setup();
		my_prompt();
		line = my_read();
		cmd = my_parse(line);
		//printf("%s\n",cmd);
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
  printf(getenv("USER"));
  printf("@");
 
  //get hostname
  char hostBuffer[256];
  int hostname;
  hostname=gethostname(hostBuffer, sizeof(hostBuffer));
  printf(hostBuffer);

  printf(" :: ");
  //get absolute directory
  char cwd[1024];
  if(getcwd(cwd, sizeof(cwd))!= NULL)
    printf(cwd);
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
	clear_line = parse_whitespace(line);
	printf("clear line: %s\n", line);
	// args = parse_arguments(parsed);
	// args = expand_variables(args);
	// args = resolve_paths(args);
	return NULL;
}
//char **parse_whitespace(char *line) 
char *parse_whitespace(char *line) 
{
//------- Removing extra white spaces--------
	int i,x;
  	for(i=x=0; line[i]; ++i)
    	if(!isspace(line[i]) || (i>0 && !isspace(line[i-1])))
      		line[x++] = line[i];
  	line[x] = '\0';
//----------------------------
//------- Adding extra white spaces for special characters --------
space_special_char(line, '<');
//Special characters include: |, <, >, &, $, ~
	
	return NULL;
}

char *space_special_char(char *line, char speacial_char)
{
	int i,x;
  	for(i=x=0; line[i]; ++i)
    	if(line[i]==speacial_char)
    		printf("we have special char");
      		//line[x++] = line[i];
  	line[x] = '\0';
	return NULL;	
} 

char **parse_arguments(char *line)
{
	return NULL;
}

char **resolve_paths(char **args)
{
	return NULL;
}

char **expand_variables(char **args)
{
	return NULL;
}

char *my_read () 
{
	// char *toParseStr = (char*)malloc(10);
	// printf("Enter string here: \n");
	// scanf("%s",toParseStr);
	// printf("%s\n",toParseStr);
	// free(toParseStr);
	// char *line = NULL;
 //  	ssize_t bufsize = 0; // have getline allocate a buffer for us
 //  	getline(&line, &bufsize, stdin);
	char line[MAXCHAR];
  	fgets(line, MAXCHAR, stdin);
  	printf("%s\n",line);
  	return line;
	//return 0;
}

void my_execute (char ** cmd) {

}

void my_clean () {}
