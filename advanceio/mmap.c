#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include "../lib/err.h"
#include "../lib/common.h"

#define COPYINCR (1024*1024*5)

/**
 * 在虚拟机上，跟宿主机做了目录映射，在映射的目录中，mmap写可能会失败
 */ 
int main(int argc, char *argv[])
{
    int fdin, fdout;
    void *src, *dst;
    size_t copysz;
    struct stat sbuf;
    off_t fsz = 0;

    if (argc != 3) {
        err_quit("usage: %s <fromfile> <tofile>\n", argv[0]);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0) {
        err_sys("can't open %s for reading\n", argv[1]);
    }

    if ((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0) {
        err_sys("can't create %s for writing\n", argv[2]);
    }

    /* get size of input file*/
    if (fstat(fdin, &sbuf) < 0) {
        err_sys("stat error\n");
    }
    /* set output file size */
    if (ftruncate(fdout, sbuf.st_size) < 0) {
        err_sys("ftruncate error\n");
    }

    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) <= COPYINCR) {
            copysz = sbuf.st_size - fsz;
        } else {
            copysz = COPYINCR;
        }

        if ((src = mmap(0, copysz, PROT_READ, MAP_SHARED, fdin, fsz)) == MAP_FAILED) {
            err_sys("mmap error for input");
        }

        if ((dst = mmap(0, copysz, PROT_READ | PROT_WRITE, MAP_SHARED, fdout, fsz)) == MAP_FAILED) {
            err_sys("mmap error for output");
        }

        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }
    return 0;
}