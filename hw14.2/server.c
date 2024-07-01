#include "includes.h"

int main(void) {

    int stat;
    int work = 1;
    int i = 0, i2 = 0;
    int num_user_server;
    key_t key_msg_from_server, key_msg_to_server;
    int id_shm_get, id_shm_send, id_sem;
    struct req_send  *point_shm_send;
    struct req_send  *point_shm_get;
    ssize_t status_rcv;
    int last_user = 0;
    struct sembuf lck_msg = {1, 0, 0};
    struct sembuf lck_get_msg[3] = {{3, 0, 0}, {2, 1, 0}, {4, -1, 0}};
    key_msg_from_server = ftok("key_from_server", 6);
    key_msg_to_server = ftok("key_to_server", 6);

    id_sem = semget(key_msg_from_server, 10, IPC_CREAT | 0666);
    id_shm_get = shmget(key_msg_to_server, sizeof(struct req_send ), IPC_CREAT | 0666);
    id_shm_send = shmget(key_msg_from_server, sizeof(struct req_send ), IPC_CREAT | 0666);
    point_shm_send = (struct req_send  *)shmat(id_shm_send, NULL, 0);
    point_shm_get = (struct req_send  *)shmat(id_shm_get, NULL, 0);
    memset(point_shm_get, 0, sizeof(struct req_send ));
    memset(point_shm_send, 0, sizeof(struct req_send ));
    for (i = 0; i < 10; i++) {
        stat = semctl(id_sem, i, SETVAL, 15);
    }
    printf("Сервер запущен.\n");

    while (1 == work) {
        sleep(1);
        stat = semctl(id_sem, 1, SETVAL, 1);
        stat = semctl(id_sem, 0, SETVAL, 0);
        stat = semop(id_sem, &lck_msg, 1);
        switch (point_shm_get->type_msg) {

        case 0:
            printf("Пользователь %s  зашел.\n", point_shm_get->users[0]);
            if (10 >= point_shm_send->amount_users) {
                point_shm_send->amount_users++;
                strcpy(point_shm_send->users[last_user], point_shm_get->users[0]);
                last_user++;
                point_shm_send->type_msg = 4;
            }
            else {
                point_shm_send->type_msg = -4;
            }
            stat = semctl(id_sem, 3, SETVAL, last_user);
            stat = semctl(id_sem, 4, SETVAL, 1);
            stat = semctl(id_sem, 2, SETVAL, 0);
            stat = semop(id_sem, lck_get_msg, 3);
            break;

        case 1:
            printf("Пользователь %s отключился.\n", point_shm_get->users[0]);
            for (i = 0; i < 10; i++) {
                if (!strcmp(point_shm_get->users[0], point_shm_send->users[i])) {
                    i2 = i;
                }
            }
            strcpy(point_shm_send->users[i2], point_shm_send->users[last_user - 1]);
            memset(point_shm_send->users[last_user - 1], 0, sizeof(point_shm_send->users[last_user - 1]));
            point_shm_send->amount_users--;
            point_shm_send->type_msg = -4;
            stat = semctl(id_sem, 3, SETVAL, last_user);
            stat = semctl(id_sem, 4, SETVAL, 1);
            stat = semctl(id_sem, 2, SETVAL, 0);
            stat = semop(id_sem, lck_get_msg, 3);
            break;

        case 3:
            memset(point_shm_send->msg, 0, sizeof(point_shm_send->msg));
            strcat(point_shm_send->msg, point_shm_get->users[0]);
            strcat(point_shm_send->msg, ": ");
            strcat(point_shm_send->msg, point_shm_get->msg);
            point_shm_send->type_msg = 5;
            stat = semctl(id_sem, 3, SETVAL, last_user);
            stat = semctl(id_sem, 4, SETVAL, 1);
            stat = semctl(id_sem, 2, SETVAL, 0);
            stat = semop(id_sem, lck_get_msg, 3);
            break;

        case 6:
            printf("Пользователь %s выключает сервер.\n", point_shm_get->users[0]);
            point_shm_send->type_msg = -1;
            stat = semctl(id_sem, 3, SETVAL, last_user);
            stat = semctl(id_sem, 4, SETVAL, 1);
            stat = semctl(id_sem, 2, SETVAL, 0);
            stat = semop(id_sem, lck_get_msg, 3);
            work = 0;
            break;

        default:
            break;
        }
    }
    exit(0);
}
