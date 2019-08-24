#include <stdio.h>
#include <pthread.h>
#include "../common/err.h"

void *thrn1(void *);
void *thrn2(void *);

typedef struct thread_ret {
    int code;
    char *msg;
} t_ret;

// static t_ret ret;

int main(void)
{
    int err;
    t_ret ret;
    t_ret *tret;
    pthread_t tid1, tid2;
    if (pthread_create(&tid1, NULL, thrn1, &ret) != 0) {
        printf("cant create thread\n");
        return 1;
    }

    if (pthread_create(&tid2, NULL, thrn2, &ret) != 0) {
        printf("cant create thread\n");
        return 1;
    }

    err = pthread_join(tid1, (void *)&tret);
    printf("thread 1 exit code %ld, %s\n", ret.code, ret.msg);

    err = pthread_join(tid2, (void *)&tret);
    printf("thread 2 exit code %ld, %s\n", ret.code, ret.msg);
}

void *thrn1(void *arg)
{
    printf("thread 1 running\n");
    ((t_ret *)arg)->code = 1;
    ((t_ret *)arg)->msg = "thread-1 exit";
    return (void *)0;
}

void *thrn2(void *arg)
{
    printf("thread 2 running\n");
    ((t_ret *)arg)->code = 2;
    ((t_ret *)arg)->msg = "thread-2 exit";
    return (void *) 0;
}
