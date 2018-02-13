#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void pipeop(char** args, int numargs);

int main()
{
	return 0;
}

void pipeop(char** args, int numargs)
{
	int i;
	int k = 0;
	int j = 0;

//strips args into sections for execution
	char newargs0[5][35];
	char newargs1[5][35];
	char newargs2[5][35];
	char newargs3[5][35];

//used to iterate through newargs
	int count0 = 0;
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;

	for(i = 0; i < numargs; i++)
	{
		if(args[i][0] == '|')
		{
			if(i == numargs - 1 || i == 0 || args[i - 1][0] == '|' || args[i + 1][0] == '|')
			{
				printf("Error in arguments list."); //error check
			}
			
			k++; // number of pipes
		}

		else//if cmd argument is not a pipe add it to its respective portion
		{
			if(k == 0)
			{
				if(count0 == 0)
				{
					strcpy(newargs0[count0], "bin/");
					strcat(newargs0[count0], args[i]);
				}
				strcpy(newargs0[count0],args[i]);
				count0++;
			}

			if(k == 1)
			{
                                if(count1 == 0)
                                {
                                        strcpy(newargs1[count1], "bin/");
                                        strcat(newargs1[count1], args[i]);
                                }

				strcpy(newargs1[count1],args[i]);
				count1++;

			}

			if(k == 2)
			{
                                if(count2 == 0)
                                {
                                        strcpy(newargs2[count2], "bin/");
                                        strcat(newargs2[count2], args[i]);
                                }

				strcpy(newargs2[count2],args[i]);
				count2++;

			}

			if(k == 3)
			{
                                if(count3 == 0)
                                {
                                        strcpy(newargs3[count3], "bin/");
                                        strcat(newargs3[count3], args[i]);
                                }

				strcpy(newargs3[count3],args[i]);
				count3++;

			}	
		}
	}

	if(k == 0) return;

	int wait;
	int wait1;
	int wait2;
	int wait3;

	int FD[2];
	int FD2[2];
	int FD3[3];

	int one_pid;
	int two_pid;
	int three_pid;
	int four_pid;

	pipe(FD);
	pipe(FD2);
	pipe(FD3);
	
	if(k == 1)
	{
		one_pid = fork();
		
		if (one_pid == 0)
		{
			close(1);
			dup(FD[1]);
			close(FD[0]);
			close(FD2[0]);
			close(FD2[1]);
			close(FD3[0]);
			close(FD3[1]);
			execvp((char*)newargs0[0],(char**)newargs0);
		}

		else
		{
			waitpid(one_pid, &wait, 0);

			two_pid = fork();

			if(two_pid == 0)
			{
				close(0);
                        	dup(FD[0]);
				close(FD[1]);
                        	close(FD2[0]);
				close(FD2[1]);
                        	close(FD3[0]);
				close(FD3[1]);
				execvp((char*)newargs1[0], (char**)newargs1);
			}

			else
			{
				waitpid(two_pid, &wait1, 0);
			}
		}
	}

	if(k == 2)
	{
		one_pid = fork();


		if(one_pid = 0)
		{
                        close(0);
                        dup(FD[0]);
                        close(FD[1]);
                        close(FD2[0]);
                        close(FD2[1]);
                        close(FD3[0]);
                        close(FD3[1]);

			execvp((char*)newargs0[0],(char**) newargs0);
		}

		else
		{

			waitpid(one_pid, &wait, 0);

			two_pid = fork();

			if(two_pid == 0)
			{
	                        close(0);
                                dup(FD[0]);
                                close(1);
				dup(FD2[1]);
                                close(FD2[0]);
                                close(FD2[1]);
                                close(FD3[0]);
                                close(FD3[1]);

				execvp((char*)newargs1[0],(char**) newargs1);
			}

			else
			{
				waitpid(two_pid, &wait1, 0);

				three_pid = fork();
	
				if(three_pid == 0)
				{
	                                close(0);
                                	dup(FD2[0]);
                            		close(FD[1]);
                        	        close(FD2[0]);
                	                close(FD2[1]);
        	                        close(FD3[0]);
	                                close(FD3[1]);

					execvp((char*)newargs2[0], (char**)newargs2);
				}

				else
				{
					waitpid(three_pid, &wait2, 0);
				}
			}
		}
		
	}
	
	if(k == 3)
	{
		one_pid = fork();

			if(one_pid == 0)
			{
                                close(1);
                                dup(FD[1]);
                                close(FD[1]);
                                close(FD2[0]);
                                close(FD2[1]);
                                close(FD3[0]);
                                close(FD3[1]);

				execvp((char*)newargs0[0],(char**) newargs0);
			}

			else
			{
				waitpid(one_pid, &wait, 0);

				two_pid = fork();
				if(two_pid == 0)
				{
	                                close(0);
	                                dup(FD[0]);
					close(FD[1]);
	                                close(1);
					dup(FD2[1]);
					close(FD2[0]);
	                                close(FD3[0]);
	                                close(FD3[1]);

					execvp((char*)newargs1[0],(char**) newargs1);
				}

				else
				{
					waitpid(two_pid, &wait1, 0);
					
					three_pid = fork();

					if(three_pid == 0)
					{
		                                close(0);
		                                dup(FD2[0]);
	        	                        close(1);
						dup(FD3[1]);
						close(FD[0]);
						close(FD[1]);
	                	                close(FD2[1]);
	                                	close(FD3[0]);

						execvp((char*)newargs2[0],(char**) newargs2);
					}
					
					else
					{
						waitpid(three_pid, &wait2, 0);
						four_pid = fork();
						if(four_pid == 0)
						{
			                                close(0);
                			                dup(FD3[0]);
                			                close(FD[1]);
                        			        close(FD2[0]);
                        			        close(FD2[1]);
                        			        close(FD3[0]);
		
							execvp((char*)newargs3[0],(char**) newargs3);
						}
						
						else
						{
							waitpid(four_pid, &wait3, 0);
						}
					}
				}
			}
	}
}
