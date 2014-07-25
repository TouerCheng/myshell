/*
 * =====================================================================================
 *
 *       Filename:  explian_input.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2014 10:27:19 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cheng, 623977469@qq.com
 *        Company:  LinuxGroup2013
 *
 * =====================================================================================
 */

#include "head.h"
void explain_input(char *buf, int *argcount, char arglist[100][256])
{
	char*p= buf;
	char*q= buf;
	int number= 0;

	while (1) 
	{
		if ( p[0] == '\n' )
		  break;
		if ( p[0] == ' '  )
		  p++;
		else 
		{
			q = p;
			number = 0;
			while( (q[0]!=' ') && (q[0]!='\n') ) 
			{
				number++;
				q++;				
			}
			strncpy(arglist[*argcount], p, number+1);
			arglist[*argcount][number] = '\0';
			*argcount = *argcount + 1;
			p = q;
					
		}
	}
}
