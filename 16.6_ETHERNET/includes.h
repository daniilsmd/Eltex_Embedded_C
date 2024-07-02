#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h> 

#ifndef __INCLUDES_H__
#define __INCLUDES_H__

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

#endif
