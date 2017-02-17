/* Parents and fruits
 * filename: parents.c
 * author: Tian Baoliang
 * ID : 2015204186
 * Date:2016/12/09
*/
#include <sys/types.h>  
#include <sys/shm.h>  
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
#define SEMKEY 6666
#define MAX_TIME 30
#define SHMKEY 333333L 
#define INFOSIZE 256000 
#define NUMFILEDES 2000 
const char * fruit[8] ={ "orange","apple"};
const char * FilePath = "/home/user01/victor/project/daemons.log";
int semid;
int shmid;
extern int locker(int num);
extern int unlocker(int num);
void clearLog(){
        int  fd, len;
        if((fd = open(FilePath, O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0)
        {
            perror("open");
            exit(1);
        }
        ftruncate(fd,0);
	close(fd);
        return;
}

void output(char * buf){
        int  fd, len;
/*        char *buf = "this is a Dameon\n";*/
        len = strlen(buf);
        if((fd = open(FilePath, O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0)
        {
            perror("open");
            exit(1);
        }
        write(fd, buf, len);
        close(fd);
	return;
}

void *parent(void *arg){
	printf("Producer is generated.\n");
	int index = (int)arg;
	while(1){
		if (unlocker(0)  != 0) { 
   		perror("Problems unlocking sem empty"); 
		exit(1);} 
		else{printf("a fruit has been placed in plate");}


		if (locker(index)  != 0) { 
   		perror("Problems unlocking sem "); 
		exit(1); }
		else{printf("it is %s\n ",fruit[index-1]);}
		sleep(1);
	}

}
int main(int argc,char *argv[]){
/*	init_daemon();*/
	int fd; 
	signal(SIGTTOU,SIG_IGN); 
	signal(SIGTTIN,SIG_IGN); 
	signal(SIGTSTP,SIG_IGN); 
	if (fork() != 0)   /* Parent  */ 
	{ 
	/*	sleep(10); */
		exit(0); 
	} 
 	setsid();  /* detach from process group and 
	relinquish controlling terminal   */ 
 	for (fd=0; fd<NUMFILEDES; fd++) 
	close(fd); 
 	chdir("/"); 
	umask(0); 

	int value;
	pthread_t pidF,pidM;
/*	pthread_t pidM;*/
	clearLog();
	output("welcome");
 printf("Welcome to Parents and fruits  problem!\n");
/*init as daemon*/

/*initial sem*/
	/*if((semid = semget(IPC_PRIVATE,3,IPC_CREAT|0666)) < 0)*/
	if((semid = semget(SEMKEY,3,IPC_CREAT|0666)) < 0)
	{
		perror("create semaphore failed");
		exit(1);
	}
	/*semid=semget(SEMKEY,3,IPC_CREAT|0660); create 3 sem in the sem set*/
	/*initial value of sem empty(2),orange(0),apple(0)*/
	semctl(semid,0,SETVAL,2);
	semctl(semid,1,SETVAL,0);
	semctl(semid,2,SETVAL,0);
	value =	semctl(semid,0,GETVAL,NULL);
	 printf("create,value is %d\n",value);
	value = semctl(semid,1,GETVAL,NULL);
	 printf("create,value is %d\n",value);
	value = semctl(semid,2,GETVAL,NULL);
	 printf("create,value is %d\n",value);
/*create threads*/
	pthread_create(&pidM,NULL,parent,(void *)1);
	pthread_create(&pidF,NULL,parent,(void *)2); 
	pthread_join(pidM,NULL);
	pthread_join(pidF,NULL);
		
/*	sleep(MAX_TIME);*/
	value =	semctl(semid,0,GETVAL,NULL);
	 printf("value is %d\n",value);
	value = semctl(semid,1,GETVAL,NULL);
	 printf("value is %d\n",value);
	value = semctl(semid,2,GETVAL,NULL);
	 printf("value is %d\n",value);

        /*exit(0)*/;
        return 0;

}
