#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(void) {
    setbuf(stdout, NULL);
    pid_t cpid[5];

    for (int i = 0; i < 5; i++) {
        if ((cpid[i] = fork()) == -1) {
            perror("Cant fork!\n");
            exit(1);
	}
	else if (cpid[i] == 0) {
            printf("\n child[%d] before: pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
            sleep(2);
            printf("\n child[%d] after : pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
	    return 0;
        }  else {
           printf("parent: pid=%d, child[%d] = %d, idg=%d\n", getpid(), i, cpid[i], getgid());
        }
    }
    
    return 0;
}
