#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void setFl(int fd, int flag)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("get file flag error\n");
        exit(-1);
    }
    val |= flag;
    if (fcntl(fd, F_SETFL, val) < 0) {
        printf("set file flag error\n");
        exit(-1);
    }
}

void clrFl(int fd, int flag)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("get file flag error\n");
        exit(-1);
    }
    val &= ~flag;
    if (fcntl(fd, F_SETFL, val) < 0) {
        printf("clear file flag error\n");
        exit(-1);
    }
}
