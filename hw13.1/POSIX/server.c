#include "includes.h"

int main() {

    mq_unlink("/server_to_client");
    mq_unlink("/client_to_server");
    int prt = 0; 

    mqd_t server_client = mq_open("/server_to_client", O_WRONLY | O_CREAT, 0600, NULL);
    mqd_t client_server = mq_open("/client_to_server", O_RDONLY | O_CREAT, 0600, NULL);
    struct mq_attr *attr = (struct mq_attr *)malloc(sizeof(struct mq_attr));
    mq_getattr(server_client, attr);
    char *buf = (char *)malloc(sizeof(char) * attr->mq_msgsize);
    sprintf(buf, "Hi!");
    printf("Отправляем сообщение\n");
    mq_send(server_client, buf, strlen(buf), 0);

    memset(buf, 0, sizeof(char) * attr->mq_msgsize);
    mq_receive(client_server, buf, attr->mq_msgsize + 1, &prt);
    printf("Сообщение %s\n", buf);
    mq_close(server_client);
    mq_close(client_server);
    exit(0);
}
