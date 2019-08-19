#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void fn1();
static void fn2();

int main(void)
{
    atexit(fn1);
    atexit(fn2);
    _Exit(0);
}

static void fn1()
{
    printf("fn1\n");
}
static void fn2()
{
    printf("fn2\n");
}