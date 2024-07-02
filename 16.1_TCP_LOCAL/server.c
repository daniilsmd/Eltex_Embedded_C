#include "includes.h"

int main() {
    
    int descr_pass, descr_act;
    char buf[15];
    struct sockaddr_un adr_server, adr_client;
    socklen_t size = sizeof(struct sockaddr_un);

    memset(&adr_server, 0, sizeof(adr_server));
    memset(&adr_client, 0, sizeof(adr_client));
    strcat(adr_server.sun_path, "/tmp/stream_serv");
    adr_server.sun_family = AF_LOCAL;  
    descr_pass = socket(AF_LOCAL, SOCK_STREAM, 0);
    int tmp = bind(descr_pass, (struct sockaddr *) &adr_server, size);
    
    if (tmp == -1) {
        printf("Ошибка %d", errno);
        close(descr_pass);
        unlink("/tmp/stream_serv");
        return -1;
    }
    listen(descr_pass, 2);
    descr_act = accept(descr_pass, (struct sockaddr *) &adr_client, &size);
    tmp = recv(descr_act, buf, 10, MSG_WAITALL);

    if (tmp == -1) {
        printf("Ошибка получения %d", errno);
        close(descr_pass);
        close(descr_act);
        unlink("/tmp/stream_serv");
        return -1;
    }
    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    tmp = send(descr_act, buf, 10, 0); 

    if (tmp == -1) {
        printf("Ошибка отправки %d", errno);
        close(descr_pass);
        close(descr_act);
        unlink("/tmp/stream_serv");
        return -1;
    }
    buf[0] = '\000'; 
    close(descr_act);
    close(descr_pass);
    unlink("/tmp/stream_serv");
    return 0;
}