#include "draw_menu.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

int files_all(const char *path, FileEntry **prompts, int *num_prompts) {

    int ticker = 0;
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(path)) == NULL)
        return -1;
    *prompts = (FileEntry *)malloc(sizeof(FileEntry) * 100);
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.')
            continue;
        strcpy((*prompts)[ticker].filename, entry->d_name);
        (*prompts)[ticker].flag_dir = (entry->d_type == DT_DIR);
        ticker++;
    }
    closedir(dir);
    *num_prompts = ticker;
    return 0;
}

void clear_mem(FileEntry *prompts, int num_prompts) {

    if (prompts != NULL)
        free(prompts);
}

void output_menu(int y_1, int x_1, int height, int width, FileEntry *prompts, int num_prompts, int id_curr, int id_select, int flag_act) {
    
    int i;
    if (flag_act)
        attron(A_BOLD);
    for (i = 0; i < height; i++) {
        mvprintw(y_1 + i, x_1, "|");
        mvprintw(y_1 + i, x_1 + width, "|");
    }
    for (i = 0; i < width + 1; i++) {
        mvprintw(y_1, x_1 + i, "-");
        mvprintw(y_1 + height, x_1 + i, "-");
    }
    attroff(A_BOLD);
    attron(A_BOLD);
    mvprintw(y_1, x_1 + 2, "Filename");
    attroff(A_BOLD);
    for (i = 0; i < height - 2 && i < num_prompts; i++) {
        mvprintw(y_1 + i + 1, x_1 + 2, prompts[i].filename);
        if (prompts[i].flag_dir)
            mvprintw(y_1 + i + 1, x_1 + width - 9, "--DIR--");
        if (i == id_select && flag_act) {
            attron(A_REVERSE);
            mvprintw(y_1 + i + 1, x_1 + 2, prompts[i].filename);
            attroff(A_REVERSE);
        }
        if (i == id_curr && flag_act)
            mvprintw(y_1 + i + 1, x_1, ">");
    }
}
