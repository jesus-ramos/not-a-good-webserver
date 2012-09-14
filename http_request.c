#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "http_request.h"
#include "http_response.h"
#include "socket_ops.h"

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
};

static enum request_type get_request_type(char *rq)
{
    int i;

    for (i = 0; i < sizeof(request_types) / sizeof(struct request_type_entry); i++)
        if (!strcmp(rq, request_types[i].str))
            return request_types[i].request_type;

    return INVALID;
}

static void free_http_request(struct http_request *http_req)
{
    if (http_req->file_name)
        free(http_req->file_name);

    free(http_req);
}

static int parse_header(struct http_request *http_req, char *line)
{
    char *tok;
    int len;

    if (!(tok = strtok(line, " ")))
        return 0;
    http_req->request_type = get_request_type(tok);
    if (!(tok = strtok(NULL, " ")))
        return 0;
    len = strlen(tok);
    http_req->file_name = malloc(len + 1);
    strcpy(http_req->file_name, tok);

    return 1;
}

static struct http_request *parse_request(int request_fd)
{
    struct http_request *http_req;
    char *line;

    if (!(http_req = calloc(sizeof(struct http_request), 1)))
        return NULL;

    if (sgetline(request_fd, &line) < 1)
        return NULL;
    if (!parse_header(http_req, line))
        goto parse_error;
    free(line);

    return http_req;

parse_error:
    free(line);
    free_http_request(http_req);
    return NULL;
}

#define INT_TO_PTR(n)   ((void *)(unsigned long)n)
#define PTR_TO_INT(ptr) ((int)(unsigned long)ptr)

static void *handle_request(void *arg)
{
    int request_fd;
    struct http_request *http_req;

    request_fd = PTR_TO_INT(arg);
    http_req = parse_request(request_fd);
    send_response(http_req);

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
