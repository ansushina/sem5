#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

#define READERS 5
#define WRITERS 3
#define MAX 10


#define ACTIVE_READERS 0	// активные читатели
#define WAIT_WRITERS 1	// ждущие писатели
#define ACTIVE_WRITERS 2	// активные писатели
#define WAIT_READERS 3    // ждущие читатели

struct sembuf start_reader[5]	= {{WAIT_READERS, 1, 0}, {WAIT_WRITERS,  0, 0}, {ACTIVE_WRITERS,  0, 0}, {WAIT_READERS, -1, 0}, {ACTIVE_READERS,  1, 0}};
struct sembuf stop_reader[1]	= {{ACTIVE_READERS, -1, 0}};  
struct sembuf start_writer[5] = {{WAIT_WRITERS,  1, 0}, {ACTIVE_WRITERS, 0, 0}, {ACTIVE_READERS,  0, 0}, {WAIT_WRITERS, -1, 0}, {ACTIVE_WRITERS,  1, 0}};      
struct sembuf stop_writer[1]  = {{ACTIVE_WRITERS,  -1, 0}};

void start_read(int sem_id) 
{ 
    semop(sem_id, start_reader, 5);
}

void stop_read(int sem_id) 
{ 
    semop(sem_id, stop_reader, 1); 
}

void start_write(int sem_id) 
{
  semop(sem_id, start_writer, 5);
}

void stop_write(int sem_id) 
{ 
    semop(sem_id, stop_writer, 1); 
}

int reader(int *shbuf, int sem_id, int k)
{
	if (!shbuf || sem_id == -1)
		return 1;
	
	while (*shbuf < MAX)
	{
		start_read(sem_id);
		printf("reader №%d: %d\n", k, *shbuf);
		stop_read(sem_id);
		sleep(rand()%5 + 1);
	}
	return 0;
}

int writer(int *shbuf, int sem_id, int k)
{
	if (!shbuf || sem_id == -1)
		return 1;
	
	while (*shbuf < MAX)
	{
		start_write(sem_id);
		*shbuf += 1;
		printf("writer №%d: %d\n", k, *shbuf);
		stop_write(sem_id);
		sleep(rand()%3 + 1);
	}
	return 0;
}

int main(void)
{
	setbuf(stdout, NULL);
	int n = READERS + WRITERS, perms = S_IRWXU | S_IRWXG | S_IRWXO;
	//printf("Parent-id: %d\n", getpid());
	
	int fd = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | perms);
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
	int semid = semget(IPC_PRIVATE, 4, perms);
	if (semid == -1) 
	{
		perror("semget");
		return 1;
	}
	
	*shbuf = 0;
	semctl(semid, 0, SETVAL, 0);
	semctl(semid, 1, SETVAL, 0);
	semctl(semid, 2, SETVAL, 0);
    semctl(semid, 3, SETALL, 0);
	
	pid_t forks[n], rc;
	for (int i = 0; i < n; i++)
	{
		if ((forks[i] = fork()) == -1)
		{
			perror("Can't fork");
			return 1;
		}
		else if (forks[i] == 0)
		{
			srand(time(NULL));
			sleep(1);
			if (i < WRITERS)
			{
				printf("forked writer: %d\n", getpid());
				rc = writer(shbuf, semid, i);
			}
			else
			{
				printf("forked reader: %d\n", getpid());
				rc = reader(shbuf, semid, i - WRITERS);
			}
			return rc;
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