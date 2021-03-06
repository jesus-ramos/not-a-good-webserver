#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "buffer.h"
#include "http_request.h"
#include "http_response.h"

#define REQ_WAIT_TIME 2

static void free_http_request(struct http_request *http_req)
{
    if (http_req->file_name)
        free(http_req->file_name);

    free(http_req);
}

static int read_request_from_socket(int request_fd, struct buffer *buf)
{
    char mini_buf[128];
    int bytes_read;
    fd_set rfds;
    struct timeval tv;
    int ret;

    FD_ZERO(&rfds);
    FD_SET(request_fd, &rfds);

    tv.tv_sec = REQ_WAIT_TIME;
    tv.tv_usec = 0;

    do
    {
        if ((ret = select(request_fd + 1, &rfds, NULL, NULL, &tv)) == -1)
            return 0;
        if (!ret)
            return 1;
        if ((bytes_read = read(request_fd, mini_buf, 128)) == -1)
            return 0;
        if (!buffer_append(buf, mini_buf, bytes_read))
            return 0;
        if (buf->len >= 4 &&
            !strncmp((const char *)&buf->data[buf->len - 4], EOR, 4))
            return 1;
    } while (bytes_read);

    return 1;
}

static void parse_request_line(char *line, struct http_request *req)
{
    char *tok;
    int len;
    char *tmp;

    tok = strtok(line, " ");
    if ((req->request = get_request_type(tok)) != GET)
        return;

    tok = strtok(NULL, " ");
    len = strlen(tok);
    if (!(tmp = malloc(len + 1)))
        return;
    req->file_name = tmp;
    strcpy(req->file_name, tok);
}

static struct http_request *parse_request(int request_fd)
{
    struct http_request *http_req;
    struct buffer buf;
    struct buffer line_buf;
    const char *current;

    if (!(http_req = calloc(sizeof(struct http_request), 1)))
        return NULL;
    if (!init_buffer(&buf))
        goto err_no_buf;
    if (!read_request_from_socket(request_fd, &buf))
        goto error;
    buffer_append(&buf, "\0", 1);
    printf("%s", buf.data);

    current = buf.data;
    if (!init_buffer(&line_buf))
        goto err_linebuf;
    if (!buffer_getline(&line_buf, current))
        goto err_linebuf;
    parse_request_line(line_buf.data, http_req);
    if (http_req->request == INVALID)
        goto out;

    /* TODO: parse remaining lines in request */

out:
    free(buf.data);
    free(line_buf.data);
    return http_req;

err_linebuf:
    free(line_buf.data);
error:
    free(buf.data);
err_no_buf:
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
    if (!(http_req = parse_request(request_fd)))
        goto out;
    send_response(request_fd, http_req);
    free_http_request(http_req);
out:
    close(request_fd);

    return NULL;
}

void process_request(int request_fd)
{
    pthread_t request_thread;

    pthread_create(&request_thread, NULL, handle_request,
                   INT_TO_PTR(request_fd));
}

#undef INT_TO_PTR
#undef PTR_TO_INT
