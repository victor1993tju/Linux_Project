/* Parents and fruits
 * filename: son.c
 * author: Tian Baoliang
 * ID : 2015204186
 * Date:2016/12/12
*/
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h> 
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define SEMKEY 6666
int semid;
extern int locker(int num);
extern int unlocker(int num);

void *son(void *arg){
	int value;
	int index = (int)arg;
	printf("Son %d  is coming.\n",index);/*1 or 2*/
        while(1){
		if (unlocker(1)  != 0) {
                perror("Problems unlocking sem orange");
                exit(1);}
                else{printf("an orange  has been taken from  plate by son  %d\n",index);}
                /*
		value = semctl(semid,0,GETVAL,NULL);
        	 printf("value 0  is %d\n",value);*/
		if (locker(0)  != 0) {
                perror("Problems unlocking sem ");
                exit(1); }
                else{printf("plate has empty place!\n ");}
		sleep(1);  
      }

}


int main(int argc,char *argv[]){
        int value;
/*        pthread_t pidS1;*/
        pthread_t pidS1,pidS2;
        if((semid = semget(SEMKEY,3,IPC_CREAT|0666)) < 0)
        {
                perror("create semaphore failed");
                exit(1);
        }
/*	 
	semctl(semid,0,SETVAL,2);
        semctl(semid,1,SETVAL,0);
        semctl(semid,2,SETVAL,0);*/
	value =  semctl(semid,0,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,1,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,2,GETVAL,NULL);
         printf("create,value is %d\n",value);
	sleep(2);
/*create threads*/
        pthread_create(&pidS1,NULL,son,(void *)1);
        pthread_create(&pidS2,NULL,son,(void *)2);
	pthread_join(pidS1,NULL);
	pthread_join(pidS2,NULL);
/*
        value = semctl(semid,0,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,1,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,2,GETVAL,NULL);
         printf("create,value is %d\n",value);
*/
	exit(0);
	return 0;
}
