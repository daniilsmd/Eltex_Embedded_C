#include "includes.h"

int main() {
  
    int descr;
    char buf[15];
    struct sockaddr_un adr_server, adr_client;
    socklen_t size = sizeof(struct sockaddr_un);
    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    strcat(adr_server.sun_path, "/tmp/stream_serv");
    adr_server.sun_family = AF_LOCAL;  

    descr = socket(AF_LOCAL, SOCK_DGRAM, 0);
    int tmp = bind(descr, (struct sockaddr *) &adr_server, size);
    if (tmp == -1) {
        printf("Ошибка %d", errno);
        close(descr);
        unlink("/tmp/stream_serv");
        return -1;
    } 
    
    size = sizeof(adr_client);
    tmp = recvfrom(descr, buf, 10, 0, (struct sockaddr *) &adr_client, &size);

    if (tmp == -1) {
        printf("Ошибка получения %d", errno);
        close(descr); 
        unlink("/tmp/stream_serv");
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    tmp = sendto(descr, buf, 10, 0, (struct sockaddr *) &adr_client, size); 

    if (tmp == -1) {
        printf("Ошибка отправки %d", errno);
        close(descr); 
        unlink("/tmp/stream_serv");
        return -1;
    }
    buf[0] = '\000';  
    close(descr);
    unlink("/tmp/stream_serv");
    return 0;
}