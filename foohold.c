#include <stdlib.h>
#include <pthread.h>

struct foo {
    int f_count;
    pthread_mutex_t f_mutex;
    int f_id;
}

struct foo *foo_alloc(int id)
{
    struct foo *fp;

    if ((fp = malloc(sizeof(struct foo))) == NULL) {
        return fp;
    }
    fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_mutex, NULL) != 0) {
        free(fp);
        return NULL;
    }
    return fp;
}

void foo_hold(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_mutex);
    fp->f_count++;
    pthread_mutex_unlock(&fp->f_mutex);
}

void foo_release(struct foo *fp)
{
    pthread_mutex_lock(&fp->f_mutex);
    if (--fp->f_count == 0) {
        pthread_mutex_unlock(&fp->f_mutex);
        pthread_mutex_destroy(&fp->f_mutex);
        free(fp);
        reutrn;
    } else {
        pthread_mutex_unlock(&fp->f_mutex);
    }
}