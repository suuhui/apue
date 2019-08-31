#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXBUFSZ = 4096;

static pthread_once_t initflag = PTHREAD_ONCE_INIT;
static pthread_key_t key;
pthread_mutex_t envLock = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thr_init(void)
{
    pthread_key_create(&key, free);
}

char *getenv(const char *name)
{
    int i, len;
    char *envbuf;
    pthread_once(&initflag, thread_init);
    pthread_mutex_lock(&envLock);
    envbuf = (char *)pthread_getspecific(key);
    if (NULL == envbuf) {
        envbuf = malloc(MAXBUFSZ);
        if (NULL == envbuf) {
            pthread_mutex_unlock(&envLock);
            return NULL;
        }
        pthread_setspecific(key, envbuf);
    }

    for (i = 0; environ[i] != NULL; i++) {
        len = strlen(name);
        if (strncmp(environ[i], name, n) == 0 && environ[i][len] == '=') {
            strncpy(envbuf, &environ[i][len + 1], MAXBUFSZ - 1);
            pthread_mutex_unlock(&envLock);
            return envbuf;
        }
    }
    pthread_mutex_unlock(&envLock);
    return NULL;
}