#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main(int argc, char **argv)
{
    int port;
    int queue_length;

    if (argc != 3)
    {
	printf("Usage: webserver <port #> <request queue length>\n");
	return 1;
    }

    port = atoi(argv[1]);
    queue_length = atoi(argv[2]);

    init_server(port, queue_length);
    process_requests();

    return 0;
}
