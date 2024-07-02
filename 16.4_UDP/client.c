#include "includes.h"

struct udp_header {
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[13-8];
};

int main() {

    int descr;
    char buf[33];
    struct udp_header msg1, *msg2; 
    struct sockaddr_in adr_server;
    socklen_t size = sizeof(struct sockaddr_in);
    descr = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 

    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    adr_server.sin_port = htons(7780);
    msg1.src_port = htons(7757);
    msg1.des_port = htons(7780);
    msg1.length = htons(13);
    msg1.check_sum = 0;
    strcat(msg1.payload, "Hi"); 
    
    if (sendto(descr, &msg1, 13, 0, (struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
        close(descr);
        return -1;
    }

    while(1) {
        if (recvfrom(descr, buf, 33, 0, (struct sockaddr *) &adr_server, &size) == -1) {
            printf("Получено: %s\n", buf); 
        }
        else {
            msg2 = &buf[20];
        }
        if (msg2->des_port == msg1.src_port) {
            printf(", Сервер: %s\n", msg2->payload); 
            break;
        }
    }
    close(descr);
    return 0;
}