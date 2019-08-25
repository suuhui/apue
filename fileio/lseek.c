#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(int argc, char *argv[])
{
    int fd;
    off_t pos;
    const char *path = "testOpen.txt";
    fd = open(path, O_RDWR | O_CREAT);
    // 确定当前偏移量
    pos = lseek(fd, 0, SEEK_CUR);
    printf("current position: %lld\n", pos);

    if (write(fd, buf1, 10) != 10) {
        printf("buf1 write error\n");
        return -1;
    }

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        printf("lseek error\n");
        return -1;
    }

    if (write(fd, buf2, 10) != 10) {
        printf("buf2 write error\n");
        return -1;
    }

    return 0;
}