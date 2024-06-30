#include "parser.h"

int main() {

    pid_t pid;
    char prompt[100];
    char *args[10];
    char *args_pipe[10];
    int fd[2];

    while (1) {
        printf("Введите команду:\n");
        fgets(prompt, sizeof(prompt), stdin);
        prompt[strcspn(prompt, "\n")] = 0;
        if (strcmp(prompt, "exit") == 0) {
            exit(0);
        }

        char *pipe_pos = strchr(prompt, '|');
        if (pipe_pos != NULL) {
            *pipe_pos = 0;
            pipe_pos++;
            while (*pipe_pos == ' ') pipe_pos++;
            parse_command(prompt, args);
            parse_command(pipe_pos, args_pipe);
            if (pipe(fd) == -1) {
                perror("Канал не был создан");
                continue;
            }

            if ((pid = fork()) == 0) {
                close(fd[0]); 
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                execvp(args[0], args);
                perror("Команда не была выполнена");
                exit(0);
            } 
            else if (pid < 0) {
                perror("Процесс не был создан");
                continue;
            }

            if ((pid = fork()) == 0) {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                execvp(args_pipe[0], args_pipe);
                perror("Команда не была выполнена");
                exit(0);
            } 
            else if (pid < 0) {
                perror("Процесс не был создан");
                continue;
            }
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);

        } 
        else {
            parse_command(prompt, args);
            pid = fork();
            if (pid == 0) {
                execvp(args[0], args);
                perror("Команда не была выполнена");
                exit(0);
            } 
            else if (pid > 0) {
                wait(NULL);
            } 
            else {
                perror("Процесс не был создан");
            }
        }
    }

    return 0;
}