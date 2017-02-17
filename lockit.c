
/* Program name - lockit.c */ 
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/sem.h>  
#define MODE 0 
extern int semid; 
 
locker(int num) 
{ 
	static struct sembuf lock_it[1] = { 
		0 , 1 , MODE 
/*		,0 , 1 , MODE */
	}; 
 
	lock_it[0].sem_num = num; /* sem number to test */ 
/*	lock_it[1].sem_num = num;  sem number to lock */ 
 
	if ((semop(semid,&lock_it[0],1)) <0)
		return 1;
	else
		return 0;
}

unlocker (int num)
{
	static struct sembuf unlock_it[1] = {
		0 , -1 , MODE
	};

	unlock_it[0].sem_num = num; /*sem # to unlock */

	if ((semop(semid,&unlock_it[0],1)) <0)
		return 1;
	else
		return 0;
}

