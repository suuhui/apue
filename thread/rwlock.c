#include <stdlib.h>
#include <pthread.h>

struct job {
    pthread_t tid;
    struct job *nextJob;
    struct job *prevJob;
};

struct queue {
    struct job *qHead;
    struct job *qTail;
    pthread_rwlock_t qLock;
};

int queueInit(struct queue *qp)
{
    int err;
    qp->qHead = NULL;
    qp->qTail = NULL;
    if ((err = pthread_rwlock_init(&qp->qLock)) != 0) {
        return err;
    }
    return 0;
}

void jobInsert(struct queue *qp, struct job *jp)
{
    int err;
    err = pthread_rwlock_wrlock(&qp->qLock);
    if (err != 0) {
        return;
    }
    jp->nextJob = qp->qHead;
    jp->prevJob = NULL;
    if (qp->qHead == NULL) {
        qp->qTail = jp;
    } else {
        qp->qHead->prevJob = jp;
    }
    qp->qHead = jp;
    pthread_rwlock_unlock(&qp->qLock);
}

void jobAppend(struct queue *qp, struct job *jp)
{
    int err;
    err = pthread_rwlock_wrlock(&qp->qLock);
    jp->nextJob = NULL;
    
}

void jobRemove(struct queue *qp, struct job *jp)
{

}

struct job *jobFind(struct queue *qp, pthread_t tid)  
{

}
