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
    char payload[5];
};

#endif
