#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void pipeop(char** args, int numargs);

int main()
{
	return 0;
}

void pipeop(char** args, int numargs)
{
	int i;
	int k = 0;
	int p[2];
	pipe(p);

	for(i = 0; i < numargs; i++)
	{
		if(args[i][0] == '|')
		{
			if(i == numargs - 1 || i == 0 || args[i - 1][0] == '|' || args[i + 1][0] == '|')
			{
				printf("Error in arguments list.");
			}

			k++;
		}
	}	

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
			execvp(args[i - 1], args);
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
				execvp(args[i + 1], args);
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

			execvp(args[i - 1], args);
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

				execvp(args[i + 1], args);
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

					execvp(args[i + 3], args);
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

				execvp(args[i - 1], args);
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

					execvp(args[i + 1], args);
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

						execvp(args[i + 3], args);
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
		
							execvp(args[i + 5], args);
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
