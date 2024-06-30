#include "includes.h"

int main() {

    mqd_t server_client = mq_open("/server_to_client", O_RDONLY);
    mqd_t client_server = mq_open("/client_to_server", O_WRONLY);
    int prt = 0; 

    struct mq_attr *attr = (struct mq_attr *)malloc(sizeof(struct mq_attr));
    mq_getattr(server_client, attr); 
    char *buf = (char *)malloc(sizeof(char) * attr->mq_msgsize); 
    mq_receive(server_client, buf, attr->mq_msgsize + 1, &prt);
    printf("Сообщение: %s\n", buf);

    printf("Отправляем сообщение\n");
    sprintf(buf, "Hello!");
    mq_send(client_server, buf, strlen(buf), 0);
    mq_close(server_client);
    mq_close(client_server);
    exit(0);
}