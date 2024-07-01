#include "includes.h"

int main() {

    int shmid = shmget(1111, 256, 0666);
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    printf("Получено сообщение от сервера: %s\n", shmaddr);
    strcpy(shmaddr, "Hello!");
    shmdt(shmaddr);
    return 0;
}