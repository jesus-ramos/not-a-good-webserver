#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http_request.h"

#define REQUEST_ENTRY(req_type) { req_type, #req_type }

struct request_type_entry request_types[] =
{
    REQUEST_ENTRY(GET),
    REQUEST_ENTRY(POST),
    REQUEST_ENTRY(HEAD),
    REQUEST_ENTRY(PUT),
    REQUEST_ENTRY(DELETE),
    REQUEST_ENTRY(TRACE),
    REQUEST_ENTRY(OPTIONS),
    REQUEST_ENTRY(CONNECT),
    REQUEST_ENTRY(PATCH),
    REQUEST_ENTRY(INVALID)
};

#define INT_TO_PTR(n)   ((void *)(unsigned long)n)
#define PTR_TO_INT(ptr) ((int)(unsigned long)ptr)

enum request_type get_request_type(char *rq)
{
    int i;

    for (i = 0; i < sizeof(request_types) / sizeof(struct request_type_entry) - 1; i++)
        if (!strcmp(rq, request_types[i].str))
            return request_types[i].request_type;
    
    return INVALID;
}

static void *handle_request(void *arg)
{
    int request_fd;

    request_fd = PTR_TO_INT(arg);

    printf("Got a request\n");

    close(request_fd);

    return NULL;
}

void process_request(int request_fd)
{
    pthread_t request_thread;

    pthread_create(&request_thread, NULL, handle_request, INT_TO_PTR(request_fd));
}

#undef INT_TO_PTR
#undef PTR_TO_INT
