/*
/* Parents and fruits
 * filename: children.c
 * author: Tian Baoliang
 * ID : 2015204186
 * Date:2016/12/12
*/
#include <stdio.h>
#include <sys/signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define EXETIME 10
int main(int argc,char  *argv[]){
/*	int time =(int) argv[1];first input  parameter*/
	int time;
	printf("input time you want to execute (senconds)\n");
	scanf("%d",&time);
	printf("execute time has set to %d senconds\n",time);
	pid_t son,daughter,wpid;
	int status;
	son = fork();
	if (son<0){
		perror("fork failed\n");
		exit(1);
	}
	if (son==0){/*first child process*/
		printf("son process is build,PID is : %d\n",getpid());
		execl("./son","son",0);
	}
	else{/*main process here*/
		daughter = fork();
		if (daughter<0){
		perror("fork failed\n");
		exit(1);
		}
		if (daughter==0){/*second child process*/
			printf("daughter process is build,PID is : %d\n",getpid());
			execl("./daughter","daughter",0);
		}else{
		/*	sleep(EXETIME);*/
			sleep(time);
			kill(son,SIGKILL);
			kill(daughter,SIGKILL);
/*			kill(-son, SIGTERM);
			kill(-daughter,SIGTERM);*/
		}
	}
			wpid = wait(&status);
			printf(" Programe is over,Thanks\n");
	return 0;
}

