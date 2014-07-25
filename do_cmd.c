/*
 * =====================================================================================
 *
 *       Filename:  do_cmd.c
 *
 *    Description:  a
 *
 *        Version:  1.0
 *        Created:  07/25/2014 10:36:26 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cheng, 623977469@qq.com
 *        Company:  LinuxGroup2013
 *
 * =====================================================================================
 */

#include "head.h"
void do_cmd(int argcount, char arglist[100][256])
{
	int	flag = 0;       
	int	how = 0;        
	int	background = 0; 
	int	status;
	int	i;
	int	fd;
	char*	arg[argcount+1];
	char*	argnext[argcount+1];
	char*	file;
	pid_t	pid;

	for (i=0; i < argcount; i++) 
	{
		arg[i] = (char *) arglist[i];
	}
	arg[argcount] = NULL;

	for (i=0; i < argcount; i++) 
	{
		if (strncmp(arg[i], "&",1) == 0) 
		{
			if (i == argcount-1) 
			{
				background = 1;
				arg[argcount-1] = NULL;
				break;
			}
			else 
			{
				printf("wrong command\n");
				return ;
			}
		}
	}

	for (i=0; arg[i]!=NULL; i++) 
	{
		if (strcmp(arg[i], ">") == 0 )
		{
			flag++;
			how = out_redirect;
			if (arg[i+1] == NULL) 
				flag++;
		}
		if ( strcmp(arg[i],"<") == 0 ) 
		{
			flag++;
			how = in_redirect;
			if(i == 0) 
				flag++;
		}
		if ( strcmp(arg[i],"|")==0 ) 
		{
			flag++;
			how = have_pipe;
			if(arg[i+1] == NULL)
				flag++;
			if(i == 0 )
				flag++;
		}
	}
	
	if (flag > 1) 
	{
		printf("wrong command\n");
		return;
	}

	if (how == out_redirect) 
	{
		for (i=0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i],">")==0)
			{
				file   = arg[i+1];
				arg[i] = NULL;
			}			
		}
	}

	if (how == in_redirect)
	{    
		for (i=0; arg[i] != NULL; i++)
		{
			if (strcmp (arg[i],"<") == 0)
			{
				file   = arg[i+1];
				arg[i] = NULL;
			}
		}
	}

	if (how == have_pipe)
	{  
		for (i=0; arg[i] != NULL; i++)
		{
			if (strcmp(arg[i],"|")==0) 
			{
				arg[i] = NULL;
				int j;
				for (j=i+1; arg[j] != NULL; j++) 
				{
					argnext[j-i-1] = arg[j];
				}
				argnext[j-i-1] = arg[j];
				break;
			}
		}
	}

	if ( (pid = fork()) < 0 )
	{
		printf("fork error\n");
		return;
	}

	switch(how)
	{
		case 0:
		if (pid == 0) 
		{
			if ( !(find_command(arg[0])) ) 
			{
					printf("%s : command not found\n", arg[0]);
					exit (0);
			}
			execvp(arg[0], arg);
			exit(0);
		}
		break;
		case 1: 
		if (pid == 0)
		{
			if ( !(find_command(arg[0])) )
			{
				printf("%s : command not found\n",arg[0]);
				exit(0);
			}
			fd = open(file,O_RDWR|O_CREAT|O_TRUNC,0644);
			dup2(fd,1);
			execvp(arg[0],arg);
			exit(0);
		}
		break;
		case 2:
		if (pid == 0) 
		{
			if ( !(find_command (arg[0])) ) 
			{
				printf("%s : command not found\n",arg[0]);
				exit(0);
			}
			fd = open(file,O_RDONLY);
			dup2(fd,0);  
			execvp(arg[0],arg);
			exit(0);
		}
		break;
		case 3:
		if(pid == 0)
		{
			int  pid2;
			int  status2;
			int  fd2;

			if ( (pid2 = fork()) < 0 ) 
			{
				printf("fork2 error\n");
				return;
			}
			else if (pid2==0)
			{
				if ( !(find_command(arg[0])) ) 
				{
					printf("%s : command not found\n",arg[0]);
					exit(0);
				}
				fd2 = open("/tmp/youdonotknowfile",
				O_WRONLY|O_CREAT|O_TRUNC,0644);
				dup2(fd2, 1);  
				execvp(arg[0], arg);
				exit(0);
			}

			if (waitpid(pid2, &status2, 0) == -1)
				printf("wait for child process error\n");

			if ( !(find_command(argnext[0])) ) 
			{
				printf("%s : command not found\n",argnext[0]);
				exit(0);
			}
			fd2 = open("/tmp/youdonotknowfile",O_RDONLY);
			dup2(fd2,0);  
			execvp (argnext[0],argnext);
			
			if ( remove("/tmp/youdonotknowfile") )
				printf("remove error\n");
			
			exit(0);
			}
		break;
		default:
			break;
	}

	
	if ( background == 1 ) 
	{
		printf("[process id %d]\n",pid);
		return ;
	}
	
	if (waitpid (pid, &status,0) == -1)
		printf("wait for child process error\n");
}


