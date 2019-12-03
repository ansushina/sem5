//производство-потребление 

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int N = 10;
const int COUNT = 10;

#define SB 0
#define SE 1
#define SF 2

#define P -1
#define V 1

const int perms = IPC_CREAT|S_IRWXU|S_IRWXG|S_IRWXO;

struct sembuf prod_start[2] = {{SE, P, 0}, {SF, P, 0}};
struct sembuf prod_end[2] =   {{SB, V, 0}, {SF, V, 0}};
struct sembuf con_start[2] =  {{SF, P, 0}, {SB, P, 0}};
struct sembuf con_end[2] =    {{SB, V, 0}, {SE, V, 0}};

static int sem_id; 
static int* shm;
static int* shm_prod; 
static int* shm_cons;

void producer(int k) {
    sleep(rand()%5);

	semop(sem_id, prod_start, 2);
	//sh_buf[*sh_pos] = rand()%10; 
	printf("Producer%d %d\n", k, shm[*shm_prod]);
	(*shm_prod)++;
	semop(sem_id, prod_end, 2);
	
}

void consumer(int k) {
    sleep(rand()%5);
    semop(sem_id, con_start, 2);
	//(*sh_pos)--;
	printf("Consumer%d %d\n", k, sh_buf[*sh_pos]);
	semop(sem_id, con_end, 2);
			
}

int main(void) {
    //создаем набор симафоров 
    int shm_id = shmget(100,(N+1)* sizeof(int), perms);
    if (shm_id == -1) {
        perror('Shared memory error! \n');
        exit(1);
    }

    shm = (int *) shmat(shm_id, 0, 0);
    if (shm == (int *)-1) {
        perror("Can't attach memory!\n");
    }

    sem_id = semget(100, 3, perms);
    if (sem_id == -1)  {
        perror("Semget error!\n");
        exit(1);
    }

    semctl(sem_id, SE, SETVAL, N); 
	semctl(sem_id, SB, SETVAL, 1); 
    semctl(sem_id, SF, SETVAL, 0); 
    
    pid_t pid;
	if ((pid = fork()) == -1)
	{
		printf("Can't fork!\n");
		exit(1);
	}
	if (pid == 0)
	{
		int k = 0;
		while (k < COUNT)
		{
			producer(k);
			k++;
		}
        exit(0);
	}
	else 
	{
		int k = 0;
		while (k < COUNT)
		{
			consumer(k);
			k++;
		}
	}


    return 0;
}