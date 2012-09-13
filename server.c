#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

#include "http_request.h"
#include "server.h"

struct server_settings
{
    int port;
    int queue_length;
};

static struct server_settings server_settings;

void init_server(int port, int queue_length)
{
    server_settings.port = port;
    server_settings.queue_length = queue_length;
}

void process_requests()
{
    int listen_fd;
    int request_fd;
    struct sockaddr_in server_addr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_addr, 0, sizeof(struct sockaddr_in));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_settings.port);
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    listen(listen_fd, server_settings.queue_length);
    
    while (1)
    {
        request_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
        process_request(request_fd);
    }
}
