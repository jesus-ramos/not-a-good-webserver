#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "buffer.h"
#include "http_response.h"

typedef void (*handle_request_fn)(int request_fd, struct http_request *req);

void handle_get_request(int request_fd, struct http_request *req)
{
    struct stat stat_buf;
    struct buffer header_buf;

    if (stat(req->file_name, &stat_buf) == -1)
    {
        perror("stat");
        /* NOT FOUND */
        return;
    }
    if (!init_buffer(&header_buf))
        return;
}

static handle_request_fn request_fns[NUM_REQUEST_TYPES] =
{
    [GET] = handle_get_request
};

void send_response(int request_fd, struct http_request *http_req)
{
    const char status_line[] = "HTTP/1.0 418 I'm a teapot\r\n";
    const char content_type_line[] = "Content-type: text/html\r\n";
    const char entity_body[] = "<html>"
        "<head><title>WebServer Feature Not Implemented</title></head>"
        "<body>This web server does not support the requested feature</body>"
        "</html>";

    if (!http_req)
        return;

    write(request_fd, status_line, sizeof(status_line) - 1);
    write(request_fd, content_type_line, sizeof(content_type_line) - 1);
    write(request_fd, CRLF, sizeof(CRLF) - 1);
    write(request_fd, entity_body, sizeof(entity_body) - 1);
}
