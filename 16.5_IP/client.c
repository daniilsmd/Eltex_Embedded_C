#include "includes.h"

struct udp_header {
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[33-28];
};

struct ip_header {
    char Ver_IHL;     
    char DS;
    short length;
    short identification;
    short flags_offset;
    char TTL; 
    char Transport_Proto;
    short Checksum;
    int src_ip;
    int dest_ip; 
    struct udp_header payload; 
};

int main() {

    int descr;   
    char buf[33];
    int flag = 1;
    struct ip_header ip_msg_client, *ip_msg_server;
    struct sockaddr_in adr_server, adr_client;
    socklen_t size = sizeof(struct sockaddr_in);
    descr = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 
    adr_server.sin_family = AF_INET;
    adr_server.sin_addr.s_addr = inet_addr("127.0.0.1");
    adr_server.sin_port = htons(7780);
    int tmp = setsockopt(descr, IPPROTO_IP, IP_HDRINCL, (void *)&flag, (socklen_t) sizeof(flag));
    
    ip_msg_client.Ver_IHL = 69;
    ip_msg_client.DS = 0;
    ip_msg_client.length = htons(33);
    ip_msg_client.identification = 0;
    ip_msg_client.flags_offset = 0;
    ip_msg_client.TTL = 64;
    ip_msg_client.Transport_Proto = 17;
    ip_msg_client.Checksum = 0;
    ip_msg_client.src_ip = inet_addr("127.0.0.1");
    ip_msg_client.dest_ip = inet_addr("127.0.0.1"); 
    ip_msg_client.payload.src_port = htons(7757);
    ip_msg_client.payload.des_port = htons(7780);
    ip_msg_client.payload.length = htons(33-20);
    ip_msg_client.payload.check_sum = 0;
    strcat(ip_msg_client.payload.payload, "Hi"); 
 
    if (sendto(descr, &ip_msg_client, 33, 0, (struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
        close(descr);
        return -1;
    }

    while(1) {
      
        if (recvfrom(descr, buf, 33, 0, (struct sockaddr *) &adr_server, &size) == -1) {
            printf("Получено: %s\n", buf); 
        }
        else {
            ip_msg_server = buf;
        }
        if (ip_msg_server->payload.des_port == ip_msg_client.payload.src_port) {
            printf(", Сервер: %s\n", ip_msg_server->payload.payload); 
            break;
        }
    }
    close(descr);
    return 0;
}