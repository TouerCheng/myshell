/*
 * =====================================================================================
 *
 *       Filename:  git_input.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2014 05:35:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cheng, 623977469@qq.com
 *        Company:  LinuxGroup2013
 *
 * =====================================================================================
 */

#include "head.h"
void get_input(char *buf)
{
	int len = 0;
	int ch;

	ch = getchar();
	while (len < 256 && ch != '\n') 
	{
		buf[len++] = ch;
		ch = getchar();
	}
		
	if(len == 256) 
	{
		printf("command is too long \n");
		exit(-1); 
	}
			
	buf[len] = '\n';
	len++;
	buf[len] = '\0';        
}
