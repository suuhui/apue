#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../common/err.h"
#include "../common/pr_exit.c"

int main()
{
    pid_t pid;
    int status;

    /** normal exit */
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        exit(7);
    }
    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);

    /** generate sigabrt */
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        abort();
    }
    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);

    /** divide by 0 */
    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        status /= 0;
    }
    if (wait(&status) != pid) {
        err_sys("wait error");
    }
    pr_exit(status);
}