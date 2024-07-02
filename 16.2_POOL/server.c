#include "includes.h"

int descr_pass[4];
int descr_act[4];
char flag_ex = 0;
int arr_cl[4];
pthread_t thread[4];

void *thread_client(void *args) {

    int *tmp = args;
    int num = *tmp;
    char buf[50];
    socklen_t size = sizeof(struct sockaddr_in);

    while (flag_ex != 'q') {
        descr_act[num] = accept(descr_pass[num], NULL, &size);
        printf("Connect %d\n", num);
        arr_cl[num] = 1;
        buf[0] = '\000';
        while (buf[0] != 'q' || buf[1] != '\000') {
            buf[0] = '\000';
            strcat(buf, "TIME");
            if (send(descr_act[num], buf, sizeof(buf), 0) == -1) {
                printf("Ошибка отправки %d %d\n", num, errno);
                break;
            }
            else {
                buf[0] = '\000';
                if (recv(descr_act[num], buf, 50, 0) == -1) {
                    printf("Ошибка получения %d %d\n", num, errno);
                    break;
                }
                else {
                    printf("adr_client %d: %s\n", num, buf);
                }
            }
        }
        send(descr_act[num], "Разъединение", sizeof("Разъединение"), 0);
        printf("Разъединение %d\n", num);
        close(descr_act[num]);
        arr_cl[num] = 0;
    }
}

void *thread_connect(void *args) {

    int num;
    int buf[50];
    struct sockaddr_in adr_server;
    socklen_t size = sizeof(struct sockaddr_in);
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;

    for (int i = 0; i <= 3; i++) {
        descr_pass[i] = socket(AF_INET, SOCK_STREAM, 0);
        adr_server.sin_port = htons(7778 + i);
        if (bind(descr_pass[i], (struct sockaddr *) &adr_server, size) == -1) {
            printf("Ошибка %d %d", i, errno); 
            arr_cl[i] = -1;
        }
        else {
            listen(descr_pass[i], 1);
            num = i;
            arr_cl[i] = 0;
            if (i > 0)
                pthread_create(&thread[i], NULL, thread_client, (void *)&num);
            printf("Сервер %d запущен, порт: %d\n", i, htons(7778 + i));
        } 
    }
    arr_cl[0] = 1;

    while (flag_ex != 'q') {
        for (int i = 1; i <= 3; i++) {
            if (arr_cl[i] == 0) {
                adr_server.sin_port = htons(7778+i);
                descr_act[0] = accept(descr_pass[0], NULL, &size);
                printf("Попытка подключения к порту %d\n", adr_server.sin_port);
                arr_cl[i] = 3;
                if (send(descr_act[0], &adr_server.sin_port, sizeof(adr_server.sin_port), 0) == -1) {
                    printf("Ошибка отправки connect %d\n", errno);
                }
                close(descr_act[0]);
                break;
            }
        } 
    }
}

int main() {

    pthread_create(&thread[0], NULL, thread_connect, NULL);

    while (flag_ex != 'q') {
        scanf("%c", &flag_ex);
    }
    for (int i = 0; i <= 3; i++) { 
        if (descr_act[i]) 
            close(descr_act[i]);
        close(descr_pass[i]);
        pthread_cancel(thread[i]); 
    }
    return 0;
}