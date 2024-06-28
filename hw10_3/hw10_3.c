#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char prompt[20];
    char *args[10];
    pid_t pid;

    while(1) {
        printf("Введите команду:\n");
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = 0;
        if (strcmp(prompt, "exit") == 0) {
            exit(0);
        }

        int i = 0;
        args[i] = strtok(prompt, " ");
        while(args[i] != NULL) {
            args[++i] = strtok(NULL, " ");
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
        } 
        else {
            wait(NULL);
        }
    }
    return 0;
}
