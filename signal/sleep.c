#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void sig_alrm1(int signo)
{
}

/**
 * 该版本有三个问题
 * 1. 后一次调用会清除前一次调用的alarm
 * 2. 修改了SIGALRM的处理方式；调用前必须保存对信号的处理方式，返回时再恢复
 * 3. alarm和pause之间存在竞争关系；pause之前alarm就超时的话进程会永久挂起
 */
unsigned int sleep1(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm1) == SIG_ERR) {
        return seconds;
    }
    alarm(seconds);
    pause();
    return alarm(0);
}

static jmp_buf env_alrm;
void sig_alrm2(int signo)
{
    longjmp(env_alrm, 1);
}

/**
 * 解决了alarm和pause的竞争关系问题，但是带来另外一个问题
 * 如果SIGALRM中断了某个其他信号的处理程序，调用longjmp会
 * 提前终止改信号处理程序
 */
unsigned int sleep2(unsigned int seconds)
{
    if (signal(SIGALRM, sig_alrm2) == SIG_ERR) {
        return seconds;
    }
    if (setjmp(env_alrm) == 0) {
        alarm(seconds);
        pause();
    }
    return alarm(0);
}