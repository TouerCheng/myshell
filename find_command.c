/*
 * =====================================================================================
 *
 *       Filename:  find_command.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2014 10:58:55 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cheng, 623977469@qq.com
 *        Company:  LinuxGroup2013
 *
 * =====================================================================================
 */

#include "head.h"
int find_command (char *command)
{
	DIR*             dp;
	struct dirent*   dirp;
	char*			 path[] = { "./", "/bin", "/usr/bin", NULL};

	
	if( strncmp(command,"./",2) == 0 )
		command = command + 2;

	int i = 0;
	while (path[i] != NULL)
	{
		if ( (dp = opendir(path[i]) ) == NULL)  
			printf ("can not open /bin \n");
		while ( (dirp = readdir(dp)) != NULL)
		{
			if (strcmp(dirp->d_name,command) == 0) 
			{
				closedir(dp);
				return 1;
			}
		}
		closedir (dp);
		i++;
	}
	return 0;
}
