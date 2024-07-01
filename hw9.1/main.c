#include <stdio.h>
#include <string.h>

int main() {

    FILE *file;
    int len, i;
    char text[] = "String from file";
    char input[128];

    file = fopen("output.txt", "w");
    fprintf(file, "%s", text);
    fclose(file);
    file = fopen("output.txt", "r");
    fseek(file, 0, SEEK_END);
    len = ftell(file);

    for (i = 1; i <= len; i++) {
        fseek(file, -i, SEEK_END);
        printf("%c", fgetc(file));
    }
    printf("\n");
    fclose(file);
    return 0;
}
