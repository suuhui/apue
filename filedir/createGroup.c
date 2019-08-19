/**
 * 设置了SUID后，创建文件看文件所属
 */
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (open("./group.log", O_CREAT | O_EXCL) < 0) {
        printf("open error\n");
        return 1;
    }
    return 0;
}