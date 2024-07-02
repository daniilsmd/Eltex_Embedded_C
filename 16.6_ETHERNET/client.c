#include "includes.h"

struct udp_header {
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[47-42];
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

struct ethernet_header {
    char des_mac[6];
    char src_mac[6];
    short type;
    struct ip_header payload;
};

int main() {

    int descr;   
    char buf[47]; 
    struct ethernet_header msg_client, *msg_server;
    struct sockaddr_ll adr_server;
    socklen_t size = sizeof(struct sockaddr_in); 
    
    descr = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));  
    adr_server.sll_family = AF_PACKET;
    adr_server.sll_protocol = 0;
    adr_server.sll_ifindex = if_nametoindex("enp2s0");
    adr_server.sll_hatype = 0;
    adr_server.sll_pkttype = 0;
    adr_server.sll_halen = 6;
    adr_server.sll_addr[0] = 0x08;
    adr_server.sll_addr[1] = 0x8f;
    adr_server.sll_addr[2] = 0xc3;
    adr_server.sll_addr[3] = 0x37;
    adr_server.sll_addr[4] = 0xf7;
    adr_server.sll_addr[5] = 0x77;
  
    msg_client.des_mac[0] = 0x08;
    msg_client.des_mac[1] = 0x8f;
    msg_client.des_mac[2] = 0xc3;
    msg_client.des_mac[3] = 0x37;
    msg_client.des_mac[4] = 0xf7;
    msg_client.des_mac[5] = 0x77;
    msg_client.src_mac[0] = 0x08;
    msg_client.src_mac[1] = 0x8f;
    msg_client.src_mac[2] = 0xc3;
    msg_client.src_mac[3] = 0x37;
    msg_client.src_mac[4] = 0xf7;
    msg_client.src_mac[5] = 0x77;
    msg_client.type = 0x0800;

    msg_client.payload.Ver_IHL = 69;
    msg_client.payload.DS = 0;
    msg_client.payload.length = htons(47-14);
    msg_client.payload.identification = 0;
    msg_client.payload.flags_offset = 0;
    msg_client.payload.TTL = 64;
    msg_client.payload.Transport_Proto = 17;
    msg_client.payload.Checksum = 0;
    msg_client.payload.src_ip = inet_addr("127.0.0.1");
    msg_client.payload.dest_ip = inet_addr("127.0.0.1"); 
    msg_client.payload.payload.src_port = htons(7757);
    msg_client.payload.payload.des_port = htons(7780);
    msg_client.payload.payload.length = htons(47-34);
    msg_client.payload.payload.check_sum = 0;
    strcat(msg_client.payload.payload.payload, "Hi"); 
 
    if (sendto(descr, &msg_client, 47, 0, (struct sockaddr *) &adr_server, size) == -1) {
        printf("Ошибка отправки %d\n", errno);
        close(descr);
        return -1;
    }

    while(1) {
        if(recvfrom(descr, buf, 47, 0, (struct sockaddr *) &adr_server, &size) == -1) {
            printf("Получено: %s\n", buf); 
        }
        else {
            msg_server = buf;
        }
        if (msg_server->payload.payload.des_port == msg_client.payload.payload.src_port) {
            printf(", Сервер: %s\n", ip_msg_server->payload.payload.payload); 
            break;
        }
    }
    close(descr);
    return 0;
}