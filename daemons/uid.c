#include <stdio.h>
#include <unistd.h>

int main(void)
{
    uid_t uid;
    uid = getuid();
    printf("real uid: %ld\n", (long)uid);
    int i;
    for (i = 0; i < 1000; i++) {
        sleep(1);
        printf("sleep %s seconds\n", i);
    }
    return 0;
}
