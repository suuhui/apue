#include <stdio.h>
#include <sys/stat.h>

// ./a.out /etc/passwd /etc /dev/log /dev/tty /var/lib/oprofile/opd_pipe /dev/sda /dev/fd

int main(int argc, char *argv[])
{
    int i;
    struct stat buf;

    for (i = 1; i < argc; i++) {
        if (lstat(argv[i], &buf) < 0) {
            printf("lstat error. pathname: %s\n", argv[i]);
            continue;
        }
        if (S_ISREG(buf.st_mode)) {
            printf("%s is regular file\n", argv[i]);
            continue;
        }
        if (S_ISDIR(buf.st_mode)) {
            printf("%s is directory file\n", argv[i]);
            continue;
        }
        if (S_ISCHR(buf.st_mode)) {
            printf("%s is character special file\n", argv[i]);
            continue;
        }
        if (S_ISBLK(buf.st_mode)) {
            printf("%s is block file\n", argv[i]);
            continue;
        }
        if (S_ISFIFO(buf.st_mode)) {
            printf("%s is fifo file\n", argv[i]);
            continue;
        }
        if (S_ISLNK(buf.st_mode)) {
            printf("%s is link file\n", argv[i]);
            continue;
        }
        if (S_ISSOCK(buf.st_mode)) {
            printf("%s is socket file\n", argv[i]);
            continue;
        }
    }
    return 0;
}