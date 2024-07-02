#include "includes.h"

char flag_ex = 0;
int desrs[4];
struct sockaddr_in adr_server[4], adr_client[4];
pthread_t thread[4]; 
socklen_t size = sizeof(struct sockaddr_in);
mqd_t mqdes;
sem_t *semid, *semid1;
struct mq_attr attr;

void *thread_client(void *args) {

    char buf[50];
    int *tmp = (void *) args;
    int num = *tmp;
    unsigned int prio;
    sem_post(semid1);
    printf("Запуск сервера %d\n", num);
    while (flag_ex != 'q') {
        sem_wait(semid);
        buf[0] = '\000';
        while (buf[0] != 'q' || buf[1] != '\000') {
            buf[0] = '\000';
            strcat(buf, "TIME");
            if (sendto(desrs[num], buf, sizeof(buf), 0, (struct sockaddr *) &adr_client[num], size) == -1) {
                printf("Ошибка отправки :%d %d\n", num, errno);
                buf[0] = 'q';
                buf[1] = '\000';
            }
            else {
                if (buf[0] != 'q' && buf[1] != '\000') {
                    buf[0] = '\000'; 
                    if (recvfrom(desrs[num], buf, sizeof(buf), 0, (struct sockaddr *) &adr_client[num], &size) == -1) {
                        printf("Ошибка получения :%d %d\n", num, errno);
                        buf[0] = 'q';
                        buf[1] = '\000';
                    }
                    printf("Клиент: %d %d: %s\n", num, adr_client[num].sin_port, buf);
                }
            }
        }
    }
}

void *thread_connect(void *args) { 

    int num;
    char buf[50];
    attr.mq_maxmsg = 3;
    attr.mq_msgsize = sizeof(adr_client[0].sin_port);
    mqdes = mq_open("/queue10", O_RDWR | O_CREAT, 0666, &attr);
    for (int i = 1; i <= 3; i++) {
        num = i;
        pthread_create(&thread[i], NULL, thread_client, (void *)&num);
        sem_wait(semid1);
    }
    while (flag_ex != 'q') {
        if (recvfrom(desrs[0], buf, 50, 0, (struct sockaddr *) &adr_client[0], &size) == -1) {
            printf("Ошибка получения %d", errno);
        }
        else {
            printf("Подключение %d\n", adr_client[0].sin_port);
            sem_post(semid);
            if (mq_send(mqdes, (char *) &adr_client[0].sin_port, sizeof(adr_client[0].sin_port), 1) == -1) {
                printf("Ошибка отправки\n"); 
            } 
        }
    }
}

int main() {

    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    semid = sem_open("/semid", O_CREAT, 0666, 0); 
    semid1 = sem_open("/semid1", O_CREAT, 0666, 0); 

    for (int i = 0; i <= 3; i++) {    

        adr_server[i].sin_family = AF_INET;                 
        adr_server[i].sin_addr.s_addr = INADDR_ANY;        
        adr_server[i].sin_port = htons(7778 + i);
        adr_client[i].sin_family = AF_INET;                 
        adr_client[i].sin_addr.s_addr = INADDR_ANY;
        desrs[i] = socket(AF_INET, SOCK_DGRAM, 0);

        if (bind(desrs[i], (struct sockaddr *) &adr_server[i], size) == -1) {
            printf("Ошибка %d %d", errno, i);
            close(desrs[i]); 
            flag_ex = 'q';
        }
    }

    pthread_create(&thread[0], NULL, thread_connect, NULL);
    while (flag_ex != 'q') {
        scanf("%c", &flag_ex); 
    }
    for (int i = 0; i <= 3; i++) {
        if (thread[i] != 0)
            pthread_cancel(thread[i]);
        close(desrs[i]);
    }
    return 0;
}