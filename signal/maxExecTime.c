#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_alrm(int signo);

int main(void)
{
    int n;
    char line[4096];
    if (signal(SIGALRM, sig_alrm) == SIG_ERR) {
        printf("signal(SIGALRM) error");
        return 1;
    }

    alarm(5);
    if ((n = read(STDIN_FILENO, line, 4096)) < 0) {
        printf("read error");
        return 1;
    }
    alarm(0);

    write(STDOUT_FILENO, line, n);
    return 0;
}

void sig_alrm(int signo)
{
    printf("SIGALRM raise\n");
}