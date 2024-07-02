#include "includes.h"

int main() {

    int descr;
    struct sockaddr_in adr_server, adr_client; 
    socklen_t size = sizeof(struct sockaddr_in);
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = inet_addr("224.0.0.1");
    adr_client.sin_port = htons(7777); 

    descr = socket(AF_INET, SOCK_DGRAM, 0);
    if (sendto(descr, "Hello", 5, 0, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
    }
    close(descr);
    return 0;
}