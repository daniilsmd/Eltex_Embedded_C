#include "includes.h"

int main() {

    int descr;
    struct sockaddr_in adr_client;
    struct ip_mreqn mreqn;
    char buf[15];
    socklen_t size = sizeof(struct sockaddr_in);

    mreqn.imr_ifindex = 0;
    mreqn.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mreqn.imr_address.s_addr = INADDR_ANY;
    adr_client.sin_family = AF_INET;
    adr_client.sin_addr.s_addr = INADDR_ANY;
    adr_client.sin_port = htons(7777); 
    descr = socket(AF_INET, SOCK_DGRAM, 0);
    
    if (bind(descr, (struct sockaddr *) &adr_client, size) == -1) {
        printf("Ошибка %d\n", errno);
        close(descr);
        return 1;
    }

    int tmp = setsockopt(descr, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn));
    if (recvfrom(descr, buf, 5, 0, (struct sockaddr *) NULL, NULL) == -1) {
        printf("Ошибка получения %d\n", errno);
    }
    else {
        printf("%s\n", buf);
    }
    close(descr);
    return 0;
}