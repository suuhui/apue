#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (open("tmpfile", O_RDONLY) < 0) {
        printf("open error\n");
        return -1;
    }
    if (unlink("tmpfile") < 0) {
        printf("unlink error: %s\n", strerror(errno));
        return -1;
    }
    printf("file unlinked\n");
    sleep(15);
    printf("done\n");
    return 0;
}