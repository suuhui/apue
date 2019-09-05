#include <stdio.h>
#include <signal.h>
// #include "../lib/common.c"
#include "../lib/err.h"

typedef void Sigfunc(int);

void sig_usr(int);

int main(void)
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) {
        err_sys("cant catch SIGUSR1");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) {
        err_sys("cant catch SIGUSR2");
    }
    for (; ;) {
        pause();
    }
}

void sig_usr(int signo)
{
    if (signo == SIGUSR1) {
        printf("received SIGUSR1\n");
    } else if (signo == SIGUSR2) {
        printf("received SIGUSR2\n");
    } else {
        printf("received signal %d\n", signo);
    }
}