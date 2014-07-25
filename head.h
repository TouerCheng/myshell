/*
 * =====================================================================================
 *
 *       Filename:  head.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/25/2014 02:54:41 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cheng, 623977469@qq.com
 *        Company:  LinuxGroup2013
 *
 * =====================================================================================
 */

#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define normol 0
#define out_redirect 1
#define in_redirect 2
#define have_pipe 3
void print_prompt();
void get_input(char *);
void explain_input(char *,int *,char a[][256]);
void do_cmd(int ,char a[][256]);
int find_command(char *);
