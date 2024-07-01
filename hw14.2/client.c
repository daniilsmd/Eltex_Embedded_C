#include "includes.h"

WINDOW *window_send;
WINDOW *window_users;
WINDOW *window_check;

void draw_header(WINDOW *window_check, WINDOW *window_users, WINDOW *window_send) {

    box(window_send, '|', '-');
    box(window_users, '|', '-');
    box(window_check, '|', '-');
    wmove(window_check, 1, 2);
    wprintw(window_check, "Messages");
    wmove(window_check, 2, 2);
    wprintw(window_check, "--------------------------------------");
    wmove(window_users, 1, 2);
    wprintw(window_users, "Users");
    wmove(window_users, 2, 2);
    wprintw(window_users, "----------------");
}

void resize_sig(int signo) {
  
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *)&size);
    resizeterm(size.ws_row, size.ws_col);
}

int main(void) {

    int i;
    int msg_x = 0, msg_y = 0;
    char buf_msg[28];
    char buf_name[20];
    struct req_send  *point_shm_send;
    struct req_send  *point_shm_get;
    key_t key_msg_from_server, key_msg_to_server;
    int id_shm_get, id_shm_send, id_sem;
    pid_t pid;
    int stat;
    int flag;
    struct sembuf lck_1[2] = {{0, 0, 0}, {0, 1, 0}};
    struct sembuf lck_2 = {1, -1, 0};
    struct sembuf lck_3 = {2, 0, 0};
    struct sembuf lck_4 = {3, -1, 0};
    struct sembuf lck_5 = {4, 0, 0};
    key_msg_from_server = ftok("key_from_server", 6);
    key_msg_to_server = ftok("key_to_server", 6);

    id_shm_get = shmget(key_msg_from_server, sizeof(struct req_send ), IPC_EXCL | 0666);
    id_shm_send = shmget(key_msg_to_server, sizeof(struct req_send ), IPC_EXCL | 0666);
    point_shm_get = (struct req_send  *)shmat(id_shm_get, NULL, 0);
    point_shm_send = (struct req_send  *)shmat(id_shm_send, NULL, 0);
    id_sem = semget(key_msg_from_server, 10, IPC_EXCL | 0666);
    initscr();
    signal(SIGWINCH, resize_sig);
    curs_set(0);
    noecho();
    refresh();

    window_send = newwin((stdscr->_maxy / 10) - 1, (stdscr->_maxx / 4) - 3, (stdscr->_maxy / 4) + 22, 3);
    window_users = newwin((stdscr->_maxy) - 10, (stdscr->_maxx / 3.5) - 1, 3, (stdscr->_maxx / 3) - 15 + 20 + 20);
    window_check = newwin((stdscr->_maxy / 3) + 20, (stdscr->_maxx / 4) - 3 + 25, 3, 3);
    wmove(window_check, 4, 2);
    wprintw(window_check, "Input your username:");
    draw_header(window_check, window_users, window_send);
    wrefresh(window_check);
    wrefresh(window_users);
    wrefresh(window_send);
    echo();
    curs_set(1);
    wmove(window_send, 1, 1);
    wgetnstr(window_send, buf_name, 20);
    werase(window_send);
    werase(window_users);
    werase(window_check);

    draw_header(window_check, window_users, window_send);
    stat = semop(id_sem, lck_1, 2);
    point_shm_send->type_msg = 0;
    strcpy(point_shm_send->users[0], buf_name);
    stat = semop(id_sem, &lck_2, 1);
    werase(window_send);
    draw_header(window_check, window_users, window_send);
    wrefresh(window_send);

    pid = fork();
    if (0 == pid) {
        while (1) {
            wgetnstr(window_send, buf_msg, 28);
            werase(window_send);
            draw_header(window_check, window_users, window_send);
            wrefresh(window_send);
            stat = semop(id_sem, lck_1, 2);
            if (0 == strcmp(buf_msg, "EXIT")) {
                point_shm_send->type_msg = 1;
                strcpy(point_shm_send->users[0], buf_name);
                stat = semop(id_sem, &lck_2, 1);
                break;
            }
            else if (0 == strcmp(buf_msg, "END")) {
                point_shm_send->type_msg = 6;
                strcpy(point_shm_send->users[0], buf_name);
                stat = semop(id_sem, &lck_2, 1);
                break;
            }
            else {
                point_shm_send->type_msg = 3;
                strcpy(point_shm_send->users[0], buf_name);
                strcpy(point_shm_send->msg, buf_msg);
                stat = semop(id_sem, &lck_2, 1);
            }
            werase(window_send);
            draw_header(window_check, window_users, window_send);
            wrefresh(window_send);
        }
    }
    else if (0 < pid) {
        msg_x = 1;
        msg_y = 4;
        werase(window_users);
        werase(window_check);
        draw_header(window_check, window_users, window_send);
        wrefresh(window_check);

        while (1) {
            sleep(1);
            stat = semop(id_sem, &lck_3, 1);
            if (-4 == point_shm_get->type_msg) {
                for (i = 0; i < 10; i++) {
                    if (!strcmp(buf_name, point_shm_get->users[i])) {
                        flag = 1;
                    }
                }
                if (1 == flag) {
                    continue;
                }
            }
            else if (4 == point_shm_get->type_msg) {
                werase(window_users);
                draw_header(window_check, window_users, window_send);
                for (i = 0; i < point_shm_get->amount_users; i++) {
                    wmove(window_users, 4 + i, 1);
                    wprintw(window_users, "%s", point_shm_get->users[i]);
                    wrefresh(window_users);
                }
            }
            else if (5 == point_shm_get->type_msg) {
                if (40 + 4 == msg_y) {
                    werase(window_check);
                    draw_header(window_check, window_users, window_send);
                    msg_x = 1;
                    msg_y = 4;
                }
                wmove(window_check, msg_y, msg_x + 1);
                wprintw(window_check, "%s", point_shm_get->msg);
                wrefresh(window_check);
                msg_y++;
            }
            else if (-1 == point_shm_get->type_msg) {
                stat = semop(id_sem, &lck_4, 1);
                stat = semop(id_sem, &lck_5, 1);
                break;
            }
            wmove(window_send, 1, 1);
            wrefresh(window_send);
            stat = semop(id_sem, &lck_4, 1);
            stat = semop(id_sem, &lck_5, 1);
        }
        pid = wait(&stat);
        if (!WIFEXITED(stat)) {
            printf("Ошибка завершения процесса.");
        }
        delwin(window_send);
        delwin(window_users);
        delwin(window_check);
        endwin();
    }
    exit(0);
}