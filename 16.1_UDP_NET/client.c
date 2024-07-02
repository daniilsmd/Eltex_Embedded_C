#include "includes.h"

int main() {
  
    int descr;
    char buf[15];
    struct sockaddr_in adr_server, adr_client;
    struct hostent *host;
    socklen_t size = sizeof(struct sockaddr_in);
    descr = socket(AF_INET, SOCK_DGRAM, 0);   
    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(2003); 
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = INADDR_ANY;
    adr_client.sin_port = htons(2004); 
    int tmp = bind(descr, (struct sockaddr *) &adr_client, size);

    if (tmp == -1) {
        printf("Ошибка %d", errno);
        close(descr); 
        return -1;
    }
    tmp = connect(descr, (const struct sockaddr *) &adr_server, size);
    strcat(buf, "Hi");
    tmp = send(descr, buf, 10, 0);

    if (tmp == -1) {
        printf("Ошибка отправки %d", errno); 
        close(descr); 
        return -1;
    } 
    buf[0] = '\000';
    tmp = recv(descr, buf, 10, 0);

    if (tmp == -1) {
        printf("Ошибка получения %d", errno); 
        close(descr); 
        return -1;
    } 
    printf("%s\n", buf);
    close(descr); 
    return 0;
}