#include "includes.h"

int main() {

    int descr;
    char buf[13];
    struct sockaddr_in adr_server, adr_client; 
    socklen_t size = sizeof(struct sockaddr_in);
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = INADDR_ANY;
    adr_server.sin_port = htons(7780); 

    descr = socket(AF_INET, SOCK_DGRAM, 0);
    if (bind(descr, (struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка %d\n", errno);
        close(descr);
        return -1;
    }

    if (recvfrom(descr, buf, 13, 0, (struct sockaddr *) &adr_client, &size) == -1) {
        printf("Ошибка получения %d\n", errno);
        close(descr);
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    if (sendto(descr, buf, sizeof(buf), 0, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
        close(descr);
        return -1;
    }
    close(descr);
    return 0;
}