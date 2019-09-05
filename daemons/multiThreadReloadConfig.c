#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include "singleinstance.c"
#include "daemonize.c"
#include "../lib/err.h"

sigset_t mask;
extern int already_running(void);

void reload(void)
{

}

void *thr_fn(void *arg)
{
    int err, signo;
    for (; ;) {
        err = sigwait(&mask, &signo);
        if (err != 0) {
            syslog(LOG_ERR, "sigwait failed");
            exit(1);
        }
        switch (signo) {
        case SIGHUP:
            syslog(LOG_INFO, "Reload configuration file");
            reload();
            break;
        case SIGTERM:
            syslog(LOG_INFO, "got SIGTERM; exiting");
            exit(0);
        default :
            syslog(LOG_INFO, "unexpected signal %d\n", signo);
        }
    }
    return 0;
}

int main(int argc, char *argv[]) 
{
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa; 

    if ((cmd = strrchr(argv[1], '/')) == NULL) {
        cmd = argv[1];
    } else {
        cmd++;
    }

    daemonize(cmd);

    if (already_running()) {
        syslog(LOG_ERR, "daemon already running");
        exit(1);
    }

    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0) {
        err_quit("%s: can't restore SIGHUP default");
    }
    sigfillset(&mask);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0) {
        err_exit(err, "SIG_BLOCK error");
    }

    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0) {
        err_exit(err, "can't create thread");
    }

    exit(0);
}