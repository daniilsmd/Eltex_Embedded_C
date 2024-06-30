#include "parser.h"

void parse_command(char *prompt, char **args) {
    int i = 0;
    args[i] = strtok(prompt, " ");
    while (args[i] != NULL && i < 9) {
        args[++i] = strtok(NULL, " ");
    }
    args[i] = NULL;
}