#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status = 0;
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        printf("pid дочернего процесса - %d, ppid дочернего процесса - %d\n", getpid(), getppid());
        exit(0);
    }
    else {
        wait(&status);
        printf("pid родительского процесса - %d, ppid  процесса - %d\n", getpid(), getppid());
        wait(&status);
        printf("Статус завершения процесса: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
