#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>  

int main() {

    int fpipe[2];
    if (pipe(fpipe) < 0) {
        perror("pipe");
        exit(0);
    }
    int pid = fork();
    if (pid == 0) {
        close(fpipe[1]);
        char msg[1024];
        int ticker = 0;
        while ((ticker = read(fpipe[0], msg + ticker, sizeof(msg) - ticker)) > 0) {
            msg[ticker] = '\0';
            printf("Сообщение получено: %s\n", msg);
            exit(0);
        }
        close(fpipe[0]);
    } 
    else {
        close(fpipe[0]);
        char msg[] = "Hi!";
        if (write(fpipe[1], msg, strlen(msg) + 1) == -1) {
            perror("Сообщение не получено");
            exit(0);
        }
        close(fpipe[1]);
    }
    return 0;
}
