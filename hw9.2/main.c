#include "draw_menu.h"

int main() {

    FileEntry *prompt1, *prompt2;
    int num_prompt1, num_prompt2;
    int id_curr1 = 0, id_curr2 = 0;
    int id_select1 = -1, id_select2 = -1;
    int selected_panel = 1;
    char path1[256] = "/";
    char path2[256] = "/";
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (1) {
        files_all(path1, &prompt1, &num_prompt1);
        files_all(path2, &prompt2, &num_prompt2);
        clear();
        output_menu(0, 0, LINES, COLS / 2, prompt1, num_prompt1, id_curr1, id_select1, selected_panel == 1);
        output_menu(0, COLS / 2, LINES, COLS / 2, prompt2, num_prompt2, id_curr2, id_select2, selected_panel == 2);
        refresh();
        int ch = getch();
        printf("%i",ch);

        switch (ch) {
            case '\t':
                selected_panel = (selected_panel == 1) ? 2 : 1;
                break;
            case KEY_UP:
                if (selected_panel == 1)
                    id_curr1 = (id_curr1 > 0) ? id_curr1 - 1 : 0;
                else
                    id_curr2 = (id_curr2 > 0) ? id_curr2 - 1 : 0;
                break;
            case KEY_DOWN:
                if (selected_panel == 1)
                    id_curr1 = (id_curr1 < num_prompt1 - 1) ? id_curr1 + 1 : num_prompt1 - 1;
                else
                    id_curr2 = (id_curr2 < num_prompt2 - 1) ? id_curr2 + 1 : num_prompt2 - 1;
                break;
            case 263:  
                if (selected_panel == 1 && strcmp(path1, "/") != 0) {
                    char *last_slash = strrchr(path1, '/');
                    if (last_slash != path1)
                        *last_slash = '\0';
                    else
                        *(last_slash + 1) = '\0';
                } 
                else if (selected_panel == 2 && strcmp(path2, "/") != 0) {
                    char *last_slash = strrchr(path2, '/');
                    if (last_slash != path2)
                        *last_slash = '\0';
                    else
                        *(last_slash + 1) = '\0';
                }
                break;
            case KEY_ENTER:
            case 10: 
             if (selected_panel == 1 && prompt1[id_curr1].flag_dir) {
                  strcat(path1, prompt1[id_curr1].filename);
                  strcat(path1, "/");
                }
            else if (selected_panel == 2 && prompt2[id_curr2].flag_dir) {
                   strcat(path2, prompt2[id_curr2].filename);
                  strcat(path2, "/");
    }

    break;
            case 'z':
            case 'Z':
                clear_mem(prompt1, num_prompt1);
                clear_mem(prompt2, num_prompt2);
                endwin();
                return 0;
                
        }
    }
    return 0;
}
