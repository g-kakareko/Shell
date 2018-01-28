
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *my_read();
void my_setup();
void my_prompt();
char **my_parse(char *line);
void my_execute(char **cmd);
void my_clean();
char *parse_whitespace(char *line);
char **parse_arguments(char *line);
char **resolve_paths(char **args);
char **expand_variables(char **args);

#define SIZE 100
int main(){

  char *line;
  char **cmd;

  while(1){
    //setup
    my_setup();

    //print prompt
    my_prompt();

    //read input
    //my_read();
    line=my_read();

    //transform input
    cmd=my_parse(line);

    
    //execute command
    my_execute(cmd);

    //cleanup
    my_clean();

    }
  return 0;
}

void my_setup(){


}
void my_prompt(){
  printf("-> ");
}


char* my_read(){
  //get line of data from stdin - can use fgets - check return value
 
  
  char *command;
  command=(char*) malloc(SIZE);

 
  int i;
  
  fgets(command, SIZE,stdin);
 
  for (i=0; i < SIZE; ++i){
    if(command[i]=='\n')
      command[i]='\0';

    
  }
  //set the null terminator
  command[strlen(command)]='\0';
  
  
  //return it as a c-string
  return command;
  //if dynamically created, make sure to free it later (cleanup)

}

char **my_parse(char *line){
  //takes in a c-string of input

  //returns an array of c-strings

  //each of the command arguments in a separate cell
  //parsing is necessary bc
  //you need to strip excess whitespace
  //you need to split up the arguments
  //you need to expand environmental variables
  //you need to resolve pathnames

  char **args;

  line=parse_whitespace(line);
  /*
  args=parse_arguments(parsed);
  args=expand_variables(args);
  args=resolve_paths(args);
  */
  //return cmd;
  return NULL;
}

/*Takes in a c-string
Returns the same c-string after adding/removing whitespace
Transforms c-string such that there is exactly one space bw each argument
*/
char *parse_whitespace(char *line){
  //Leading white space - remove until first argument at 0th slot of c-string
  //loop through array - will shift array if there is whitespace in beginning
  int i, j;
 
  int index=0;
  int temp;
  temp=strlen(line)+1;
  while(line[index]==' ' || line[index] == '\t' || line[index]== '\n'){
    index++;
  }
  if (index!=0){
      i=0;
      while(line[i+index]!='\0'){
	line[i]=line[i+index];
	i++;
    }
      line[i]='\0';
      temp=i;
      while(i < SIZE){
	line[i]=' ';
	i++;
      }
    }

  //Trailing white space - remove until last character of last arg is the 
  //n-1th character of c-string (nth character is \0
  //create a new char array and make it size temp+1 and copy line over
  char* tmp= (char*) malloc(temp+1);

  i=0;
  while(i<temp+1){
    tmp[i]=line[i];
    i++;
  }

  line= (char*) malloc(temp+1);
  i=0;

  //copy back from tmp to line
  while(i<temp+1){
    line[i]=tmp[i];
    i++;
  }
  //Extra white space between arguments
  i=0;
  j=0;
  //loop through array - if two white spaces in a row, adjust array 
  int count=0;
  for(i=0; i < strlen(line); i++){
    if(line[i]==' '){
      count++;
    }

  }

  tmp= (char*) malloc(strlen(line)-count+1);
  for(i=0; i < strlen(line);i++){
    if(line[i]!=' ' || line[i]==' ' && line[i+1]!=' '){
      tmp[j]=line[i];
      j++;
    }
   
    
  }
  tmp[j+1]='\0';


  //copy back to line - so it's the right length
  i=0;
  line= (char*) malloc(temp+1);

  while(i<strlen(tmp)){
    line[i]=tmp[i];
    i++;
  }
  
  int k=0;
  //special characters <file, cmd|, cmd|>file, you add a space bw special 
  //character and the other argument (| < > & $ ~)
  for(i=0; i < strlen(line); i++){
    if(line[i]=='|' || line[i] == '<' || line[i] == '>' || line[i]== '&' ||
       line[i]=='$' || line[i] == '~')
      {
	//if the spot before is not a space, must add space
	if(line[i-1]!=' '){
	  
	 
	}
	//if the spot after is not a space, must add space
	if(line[i+1]!=' '){
	  
	}
      }
  }
  
  
  
  
 
  //temporary print statement, just to check progress
  for (i=0; i < strlen(line); i++){
    printf("line[%d] = %c\n", i, line[i]); 
  }

  //will return line once completed with this function
  return NULL;
}

/*takes in a c-string - represents input command with augmented whitespace
Returns an array of c-strings - represents arguments of command in separate cel
You will traverse the input string placing the characters into different buckets of the output array
*/
char **parse_arguments(char *line){
  return NULL;
}

char **resolve_paths(char **args){
  return NULL;
}

char **expand_variables(char **args){
  return NULL;
}

void my_execute(char **cmd){
  //match against patterns
  //execute based on pattern
  //print results
}

void my_clean(){}
