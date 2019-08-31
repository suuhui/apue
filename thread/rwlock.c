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
    err = pthread_rwlock_init(&qp->qLock, NULL);
    if (err != 0) {
        return err;
    }
    qp->qHead = NULL;
    qp->qTail = NULL;
    return 0;
}

void jobInsert(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->qLock);
    jp->prevJob = NULL;
    if (qp->qHead == NULL) {
        qp->qTail = jp;
    } else {
        qp->qHead->prevJob = jp;
    }
    jp->nextJob = qp->qHead;
    qp->qHead = jp;
    pthread_rwlock_unlock(&qp->qLock);
}

void jobAppend(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->qLock);
    jp->nextJob = NULL;
    jp->prevJob = qp->qTail;
    if (qp->qTail == NULL) {
        qp->qHead = jp;
    } else {
        qp->qTail->nextJob = jp;
    }
    qp->qTail = jp;
    pthread_rwlock_unlock(&qp->qLock);
}

void jobRemove(struct queue *qp, struct job *jp)
{
    pthread_rwlock_wrlock(&qp->qLock);
    if (jp == qp->qHead) {
        qp->qHead = jp->nextJob;
        if (jp == qp->qTail) {
            //如果是tail，说明只有一个；jp->nextJob == NULL，无需再指定jp->nextJob->prevJob
            qp->qTail = NULL;
        } else {
            jp->nextJob->prevJob = jp->prevJob;
        }
    } else if (jp == qp->qTail) {
        // jp不可能等于qHead,因此qHead不变
        qp->qTail = jp->prevJob;
        jp->prevJob->nextJob = jp->nextJob;
    } else {
        jp->prevJob->nextJob = jp->nextJob;
        jp->nextJob->prevJob = jp->prevJob;
    }
    pthread_rwlock_unlock(&qp->qLock);
}

struct job *jobFind(struct queue *qp, pthread_t tid)
{
    struct job *jp;
    if (pthread_rwlock_rdlock(&qp->qLock) != 0) {
        return NULL;
    }
    
    for (jp = qp->qHead; jp != NULL; jp = jp->nextJob) {
        if (pthread_equal(jp->tid, tid)) {
            break;
        }
    }

    pthread_rwlock_unlock(&qp->qLock);
    return jp;
}
