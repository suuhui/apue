#include <stdio.h>
#include <signal.h>
#include "../common/err.h"
#include "pr_mask.c"

int main(void)
{
    int i = 0;
    sigset_t newmask, oldmask;

    sigemptyset(&newmask);
    sigaddset(&newmask, SIGQUIT);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
        err_sys("SIG_BLOCK error");
    }
    i++;
    pr_mask("in critical region: ");

    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
        err_sys("SIG_SETMASK error");
    }
    pause();

    i++;
    printf("i=%d\n");
    return 0;
}