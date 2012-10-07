#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_request.h"
#include "server.h"

int port;
int queue_length;
int listen_fd;

void server_exit()
{
    printf("Closing server socket\n");
    close(listen_fd);
    exit(0);
}

void init_server(int p, int queue_len)
{
    port = p;
    queue_length = queue_len;
    
    signal(SIGTERM, server_exit);
    signal(SIGABRT, server_exit);
    signal(SIGINT, server_exit);
    signal(SIGQUIT, server_exit);
    signal(SIGTSTP, server_exit);
}

void process_requests()
{
    int request_fd;
    struct sockaddr_in server_addr;

    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return;
    }
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(listen_fd, (struct sockaddr *)&server_addr,
	     sizeof(struct sockaddr_in)) == -1)
    {
        perror("bind");
        return;
    }
    if (listen(listen_fd, queue_length) == -1)
    {
        perror("listen");
        return;
    }
    
    while (1)
    {
        if ((request_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL)) == -1)
        {
            perror("accept");
            continue;
        }
        process_request(request_fd);
    }
}
