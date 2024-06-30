#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define _XOPEN_SOURCE 700

int main() {
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        perror("SIGPROCMASK");
        exit(0);
    }

    while (1) {
        pause();
    }

    return 0;
}