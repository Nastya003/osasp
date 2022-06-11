#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <wait.h>
#include <time.h>
#include <stdlib.h>

#define CHILD_COUNT 2

int childPids[CHILD_COUNT];
int childIndex = 0;
int mesNum;


void getTime() {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    time_t sec = ts.tv_sec;
    int ms = ts.tv_nsec / 1e6;

    struct tm *tmp = localtime(&sec);
    printf("%02i:%02i:%02i:%03i", tmp->tm_hour,
           tmp->tm_min, tmp->tm_sec, ms);
}

void showInfo(int childIndex, char *status, int sigNum) {

    printf("%-5d %5d %5d ", mesNum++, getpid(), getppid());
    getTime();
    printf(" child №%d %3s SIGUSR%d\n", childIndex, status, sigNum);
}

int getChildIndex(pid_t childPid) {
    for (int i = 0; i < CHILD_COUNT; ++i) {
        if(childPids[i] == childPid)
            return i;
    }
    return -1;
}

void parentAction(int sig, siginfo_t *sigInfo, void *_) {
    showInfo(getChildIndex(sigInfo->si_pid), "put", 2);

    if(mesNum == 101) {
        kill(getppid(), SIGTERM);
        return;
    }

    struct timespec t = {.tv_nsec = 100e6, .tv_sec = 0};
    nanosleep(&t, NULL);

    kill(0, SIGUSR1);
}

void childAction(int sig) {
    showInfo(childIndex, "get", 1);
    kill(getppid(), SIGUSR2);
}

void parentTerm(int sig) {
    signal(SIGTERM, SIG_IGN);
    kill(0, SIGTERM);
    signal(SIGTERM, parentTerm);

    while(wait(NULL) != -1 || errno == EINTR);
    if(errno != ECHILD) {
        perror("wait");
        exit(-1);
    }

    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = parentAction;
    sigaction(SIGUSR2, &sa, NULL);

    signal(SIGUSR1, SIG_IGN);
    signal(SIGTERM, parentTerm);

    pid_t pid = 1;
    for (int i = 0; i < CHILD_COUNT && pid > 0; ++i) {
        switch (pid = fork()) {
            case -1: {
                perror("fork");
                for (int j = 0; j < i; ++j) {
                    kill(childPids[j], SIGKILL);
                }

                return -1;
            }
            case 0: {
                printf("I'm child #%d. My pid is %d. My ppid is %d. ", childIndex, getpid(), getppid());
                putc('\n', stdout);

                signal(SIGUSR1, childAction);
                break;
            }
            default: {
                childPids[i] = pid;
                childIndex++;
                break;
            }
        }
    }

    if(pid > 0) {
        sleep(1);
        kill(0, SIGUSR1);
    }

    while(1);
}
