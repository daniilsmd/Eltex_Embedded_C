#include "includes.h"

int descr_tcp, descr_udp, descr_udp_act;          
int descrs_tcp[4];   
char flag_ex = 0;
pthread_t thread[4];      
socklen_t size = sizeof(struct sockaddr_in);

void *udp_thread(void *args) {

    int *tmp = args;
    int num = *tmp;
    struct sockaddr_in adr_client;
    char buf[50];
    printf("Процесс %d\n", num);
    while (buf[0] != 'q' || buf[1] != '\000') {
        if (recvfrom(descr_udp_act, buf, sizeof(buf), 0, (struct sockaddr *) &adr_client, &size) == -1) {
            printf("Ошибка получения пакета%d %d\n", num, errno);
            buf[0] = 'q';
            buf[1] = '\000';
        }
        else {
            printf("Клиент: %s\n", buf);
            if(buf[0] != 'q' || buf[1] != '\000') {
                buf[0] = '\000';
                strcat(buf, "TIME");
                if(sendto(descr_udp_act, buf, sizeof(buf), 0, (struct sockaddr *) &adr_client, size) == -1) {
                    printf("Ошибка отправки%d %d\n", num, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
            }
        }
    }
    thread[num] = 0;
}

void *thread_connect(void *args) {

    int num;
    struct sockaddr_in adr_server;
    fd_set rd;
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    descr_tcp = socket(AF_INET, SOCK_STREAM, 0);
    descr_udp = socket(AF_INET, SOCK_DGRAM, 0);
    descrs_tcp[0] = socket(AF_INET, SOCK_STREAM, 0);
    descr_udp_act = socket(AF_INET, SOCK_DGRAM, 0);
    adr_server.sin_port = htons(7777); 
    
    if (bind(descr_tcp, (struct sockaddr *) &adr_server, size)) {
        printf("Ошибка %d\n", errno);
    }
    else {
        listen(descr_tcp, 3);
    }
    adr_server.sin_port = htons(7777+1); 
    if (bind(descr_udp, (struct sockaddr *) &adr_server, size)) {
        printf("Ошибка %d\n", errno);
    }
    adr_server.sin_port = htons(7777+2); 
    if (bind(descrs_tcp[0], (struct sockaddr *) &adr_server, size)) {
        printf("Ошибка %d\n", errno);
    }
    else {
        listen(descrs_tcp[0], 3);
    }
    adr_server.sin_port = htons(7777+3); 
    if (bind(descr_udp_act, (struct sockaddr *) &adr_server, size)) {
        printf("Ошибка %d\n", errno);
    }
    int descr_tmp;
    while (flag_ex != 'q') {
        FD_ZERO(&rd);
        FD_SET(descr_tcp, &rd);
        FD_SET(descr_udp, &rd);
            for (int i = 1; i <= 3; i++) {
                if (thread[i] == 0) {
                    num = i;
                    if (FD_ISSET(descr_tcp, &rd)) {
                        descr_tmp = accept(descr_tcp, NULL, &size);
                        close(descr_tmp);
                        printf("Подключение\n");
                        pthread_create(&thread[num], NULL, tcp_thread, (void *)&num);
                    }
                    if (FD_ISSET(descr_udp, &rd)) {
                        if (recvfrom(descr_udp, (char *) &descr_tmp, 1, 0, NULL, &size) == -1) {
                            printf("Ошибка получения пакета%d %d\n", num, errno); 
                        }
                        printf("Подключение\n");
                        pthread_create(&thread[num], NULL, udp_thread, (void *)&num);
                    }
                    break;
                }
            }
    }
}

void *tcp_thread(void *args) {
    int *tmp = args;
    int num = *tmp;
    char buf[50];
    struct sockaddr_in adr_client;
    printf("Процесс: %d\n", num);
    buf[0] = '\000';
    descrs_tcp[num] = accept(descrs_tcp[0], (struct sockaddr *) &adr_client, &size);
    while(buf[0] != 'q' || buf[1] != '\000'){
        if (recv(descrs_tcp[num], buf, 50, 0) == -1) {
            printf("Ошибка получения %d %d\n", num, errno);
            buf[0] = 'q';
            buf[1] = '\000';
            break;
        }
        else {
            printf("Клиент: %s\n", buf);
            if (buf[0] != 'q' || buf[1] != '\000') {
                buf[0] = '\000';
                strcat(buf, "TIME");
                if (send(descrs_tcp[num], buf, 50, 0) == -1) {
                    printf("Ошибка отправки %d %d\n", num, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                    break;
                }
            }
        }
    }
    close(descrs_tcp[num]);
    thread[num] = 0;
}

int main() {

    pthread_create(&thread[0], NULL, thread_connect, NULL);
    while (flag_ex != 'q') {
        scanf("%c", &flag_ex); 
    }
    pthread_cancel(thread[0]);
    for (int i = 1; i <= 3; i++) {
        if (descrs_tcp[i])
            close(descrs_tcp[i]);
        if (thread[i])
            pthread_cancel(thread[i]);
    }
    close(descrs_tcp[0]);
    close(descr_udp_act);
    close(descr_tcp);
    close(descr_udp);
    return 0;
}