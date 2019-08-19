#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int val, fd;
    if (argc != 2) {
        printf("usage: a.out <descriptor>\n");
        return 1;
    }
    fd = atoi(argv[1]);
    if ((val = fcntl(fd, F_GETFL, 0)) < 0) {
        printf("fcntl error\n");
        return 1;
    }
    switch (val & O_ACCMODE) {
        case O_RDONLY:
            printf("read only\n");
            break;
        case O_WRONLY:
            printf("write only\n");
            break;
        case O_RDWR:
            printf("read write\n");
            break;
        default:
            printf("unkonwn access mode\n");
            return 1;
    }
    if (val & O_APPEND) {
        printf("append\n");
    }
    if (val & O_NONBLOCK) {
        printf("nonblock\n");
    }
    if (val & O_SYNC) {
        printf("synchronous write");
    }
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)
    if (val & O_FSYNC) {
        printf("synchronous writes\n");
    }
#endif
    printf("\n");
    exit(0);
}