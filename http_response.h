#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "http_header.h"
#include "http_request.h"

struct http_response
{
    enum http_version http_version;
    enum content_type content_type;
    enum request_status request_status;
    enum connection_type connection_type;

    char *body;
    char *server;
    char *date;
};

void send_response(int request_fd, struct http_request *http_req);

#endif /* _HTTP_RESPONSE_H */
