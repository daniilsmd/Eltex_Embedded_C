#include "includes.h"

int main() {
  
    int descr;
    char buf[50];
    struct sockaddr_in adr_server, adr_client; 
    socklen_t size = sizeof(struct sockaddr_in);
    descr = socket(AF_INET, SOCK_DGRAM, 0);   
    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(7778);
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = INADDR_ANY;
    

    if (bind(descr, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка %d", errno);
        close(descr);  
        return -1;
    }
    buf[0] = '\000';
    strcat(buf, "Hi");
    if (sendto(descr, buf, sizeof(buf), 0, (struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка отправки : %d\n", errno);
        close(descr);  
        return -1;
    }
    buf[0] = '\000';
    if (recvfrom(descr, buf, sizeof(adr_server.sin_port), 0, (struct sockaddr *) &adr_server, &size) == -1) {
        printf("Ошибка получения :%d \n", errno);
        close(descr);  
        return -1; 
    }
    while (buf[0] != 'q' || buf[1] != '\000') {
        buf[0] = '\000';
        printf("Введите сообщение серверу: ", 50);
        fgets(buf, 50, stdin);
        for (int i = 0; i < 50; i++) {
            if (buf[i] == '\n'){
                buf[i] = '\000';
                break;
            }
        }
        if (sendto(descr, buf, sizeof(buf), 0, (struct sockaddr *) &adr_server, size) == -1) {
            printf("Ошибка отправки :%d\n", errno);
            close(descr);  
            return -1;
        }
        else {
            if (buf[0] != 'q' || buf[1] != '\000') {
                buf[0] = '\000';
                if (recvfrom(descr, buf, 50, 0, (struct sockaddr *) &adr_server, &size) == -1) {
                    printf("Ошибка получения :%d \n", errno);
                    close(descr);  
                    return -1; 
                }
                printf("Сервер: %s\n", buf);
            }
        }
    }
    close(descr);
    return 0;
}