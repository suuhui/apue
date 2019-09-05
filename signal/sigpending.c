#include <stdio.h>
#include <signal.h>
#include "../lib/err.h"

void sig_quit(int);

int main(void)
{
    sigset_t newset, oldset, pendset;

    if (signal(SIGQUIT, sig_quit) == SIG_ERR) {
        err_sys("signal(SIG_QUIT) error");
    }

    sigemptyset(&newset);
    sigaddset(&newset, SIGQUIT);

    if (sigprocmask(SIG_BLOCK, &newset, &oldset) < 0) {
        err_sys("SIG_BLOCK error");
    }

    sleep(5);

    if (sigpending(&pendset) < 0) {
        err_sys("sigpending error");
    }
    if (sigismember(&pendset, SIGQUIT) < 0) {
        printf("\nSIGQUIT pending\n");
    }

    if (sigprocmask(SIG_SETMASK, &oldset, NULL)) {
        err_sys("SIG_SETMASK error");
    }
    printf("SIGQUIT unblocked\n");
    sleep(5);
    return 0;
}

void sig_quit(int signo)
{
    if (signo == SIGQUIT) {
        printf("\ncaught SIGQUIT\n");
    }
}
