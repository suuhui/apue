#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

static void f(int, int, int, int);
static void f1();

static jmp_buf jmpbuffer;
static int globval;

int main(void)
{
    int autoval;
    register int regval;
    volatile int volatval;
    static int statval;
    globval = 1;
    autoval = 2;
    regval = 3;
    volatval = 4;
    statval = 5;

    if (setjmp(jmpbuffer) != 0) {
        printf("after longjmp:\n");
        printf("globval=%d, autoval=%d, regval=%d, volatval=%d, statval=%d\n",
            globval, autoval, regval, volatval, statval);
            exit(0);
    }

    globval = 90;
    autoval = 91;
    regval = 92;
    volatval = 93;
    statval = 94;
    f(autoval, regval, volatval, statval);
}

static void f(int autoval, int regval, int volatval, int statval)
{
    printf("in f():\n");
    printf("globval=%d, autoval=%d, regval=%d, volatval=%d, statval=%d\n",
        globval, autoval, regval, volatval, statval);
    f1();
}

static void f1()
{
    longjmp(jmpbuffer, 1);
}