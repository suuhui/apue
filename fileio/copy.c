#include <stdio.h>
#include <unistd.h>

#define MAX 32768

int main(void)
{
    int n;
    char buf[MAX];

    while ((n = read(STDIN_FILENO, buf, MAX)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            printf("write error\n");
            return -1;
        }
    }
    if (n < 0) {
        printf("write error\n");
        return -1;
    }
    return 0;
}