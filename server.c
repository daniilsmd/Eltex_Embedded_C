#include "includes.h"

int main() {

    int shmid = shmget(1111, 256, IPC_CREAT | 0666);
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    strcpy(shmaddr, "Hi!");
    printf("Ожидание сообщения от клиента.\n");
    while (strcmp(shmaddr, "Hello!") != 0) {
        sleep(1);
    }
    printf("Получено сообщение от клиента: %s\n", shmaddr);
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}