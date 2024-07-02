#include "includes.h"

int main() {
  
    int descr;
    char buf[15];
    struct sockaddr_in adr_server, adr_client;
    struct hostent *host;
    socklen_t size = sizeof(struct sockaddr_in);
    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(2003); 

    descr = socket(AF_INET, SOCK_DGRAM, 0);
    int tmp = bind(descr, (struct sockaddr *) &adr_server, size);
    if (tmp == -1) {
        printf("Ошибка %d", errno);
        close(descr);
        return -1;
    } 
    size = sizeof(adr_client);
    tmp = recvfrom(descr, buf, 10, 0, (struct sockaddr *) &adr_client, &size);
    if (tmp == -1) {
        printf("Ошибка получения %d", errno);
        close(descr); 
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    tmp = sendto(descr, buf, 10, 0, (struct sockaddr *) &adr_client, size); 
    if (tmp == -1) {
        printf("Ошибка отправки %d", errno);
        close(descr); 
        return -1;
    }
    buf[0] = '\000';  
    close(descr);
    return 0;
}