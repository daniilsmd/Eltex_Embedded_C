#include "includes.h"

int main() {

    int descr;
    char buf[100]; 
    struct sockaddr_un adr_server, adr_client;
    descr = socket(AF_LOCAL, SOCK_DGRAM, 0);   
    memset(&adr_server, 0, sizeof(adr_server));
    adr_server.sun_family = AF_LOCAL; 
    strcat(adr_server.sun_path, "/tmp/stream_serv");
    adr_client.sun_family = AF_LOCAL; 
    strcat(adr_client.sun_path, "/tmp/stream_client");
    
    socklen_t size = sizeof(struct sockaddr_un);
    int tmp = bind(descr, (struct sockaddr *) &adr_client, size);
    if (tmp == -1) {
        printf("Ошибка %d", errno);
        close(descr); 
        unlink("/tmp/stream_client");
        return -1;
    } 

    tmp = connect(descr, (const struct sockaddr *) &adr_server, size);
    strcat(buf, "Hi");
    tmp = send(descr, buf, 10, 0);
    if (tmp == -1) {
        printf("Ошибка отправки %d", errno); 
        close(descr); 
        unlink("/tmp/stream_client");
        return -1;
    } 
    buf[0] = '\000';
    tmp = recv(descr, buf, 10, 0);
    if (tmp == -1) {
        printf("Ошибка получения %d", errno); 
        close(descr); 
        unlink("/tmp/stream_client");
        return -1;
    } 
    printf("%s\n", buf);
    close(descr); 
    unlink("/tmp/stream_client");
    return 0;
}