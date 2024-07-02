#include "includes.h"

int main() {
  
    int descr;
    char buf[50];  
    struct sockaddr_in adr_server;
    socklen_t size = sizeof(struct sockaddr_in);
    descr = socket(AF_INET, SOCK_STREAM, 0); 
    memset(&adr_server, 0, sizeof(adr_server));
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(7777);
    
    if (connect(descr, (const struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка подключения %d", errno);
        close(descr); 
        return -1;
    }
    else {
        close(descr);
    }

    descr = socket(AF_INET, SOCK_STREAM, 0); 
    adr_server.sin_port = htons(7777+2);
    if (connect(descr, (const struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка подключения %d", errno);
        close(descr); 
        return -1;
    }

    if (send(descr, "Подключение", 50, 0) == -1) {
        printf("Ошибка отправки %d", errno); 
        close(descr); 
        return -1;
    }

    while (buf[0] != 'q' || buf[1] != '\000') {
        buf[0] = '\000'; 
        if (recv(descr, buf, 50, 0) == -1) {
            printf("Ошибка получения %d", errno); 
            close(descr); 
            return -1;
        } 
        printf("%s\n", buf);
        printf("Введите сообщение: ", 50);
        buf[0] = '\000';
        fgets(buf, 50, stdin);
        for(int i = 0; i < 50; i++){
            if(buf[i] == '\n'){
                buf[i] = '\000';
                break;
            } 
        }
        if (send(descr, buf, 50, 0) == -1) {
            printf("Ошибка отправки %d", errno); 
            close(descr); 
            return -1;
        }
    } 
    close(descr); 
    return 0;
}