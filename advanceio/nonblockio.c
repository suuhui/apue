#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "../lib/fl.c"

char buf[500000];

int main(void)
{
    int ntowrite, nwrite, writenum, errnum;
    char *ptr;

    ntowrite = read(STDIN_FILENO, buf, sizeof(buf));
    fprintf(stderr, "read %d bytes\n", ntowrite);

    setFl(STDOUT_FILENO, O_NONBLOCK);

    writenum = errnum = 0;
    ptr = buf;

    while (ntowrite > 0) {
        errno = 0;
        nwrite = write(STDOUT_FILENO, ptr, ntowrite);
        fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

        if (nwrite > 0) {
            ptr += nwrite;
            ntowrite -= nwrite;
        } else {
            errnum++;
        }
        writenum++;
    }

    clrFl(STDOUT_FILENO, O_NONBLOCK);
    fprintf(stderr, "write num = %d, errnum = %d\n", writenum, errnum);
    return 0;
}
