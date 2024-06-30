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
    sa.sa_handler = my_handler; 
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    while (1) {
        pause();
    }
    return 0;
}