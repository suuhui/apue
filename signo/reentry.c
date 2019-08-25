#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include "../lib/error.c"

static void my_alarm(int signo)
{
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        err_sys("getpwnam(root) error");
    }
    alarm(1);
}

int main(void)
{
    struct passwd *mysql;
    signal(SIGALRM, my_alarm);
    alarm(1);
    for (; ;) {
        if ((mysql = getpwnam("mysql")) == NULL) {
            err_sys("getpwnam(mysql) error");
        }
        if (strcmp(mysql->pw_name, "_mysql") != 0) {
            printf("return value corrupted! pw_name=%s\n", mysql->pw_name);
        }
    }
}