#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../lib/err.h"

char *env_init[] = {"USER=unknow", "PATH=/tmp", NULL};

int main(int argc, char *argv[])
{
    pid_t pid;
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        if (execle("/home/vagrant/www/apue/proctl/echoall", "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
            printf("exec error\n");
            exit(1);
        }
    }

    if (waitpid(pid, NULL, 0) < 0) {
        printf("wait error\n");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(1);
    } else if (pid == 0) {
        if (execlp("echoall", "echoall", "only one arg", (char *)0) < 0) {
            err_sys("exec2 error");
            exit(1);
        }
    }
    exit(0);
}