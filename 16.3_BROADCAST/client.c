#include "includes.h"

int main() {

    int descr;
    char buf[15];
    struct sockaddr_in adr_client;
    socklen_t size = sizeof(struct sockaddr_in);
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = INADDR_BROADCAST;
    adr_client.sin_port = htons(7777); 
    descr = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (bind(descr, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка %d\n", errno);
        close(descr);
        return 1;
    }
    if (recvfrom(descr, buf, 5, 0, (struct sockaddr *) NULL, NULL) == -1) {
        printf("Ошибка получения %d\n", errno);
    }
    else {
        printf("%s\n", buf);
    }
    close(descr);
    return 0;
}