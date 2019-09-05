#include <stdio.h>
#include "../lib/err.h"
#include "sleep.c"

void sig_int(int signo);

int main(void)
{
    unsigned int unslept;
    if (signal(SIGINT, sig_int) == SIG_ERR) {
        err_sys("signal(SIGINT) error");
    }
    unslept = sleep2(5);
    printf("sleep2 return: %u\n", unslept);
    return 0;
}

void sig_int(int signo)
{
    int i, j;
    volatile int k;

    printf("\nsig_int start\n");
    for (i = 0; i < 3000000; i++) {
        for (j = 0; j < 400000; j++) {
            k += i * j;
        }
    }
    printf("sig_int finished\n");
}