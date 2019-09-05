#include <stdio.h>
#include <fcntl.h>
#include "../lib/common.c"
#include "../lib/err.h"
#include "../lib/tellwait.c"
#include "../lib/flock_reg.c"

static void lockabyte(const char *name, int fd, off_t offset)
{
    if (writew_lock(fd, offset, SEEK_SET, 1) < 0) {
        err_sys("%s: writew_lock error\n", name);
    }

    printf("%s: got the lock, byte %lld\n", name, (long long) offset);
}

int main(void)
{
    int fd;
    pid_t pid;

    if ((fd = creat("templock", FILE_MODE)) < 0) {
        err_sys("creat error");
    }
    if (write(fd, "ab", 2) != 2) {
        err_sys("write error");
    }

    TELL_WAIT();
    if ((pid = fork()) < 0) {
        err_sys("fork eror");
    } else if (pid == 0) {
        lockabyte("child", fd, 0);
        TELL_PARENT(getppid());
        WAIT_PARENT();
        lockabyte("child", fd, 1);
    } else {
        lockabyte("parent", fd, 1);
        TELL_CHILD(pid);
        WAIT_CHILD();
        lockabyte("parent", fd, 0);
    }
    return 0;
}
