#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <time.h>
#include "./pr_mask.c"
#include "../common/err.h"

void sig_usr1(int signo);
void sig_alrm(int signo);
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

int main(void)
{
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        err_sys("signal(SIGLARM) error");
    }
    if (signal(SIGUSR1, sig_usr1) == SIG_ERR) {
        err_sys("signal(SIGUSR1) error");
    }

    pr_mask("start main: ");
    if (sigsetjmp(jmpbuf, 1)) {
        pr_mask("end main: ");
        return 0;
    }

    canjump = 1;

    for (; ;) {
        pause();
    }
}

void sig_usr1(int signo)
{
    time_t starttime;
    if (canjump == 0) {
        return;
    }

    pr_mask("start sig_usr1: ");
    alarm(3);
    starttime = time(NULL);
    for (; ;) {
        if (time(NULL) > starttime + 5) {
            break;
        }
    }
    pr_mask("end sig_usr1: ");
    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

void sig_alrm(int signo)
{
    pr_mask("in sig_alrm: ");
}
