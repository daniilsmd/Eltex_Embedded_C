#include "includes.h"

struct message_buffer {
    long prt; 
    char text[64]; 
};

int main() {
    int server_client = 0,
        client_server = 0;

    struct message_buffer *buf = (struct message_buffer *)malloc(sizeof(struct message_buffer));
    buf->prt = 1;
    sprintf(buf->text, "Hello!"); 
    server_client = msgget(ftok("server", 1), IPC_CREAT | 0600);
    client_server = msgget(ftok("client", 2), IPC_CREAT | 0600);
    msgsnd(server_client, buf, sizeof(struct message_buffer), 0);
    
    msgrcv(client_server, buf, sizeof(struct message_buffer), 0, 0);
    printf("%ld\n%s\n", buf->prt, buf->text);
    
    msgctl(server_client, IPC_RMID, NULL);
    msgctl(client_server, IPC_RMID, NULL);
    exit(0); 
}
