#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include "../lib/err.h"

#define NTHR 8
#define NUM 16L
#define TNUM (NUM/NTHR)

long nums[NUM];
long snums[NUM];

pthread_barrier_t barrier;

int complong(const void *arg1, const void *arg2)
{
    long l1 = * (long *)arg1;
    long l2 = * (long *)arg2;

    if (l1 == l2) {
        return 0;
    } else if (l1 < l2) {
        return -1;
    } else {
        return 1;
    }
}

void *thr_fn(void *arg)
{
    long idx = (long)arg;
    qsort(&nums[idx], TNUM, sizeof(long), complong);
    pthread_barrier_wait(&barrier);
    return (void *)0;
}

void merge()
{
    long idx[NTHR];
    long i, minidx, sidx, num;
    for (i = 0; i < NTHR; i++) {
        idx[i] = i * TNUM;
    }

    for (sidx = 0; sidx < NUM; sidx++) {
        num = LONG_MAX;
        for (i = 0; i < NTHR; i++) {
            printf("sidx:%ld; idx[%ld]: %ld; nums[%ld]: %ld\n", sidx, i, idx[i], idx[i], nums[idx[i]]);
            if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)) {
                num = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        idx[minidx]++;
    }
}

int main()
{
    unsigned long i;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    srandom(1);
    for (i = 0; i < NUM; i++) {
        nums[i] = random();
    }
    gettimeofday(&start, NULL);
    //NTHR+1除了8个排序线程，还有主线程
    pthread_barrier_init(&barrier, NULL, NTHR+1);
    for (i = 0; i < NTHR; i++) {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0) {
            err_exit(err, "can't create thread");
        }
    }
    pthread_barrier_wait(&barrier);
    merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    printf("sort took %.4f seconds\n", elapsed);
    // for (i = 0; i < NUM; i++) {
    //     printf("%ld\n", snums[i]);
    // }
    return 0;
}