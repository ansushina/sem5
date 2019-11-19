#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    setbuf(stdout, NULL);
    int n = 2;
    pid_t childpid[n];
    int status;
    
    for (int i = 0; i < n; i++) {
        if ((childpid[i] = fork()) == -1) {
            perror("Cant fork!\n");
            exit(1);
        } else if (childpid[i] == 0){
            printf("child[%d]: pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
            return 0;
        } else {
            printf("parent: pid=%d, child[%d]=%d, idg=%d\n", getpid(), i, childpid[i], getgid());
            /*wait(&status);
            if (WIFEXITED(status)) {
                printf("exit-normal, code = %d\n",WEXITSTATUS(status));
            } else {
                printf("exit unnormal");
            }*/
        }
    }

    wait(&status);
            if (WIFEXITED(status)) {
                printf("exit-normal, code = %d\n",WEXITSTATUS(status));
            } else {
                printf("exit unnormal");
            }

    return 0;
}