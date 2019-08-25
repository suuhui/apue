#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *path = "testOpen.txt";
    char *errMsg;
    int fd1, fd2, fd3;
    fd1 = open(path, O_RDWR | O_CREAT);
    fd2 = open(path, O_RDWR | O_CREAT);
    errMsg = strerror(errno);
    printf("err msg: %s\n", errMsg);
    printf("fd1 is: %d; fd2 is: %d; fd3 is: %d\n", fd1, fd2, fd3);
    close(fd1);
    fd3 = open(path, O_RDWR | O_CREAT);
    fd3 = open(path, O_RDWR | O_CREAT);
    printf("fd1 is: %d; fd2 is: %d; fd3 is: %d\n", fd1, fd2, fd3);
}