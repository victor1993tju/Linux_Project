/* Parents and fruits
 * filename: daughter.c
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

void *daughter(void *arg){
        int value;
        int index = (int)arg;
        printf("Daughter %d  is coming.\n",index);/*1 or 2*/
        while(1){
                if (unlocker(2)  != 0) {
                perror("Problems unlocking sem apple ");
                exit(1);}
                else{printf("an apple  has been taken from  plate by daughter  %d\n",index);}
                /*
 *                 value = semctl(semid,0,GETVAL,NULL);
 *                                  printf("value 0  is %d\n",value);*/
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
        pthread_t pidD1,pidD2;
        if((semid = semget(SEMKEY,3,IPC_CREAT|0666)) < 0)
        {
                perror("create semaphore failed");
                exit(1);
        }
/*       
 *               semctl(semid,0,SETVAL,2);
 *                       semctl(semid,1,SETVAL,0);
 *                               semctl(semid,2,SETVAL,0);*/
        value =  semctl(semid,0,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,1,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,2,GETVAL,NULL);
         printf("create,value is %d\n",value);
        sleep(2);
/*create threads*/
        pthread_create(&pidD1,NULL,daughter,(void *)1);
        pthread_create(&pidD2,NULL,daughter,(void *)2);
        pthread_join(pidD1,NULL);
	    pthread_join(pidD2,NULL);
/*        value = semctl(semid,0,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,1,GETVAL,NULL);
         printf("create,value is %d\n",value);
        value = semctl(semid,2,GETVAL,NULL);
         printf("create,value is %d\n",value);
*/
        return 0;
}


