
#include <dirent.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#ifndef DRAW_MENU_H
#define DRAW_MENU_H

typedef struct {
    char filename[256];
    int flag_dir;
} FileEntry;

int files_all(const char *path, FileEntry **prompts, int *num_prompt);
void clear_mem(FileEntry *prompts, int num_prompt);
void output_menu(int y_1, int x_1, int height, int width, FileEntry *prompts, int num_prompt, int id_curr, int id_select, int flag_act);

#endif