#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define _XOPEN_SOURCE 700

void my_handler(int signum) {
    if (signum == SIGUSR1) {  
        printf("SIGUSR1 получен\n");
    }
}

int main() {
    struct sigaction sa;
    sigset_t sigset;
    sa.sa_handler = my_handler; 
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("SIGACTION");
        exit(0);
    }

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGUSR1);
    printf("SIGUSR1 пока не обнаружен");
    int sig;

    while (1) {
        if (sigwait(&sigset, &sig) == -1) {
            perror("SIGWAIT");
            exit(0);
        }
        if (sig == SIGUSR1) {
            printf("SIGUSR1 получен\n");
        }
    }

    return 0;
}