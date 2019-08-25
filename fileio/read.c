#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char buf[20000];
    size_t st = 20000;
    ssize_t rs, count = 0;


    fd = open("testOpen.txt", O_RDWR | O_CREAT);

    do {
        rs = read(fd, buf, st);
        if (errno > 0) {
            printf("fd is: %d; errno is: %d; err msg is: %s\n", fd, errno, strerror(errno));
        } else {
            printf("read num: %ld; str: %s\n", rs, buf);
        }
        if (rs == -1 || rs == 0) {
            break;
        }
        count += rs;
        printf("count is: %ld\n", count);
    } while(rs == -1 || rs == 0);
    printf("count is: %ld\n", count);
    return 0;
}