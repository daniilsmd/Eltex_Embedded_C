#include "includes.h"

char flag_ex = 0;
int desrs[16];  
int amount_clients = 0;
pthread_t thread[16];

void *thread_client (void *args) {

    int *num = (int *) args;
    char buf[50];
    buf[0] = '\000';
    while (buf[0] != 'q' || buf[1] != '\000') {
        buf[0] = '\000';
        strcat(buf, "TIME");
        if (send(desrs[*num], buf, sizeof(buf), 0) == -1) {
            printf("Ошибка отправки%d %d\n", *num, errno);
            buf[0] = 'q';
            buf[1] = '\000';
        }
        else {
            if (buf[0] != 'q' && buf[1] != '\000') {
                buf[0] = '\000'; 
                if (recv(desrs[*num], buf, 50, 0) == -1) {
                    printf("Ошибка получения :%d %d\n", *num, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
                printf("adr_client %d: %s\n", *num, buf);
            }
        }
    }
    send(desrs[*num], buf, sizeof(buf), 0);
    close(desrs[*num]);
    amount_clients--;
    desrs[*num] = -1;
}

void *thread_disconnect(void *args) {

    int stat;
    for (int i = 1; i <= 15; i++) {
        if (desrs[i] != -1) {
            pthread_join(thread[i], (void **)&stat);
            close(desrs[i]);
        }
    }
}

void *thread_connect(void *args) {

    struct sockaddr_in adr_server, adr_client[15]; 
    int num, tmp;
    socklen_t size = sizeof(struct sockaddr_in);
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(7777); 

    desrs[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(desrs[0], (struct sockaddr *) &adr_server, size)) {
        printf("Ошибка %d\n", errno);
        close(desrs[0]);
    }
    else {
        listen(desrs[0], 15);
        while(1) {
            num = -1;
            for (int i = 1; i <= 15; i++) {
                if (desrs[i] == -1) {
                    num = i;
                    break;
                }
            }
            if (num > 0) {
                desrs[num] = accept(desrs[0], (struct sockaddr *) &adr_client[num], &size);
                tmp = num;
                pthread_create(&thread[num + 1], NULL, thread_client, (void *)&tmp);
                amount_clients++;
            }
            else {
                sleep(1);
            }
        }
    }
}

int main() {
  
    int stat;
    for (int i = 0; i < 15; i++)
        desrs[i] = -1;
    pthread_create(&thread[0], NULL, thread_connect, NULL);
    while (flag_ex != 'q') {
        scanf("%c", &flag_ex);
        if (flag_ex == 'b') {
            pthread_cancel(thread[0]);
            pthread_create(&thread[0], NULL, thread_disconnect, NULL); 
            pthread_join(thread[0], (void **)&stat);
            flag_ex = 'q';
        }
    }
    close(desrs[0]);
    return 0;
}