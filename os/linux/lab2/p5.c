#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int flag = 0;

void catch_sis(int sis_num) {
    signal(sis_num, catch_sis);
    printf("catch_sis %d \n", sis_num);
    flag = 1;
}

int main(void) {
    setbuf(stdout, NULL);

    //signal(SIGTERM, catch_sis); //cntr+z
    signal(SIGINT, catch_sis); //ignore
    signal(SIGSEGV, SIG_DFL); //default

    sleep(2);

    char msg2[][16] = {"message1","message2"};
    char msg[] = "message";
    char buf[16];
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
            printf("child[%d]: pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
            if (flag) {
                close(mypipe[0]);
                write(mypipe[1], msg2[i], sizeof(msg));
                //printf("child[%d]: pid=%d; ppid=%d; gid=%d;\n", i, getpid(), getppid(), getgid());
            }
            return 0;
        } else {
            printf("parent: pid=%d, child[%d]=%d, idg=%d\n", getpid(), i, childpid[i], getgid());
            /*wait(&status);
            if (WIFEXITED(status)) {
                printf("exit-normal, code = %d\n",WEXITSTATUS(status));
            } else {
                printf("exit unnormal");
            }*/
            if (flag) {
                close(mypipe[1]);
                read(mypipe[0], buf, sizeof(buf));
                printf("parent msg: %s\n", buf);
            }
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