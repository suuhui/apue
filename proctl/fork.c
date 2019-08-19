#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int globval = 5;
char buf[] = "a write to stdout\n";

int main(void)
{
    int var;
    pid_t pid;
    const char *name = "envname";

    var = 99;
    // 将长度减1是为了避免将null字节输出
    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        printf("write error\n");
        return 1;
    }

    printf("before fork, envname=%s\n", getenv(name));
    if ((pid = fork()) < 0) {
        printf("fork error\n");
        return 1;
    } else if (pid == 0) {
        putenv("envname=helloenv");
        globval++;
        var++;
    } else {
        sleep(2);
    }
    printf("pid=%ld, glob=%d, var=%dm envname=%s\n", (long)getpid(), globval, var, getenv(name));
    return 0;
}