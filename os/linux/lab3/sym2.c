#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

#define PROD 3
#define CONS 3
#define BUF 20

// 0 - consumer, 1 - producer, 2 - binary
struct sembuf prod_start[2] = { { 1, -1, 0 }, { 2, -1, 0 } };
struct sembuf prod_end[2] = { { 0, 1, 0 }, { 2, 1, 0 } };
struct sembuf cons_start[2] = { { 0, -1, 0 }, { 2, -1, 0 } };
struct sembuf cons_end[2] = { { 1, 1, 0 }, { 2, 1, 0 } };

//static int shprod = 0;
//static int shcons = 0;

void print_buffer(int * buf)
{
    printf("\n");
	for (int k = 0; k < BUF + 2; k++)
   {
	 	printf("%d ", *(buf + k));
   }
   printf("\n");
}

int producer(int *buf, int *prod, int sem_id, int k) 
{
	while (1) {
        int op_p, op_v;
        op_p = semop(sem_id, prod_start, 2);
        if ( op_p == -1 )
        {
            perror( "Can't make p-operation!\n" );
            return 1;
        }
        
        int value = *(buf + *prod) + 1;
        if (++(*prod) == BUF) {
            //exit(1);
            *prod = 0;
        }
        *(buf + *prod) = value;
        printf("Producer №%d set: %d to pos %d\n", k, value, *prod);
        
        op_v = semop(sem_id, prod_end, 2);
        if (op_v == -1 )
        {
            perror( "Can't make v-operation!\n" );
            return 1; 
        }
        //print_buffer(buf);
        sleep(rand()%3);
    }
	return 0;
}

int consumer(int *buf, int *cons, int sem_id, int k) 
{ 
    while(1) {
        sleep(rand()%5);
        int op_p, op_v;
        op_p = semop(sem_id, cons_start, 2);
        if (op_p == -1 )
        {
            perror( "Can't make p-operation!\n" );
            return 1;
        }
        
        if (++(*cons) == BUF){
            //exit(1);
            *cons = 0;
        }
        int value = *(buf + *cons);
        printf("Consumer №%d read: %d from pos %d\n", k, value, *cons);
        
        op_v = semop(sem_id, cons_end, 2);
        if (op_v == -1 )
        {
            perror( "Can't make v-operation!\n" );
            return 1;
        }
    }
	return 0;
}

int main(void)
{
	setbuf(stdout, NULL);
	int n = PROD + CONS, perms = S_IRWXU | S_IRWXG | S_IRWXO;
	printf("Parent-id: %d\n", getpid());
	
	int fd = shmget(IPC_PRIVATE, (BUF + 2) * sizeof(int), IPC_CREAT | perms);
	if (fd == -1)
	{
		perror("shmget"); 
		return 1;
	}
	int *shbuf = (int *) shmat(fd, 0, 0);
	if (shbuf == (int *) -1) 
	{
		perror("shmat");
		return 1;
	}
	int *shprod = shbuf + BUF, *shcons = shbuf + BUF + 1;
	*shbuf = *shprod = *shcons = 0;
	int semid = semget(IPC_PRIVATE, 3, perms);
	if (semid == -1) 
	{
		perror("semget");
		return 1;
	}
	semctl(semid, 0, SETVAL, 0); 
	semctl(semid, 1, SETVAL, BUF); 
    semctl(semid, 2, SETVAL, 1); 
	
	pid_t forks[n];
	for (int i = 0; i < n; i ++)
	{
		if ((forks[i] = fork()) == -1)
		{
			perror("Can't fork.");
			return 1;
		}
		else if (forks[i] == 0)
		{
			srand(time(NULL));
			if (i < PROD)
			{
				printf("forked producer: %d\n", getpid());
			
				producer(shbuf, shprod, semid, i);
			}
			else
			{
				printf("forked consumer: %d\n", getpid());
			 
				consumer(shbuf, shcons, semid, i - PROD);
			}
			return 0;
		}
	}
	
	int status;
	for (int i = 0; i < n; i++)
	{
		wait(&status);
		if (!WIFEXITED(status))
			printf("exit-error, code = %d\n", status);
	}
	if (shmdt(shbuf) == -1)
	{
		perror("shmdt" );
		return 1;
	}
	return 0;
}