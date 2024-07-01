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
    key_t msg_key;
    int msg_id;
    struct req_send req_send;
    char *name_file = "file_key.txt";
    pid_t pid;
    int status;
    ssize_t status_rcv;
    msg_key = ftok(name_file, 6);
    msg_id = msgget(msg_key, IPC_CREAT | 0666);

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
    wgetnstr(window_send, req_send.users[0], sizeof(req_send.users[0]));
    werase(window_send);
    werase(window_users);
    werase(window_check);
    draw_header(window_check, window_users, window_send);
    msg_id = msgget(msg_key, IPC_EXCL | 0666);
    req_send.mtype = 5;
    req_send.type_msg = 0;
    status = msgsnd(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 0);

    werase(window_send);
    draw_header(window_check, window_users, window_send);
    status_rcv = msgrcv(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 6, 0);

    for (i = 0; i < req_send.amount_users; i++) {
        wmove(window_users, 4 + i, 1);
        wprintw(window_users, "%s", req_send.users[i]);
        wrefresh(window_users);
    }
    pid = fork();
    if (0 == pid) {
      
        msg_x = 1;
        msg_y = 5;
        werase(window_users);
        werase(window_check);
        draw_header(window_check, window_users, window_send);
        wrefresh(window_check);
        while (1) {
            status_rcv = msgrcv(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), req_send.prt, 0);

            if (-1 == req_send.amount_users) {
                break;
            }
            else if (4 == req_send.type_msg) {
                werase(window_users);
                draw_header(window_check, window_users, window_send);
                for (i = 0; i < req_send.amount_users; i++) {
                    wmove(window_users, 4 + i, 1);
                    wprintw(window_users, "%s", req_send.users[i]);
                    wrefresh(window_users);
                }
            }
            else if (5 == req_send.type_msg) {
                if (40 + 4 == msg_y) {
                    werase(window_check);
                    draw_header(window_check, window_users, window_send);
                    msg_x = 1;
                    msg_y = 4;
                }
                wmove(window_check, msg_y, msg_x + 1);
                wprintw(window_check, "%s", req_send.msg);
                wrefresh(window_check);
                msg_y++;
            }
            wmove(window_send, 1, 1);
            wrefresh(window_send);
        }
    }
    else if (0 < pid) {
        req_send.mtype = 5;
        while (1) {
            wmove(window_send, 1, 1);
            wgetnstr(window_send, req_send.msg, 28);
            werase(window_send);
            draw_header(window_check, window_users, window_send);
            wrefresh(window_send);
            if (0 == strcmp(req_send.msg, "exit")) {
                req_send.type_msg = 1;
                status = msgsnd(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 0);
                break;
            }
            else if (0 == strcmp(req_send.msg, "fin")) {
                req_send.type_msg = 6;
                status = msgsnd(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 0);
                break;
            }
            else {
                req_send.type_msg = 3;
                status = msgsnd(msg_id, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 0);
            }
        }
        delwin(window_send);
        delwin(window_users);
        delwin(window_check);
        endwin();
    }
    exit(0);
}



