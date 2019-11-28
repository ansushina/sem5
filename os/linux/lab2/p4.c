#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    setbuf(stdout, NULL);
    char msg2[][8] = {"mes1","mes2"};
    char buf[40] = "";
    int mypipe[2];
    int n = 2;
    pid_t childpid[n];
    int status;

    if (pipe(mypipe) == -1) {
        perror("pipe!\n");
        exit(1);
    }
    
    for (int i = 0; i < n; i++) {
        if ((childpid[i] = fork()) == -1) {
            perror("Cant fork!\n");
            exit(1);
        } else if (childpid[i] == 0){
            close(mypipe[0]);
            write(mypipe[1], msg2[i], sizeof(msg2[i]));
            printf("child[%d]: pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
            return 0;
        } else {
            printf("parent: pid=%d, child[%d]=%d, idg=%d\n", getpid(), i, childpid[i], getgid());
    

        }
    }


    for (int i = 0; i < n; i++) {
        wait(&status);
            if (WIFEXITED(status)) {
                printf("exit-normal, code = %d\n",WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("exit-signal, code = %d\n",WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped, code = %d\n",WSTOPSIG(status));
            } else {
                printf("exit unnormal");
            }
    }
    close(mypipe[1]);
    read(mypipe[0], buf, sizeof(buf));
    printf("parent msg: ");
    for (int i = 0 ; i < sizeof(buf); i++) {
        printf("%c", buf[i]);
    }
    printf("\n");
    return 0;
}