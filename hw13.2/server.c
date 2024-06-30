#include "includes.h"

pthread_mutex_t mutex_user;

int main(void) {

    key_t key_message;
    int id_message;
    struct req_send req_send_users_data;
    struct req_send req_send;
    char *name_file = "file_key.txt";
    int status;
    ssize_t status_rcv;
    int last_user = 0;
    int mas_prio[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int free_prio = 10;
    int i = 0, i2 = 0;
    int work = 1;
    int num_user_server;
    key_message = ftok(name_file, 6);
    id_message = msgget(key_message, IPC_CREAT | 0666);

    for (i = 5; i < 20; i++) {
        while (msgrcv(id_message, &req_send, sizeof(req_send) - sizeof(req_send.mtype), i, IPC_NOWAIT) > 0)
            ;
    }
    req_send.amount_users = 0;
    req_send_users_data.amount_users = 0;
    printf("Сервер запущен.\n");

    while (1 == work) {
        sleep(1);
        status_rcv = msgrcv(id_message, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 5, 0);
        switch (req_send.type_msg) {
        case 0:
            printf("Пользователь %s  зашел.\n", req_send.users[0]);
            for (i = 0; i < 10; i++) {
                if ((0 == mas_prio[i]) && (20 > free_prio)) {
                    last_user++;
                    free_prio++;
                    i2 = i;
                    req_send_users_data.amount_users = last_user;
                    strcpy(req_send_users_data.users[i], req_send.users[0]);
                    req_send_users_data.type_msg = 4;

                    for (i = 0; i < 10; i++) {
                        if (0 != mas_prio[i]) {
                            req_send_users_data.mtype = mas_prio[i];
                            req_send_users_data.prt = mas_prio[i];
                            req_send_users_data.num_user = i;
                            status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
                        }
                    }
                    req_send_users_data.prt = free_prio;
                    mas_prio[i2] = req_send_users_data.prt;
                    req_send_users_data.num_user = i2;
                    req_send_users_data.mtype = 6;
                    status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
                    break;
                }
                else if (i == 9) {
                    req_send.prt = -1;
                    req_send.mtype = 6;
                    status = msgsnd(id_message, &req_send, sizeof(req_send) - sizeof(req_send.mtype), 0);
                    break;
                }
            }
            break;

        case 1:
            for (i = 0; i < 10; i++) {
                if (mas_prio[i] == req_send.prt)
                {
                    num_user_server = i;
                }
            }
            printf("Пользователь %s отключился.\n", req_send_users_data.users[num_user_server]);
            req_send_users_data.mtype = mas_prio[num_user_server];
            req_send_users_data.type_msg = -1;
            status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
            strcpy(req_send_users_data.users[num_user_server], req_send_users_data.users[last_user - 1]);
            memset(req_send_users_data.users[last_user - 1], 0, sizeof(req_send_users_data.users[last_user - 1]));
            mas_prio[num_user_server] = mas_prio[last_user - 1];
            mas_prio[last_user - 1] = 0;
            last_user--;
            req_send_users_data.amount_users--;
            req_send_users_data.type_msg = 4;

            for (i = 0; i < 10; i++) {
                if (0 != mas_prio[i]) {
                    req_send_users_data.mtype = mas_prio[i];
                    req_send_users_data.prt = mas_prio[i];
                    req_send_users_data.num_user = i;
                    status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
                }
            }
            break;

        case 3:
            for (i = 0; i < 10; i++) {
                if (mas_prio[i] == req_send.prt) {
                    num_user_server = i;
                }
            }
            for (i = 0; i < 10; i++) {
                if (mas_prio[i] == req_send.prt) {
                    num_user_server = i;
                }
            }
            memset(req_send_users_data.msg, 0, sizeof(req_send_users_data.msg));
            strcat(req_send_users_data.msg, req_send_users_data.users[num_user_server]);
            strcat(req_send_users_data.msg, ": ");
            strcat(req_send_users_data.msg, req_send.msg);
            printf("Пользователь %s отправил сообщение.\n", req_send_users_data.users[num_user_server]);
            req_send_users_data.type_msg = 5;
            for (i = 0; i < 10; i++) {
                if (0 != mas_prio[i]) {
                    req_send_users_data.mtype = mas_prio[i];
                    req_send_users_data.prt = mas_prio[i];
                    req_send_users_data.num_user = i;
                    status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
                }
            }
            break;

        case 6:
            printf("Пользователь %s выключает сервер.\n", req_send.users[0]);
            req_send_users_data.amount_users = -1;
            for (i = 0; i < 10; i++) {
                if (0 != mas_prio[i]) {
                    req_send_users_data.mtype = mas_prio[i];
                    req_send_users_data.prt = mas_prio[i];
                    req_send_users_data.num_user = i;
                    status = msgsnd(id_message, &req_send_users_data, sizeof(req_send_users_data) - sizeof(req_send_users_data.mtype), 0);
                }
            }
            work = 0;
            break;

        default:
            break;
        }
    }
    exit(0);
}