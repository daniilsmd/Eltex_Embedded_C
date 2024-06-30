#include "includes.h"

struct message_buffer {
    long prt; 
    char text[64];
};

int main() {

    int server_client = 0, 
        client_server = 0; 
        
    struct message_buffer *buf = (struct message_buffer *)malloc(sizeof(struct message_buffer)); 
    server_client = msgget(ftok("server", 1), 0);
    client_server = msgget(ftok("client", 2), 0);

    msgrcv(server_client, buf, sizeof(struct message_buffer), 0, 0);
    printf("%ld\n%s\n", buf->prt, buf->text); 
    sprintf(buf->text, "Hello!");
    msgsnd(client_server, buf, sizeof(struct message_buffer), 0);
    msgctl(server_client, IPC_RMID, NULL);
    msgctl(client_server, IPC_RMID, NULL);
    exit(0); 
}