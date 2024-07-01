#include "includes.h"

int main() {

    int file_shm;
    char *pointer_shm;
    sem_t *semaphore;

    file_shm = shm_open("/my_shared_memory", O_RDWR, 0666);
    pointer_shm = mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, file_shm, 0);
    semaphore = sem_open("/my_semaphore", 0);
    if (semaphore == SEM_FAILED) {
        perror("SEM_OPEN");
        exit(0);
    }
    printf("Получено сообщение от сервера: %s\n", pointer_shm);
    strcpy(pointer_shm, "Hello!");
    sem_post(semaphore);
    munmap(pointer_shm, 1024);
    sem_close(semaphore);
    return 0;
}