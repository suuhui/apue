#include <stdio.h>
#include <stdlib.h>

static void myExit1(void);
static void myExit2(void);

int main(int argc, char *argv[])
{
    if (atexit(myExit1) != 0) {
        printf("cant register myExit1\n");
        exit(1);
    }
    if (atexit(myExit2) != 0) {
        printf("cant register myExit2\n");
        exit(1);
    }
    printf("maian is done\n");
    return 0;
}

static void myExit1()
{
    printf("register myExit1\n");
}

static void myExit2()
{
    printf("register myExit2\n");
}