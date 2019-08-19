#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./a.out <pathname>\n");
        return 1;
    }
    printf("uid: %d. euid: %d\n", getuid(), geteuid());
    if (access(argv[1], R_OK) < 0) {
        printf("access error for \"%s\"\n", argv[1]);
    } else {
        printf("read access ok.\n");
    }
    if (open(argv[1], O_RDONLY) < 0) {
        printf("open error for \"%s\"\n", argv[1]);
    } else {
        printf("read open ok\n");
    }
    return 0;
}