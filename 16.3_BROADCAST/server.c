#include "includes.h"

int main() {

    int descr;
    int flag = 1;
    struct sockaddr_in adr_server, adr_client; 
    socklen_t size = sizeof(struct sockaddr_in);
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = INADDR_BROADCAST;
    adr_client.sin_port = htons(7777); 

    descr = socket(AF_INET, SOCK_DGRAM, 0);
    int tmp = setsockopt(descr, SOL_SOCKET, SO_BROADCAST, (void *)&flag, (socklen_t) sizeof(flag));
    if (sendto(descr, "Hello", 5, 0, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
    }
    close(descr);
    return 0;
}