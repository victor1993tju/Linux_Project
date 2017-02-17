
/* Program name - dstart.c */ 
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>  
#include <signal.h>  
#define NUMFILEDES 2000 

main() 
{ 
	int fd; 
 
	signal(SIGTTOU,SIG_IGN); 
	signal(SIGTTIN,SIG_IGN); 
	signal(SIGTSTP,SIG_IGN); 
 
	if (fork() != 0)   /* Parent  */ 
	{ 
		sleep(10); 
		exit(0); 
	} 
 
	setsid();  /* detach from process group and 
	relinquish controlling terminal   */ 
 
	for (fd=0; fd<NUMFILEDES; fd++) 
	close(fd); /*close all the open files*/
 
	chdir("/"); /*change to root path*/
	umask(0); 
 
	execl("/home/user01/victor/project/","parents",0); 
	/* Set to appropriate dir  */ 
} 

