#include "http_response.h"

char *content_type_text[] =
{
    [CT_HTML]   = "text/html",
    [CT_JPEG]   = "image/jpeg",
    [CT_GIF]    = "image/gif",
    [CT_PNG]    = "image/png",
    [CT_STREAM] = "application/octet-stream"
};

char *request_status_text[] =
{
    [OK]              = "200 OK",
    [NOT_FOUND]       = "404 Not Found",
    [NOT_IMPLEMENTED] = "501 Not Implemented"
};

void send_response(int request_fd, struct http_request *http_req)
{
    if (!http_req)
        return;
}
