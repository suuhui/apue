#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "../lib/err.h"
#include "../lib/path.c"

typedef Myfunc(const char *, const struct stat *, int);

static Myfunc myfunc;
static int myftw(char *, Myfunc *);
static int dopath(Myfunc *);
static long nreg, ndir, nblk, nfifo, nsock, nchr, nlink, ntot;

int main(int argc, char *argv[])
{
    int ret;
    if (argc != 2) {
        printf("Usage: ./a.out <starting-pathname>\n");
        return -1;
    }
    ret = myftw(argv[1], myfunc);
    ntot = nreg + ndir + nblk + nfifo + nsock + nchr + nlink;
    if (ntot == 0) {
        ntot = 1;
    }
    printf("total files: %ld\n", ntot);
    printf("regular files = %7ld, %5.2f%%\n", nreg, nreg*100.0 / ntot);
    printf("directory files = %7ld, %5.2f%%\n", ndir, ndir*100.0 / ntot);
    printf("block files = %7ld, %5.2f%%\n", nblk, nblk*100.0 / ntot);
    printf("char files = %7ld, %5.2f%%\n", nchr, nchr*100.0 / ntot);
    printf("fifo files = %7ld, %5.2f%%\n", nfifo, nfifo*100.0 / ntot);
    printf("socket files = %7ld, %5.2f%%\n", nsock, nsock*100.0 / ntot);
    printf("link files = %7ld, %5.2f%%\n", nlink, nlink*100.0 / ntot);
    return ret;
}

#define FTW_F 1 /* file other than directory */
#define FTW_D 2 /* directory */
#define FTW_DNR 3 /* directory that can't read */
#define FTW_NS 4 /* file that can't stat */

static char *fullpath;
static size_t pathlen;

static int myftw(char *pathname, Myfunc* func)
{
    fullpath = path_alloc(&pathlen); /* malloc PATH_MAX+1 bytes */
    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
            printf("realloc failed\n");
            exit(-1);
        }
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(Myfunc* func)
{
    struct stat statbuf;
    struct dirent *dirp;
    DIR *dp;
    int ret, n;
    if (lstat(fullpath, &statbuf) < 0) {
        return (func(fullpath, &statbuf, FTW_NS));
    }
    if (S_ISDIR(statbuf.st_mode) == 0) {
        return (func(fullpath, &statbuf, FTW_F));
    }
    // printf("full pathname: %s\n", fullpath);
    if ((ret = func(fullpath, &statbuf, FTW_D)) != 0) {
        return ret;
    }
    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > pathlen) {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL) {
            err_sys("realloc error");
        }
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL) {
        return (func(fullpath, &statbuf, FTW_DNR));
    }
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0) {
            break;
        }
    }
    fullpath[n-1] = 0;
    if (closedir(dp) < 0) {
        err_ret("can't close directory %s", fullpath);
    }
    return ret;
}

static int myfunc(const char *pathname, const struct stat *statptr, int type)
{
    switch (type) {
        case FTW_F:
            switch (statptr->st_mode & S_IFMT) {
                case S_IFREG: nreg++; break;
                case S_IFBLK: nblk++; break;
                case S_IFCHR: nchr++; break;
                case S_IFIFO: nfifo++; break;
                case S_IFLNK: nlink++; break;
                case S_IFSOCK: nsock++; break;
                case S_IFDIR: 
                    err_dump("for S_IFDIR for %s", pathname);
            }
            break;
        case FTW_D:
            ndir++;
            break;
        case FTW_DNR:
            err_ret("can't read directory %s", pathname);
            break;
        case FTW_NS:
            err_ret("stat error for %s", pathname);
            break;
        default:
            err_dump("unknow type %d for pathname %s", type, pathname);
    }
    return 0;
}
