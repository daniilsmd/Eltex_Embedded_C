#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    pid_t pid1, pid2, pid3, pid4, pid5;
    pid1 = fork();
    int wstatus = 0;
    
    if (pid1 == 0) {
        printf("pid 1-ого процесса - %d, ppid 1-ого процесса - %d\n", getpid(), getppid()); 
        pid3 = fork(); 
        if (pid3 == 0) {
            printf("pid 3-его процесса - %d, ppid 3-его процесса - %d\n", getpid(), getppid()); 
            sleep(1);
            printf("Завершение процесса 3\n");
            exit(0);
        }

        if (pid3 != 0) {
            pid4 = fork();
            if (pid4 == 0) {
                printf("pid 4-ого процесса - %d, ppid 4-ого процесса - %d\n", getpid(), getppid()); 
                sleep(1);
                printf("Завершение процесса 4\n");
                exit(0);
            }
        }
        wait(&wstatus);
        if (WIFEXITED(wstatus) != 0) {
            printf("Завершение процесса 1\n");
        } 
        else {
            printf("Процесс 1 не завершен\n");
        }
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        printf("pid 2-ого процесса - %d, ppid 2-ого процесса - %d\n", getpid(), getppid());  
        pid5 = fork();
        if (pid5 == 0) {
            printf("pid 5-ого процесса - %d, ppid 5-ого процесса - %d\n", getpid(), getppid()); 
            sleep(1);
            printf("Завершение процесса 5\n");
            exit(0);
        }
        wait(&wstatus);
        if (WIFEXITED(wstatus) != 0) {
            printf("Завершение процесса 2\n");
        } 
        else {
            printf("Процесс 2 не завершен\n");
        }
        exit(0);
    } else {
        wait(&wstatus); 
        wait(&wstatus);
        printf("Завершение родительского процесса\n");
        printf("pid родительского процесса - %d, ppid родительского процесса - %d\n", getpid(), getppid()); 
        exit(0);
    }
}
