#include "includes.h"

int main() {

    int file_shm;
    char *pointer_shm;
    sem_t *semaphore;

    file_shm = shm_open("/my_shared_memory", O_CREAT | O_RDWR, 0666);
    if (ftruncate(file_shm, 1024) == -1) {
        perror("FTRUNCATE");
        exit(0);
    }
    pointer_shm = mmap(0, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, file_shm, 0);
    semaphore = sem_open("/my_semaphore", O_CREAT, 0666, 0);
    strcpy(pointer_shm, "Hi!");

    printf("Ожидание сообщения от клиента.\n");
    sem_wait(semaphore);
    printf("Получено сообщение от клиента: %s\n", pointer_shm);
    munmap(pointer_shm, 1024);
    shm_unlink("/my_shared_memory");
    sem_close(semaphore);
    sem_unlink("/my_semaphore");
    return 0;
}
