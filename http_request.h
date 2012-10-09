#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

#include "http_header.h"

struct http_request
{
    enum request_type request;
    enum connection_type connection_type;
    enum http_version http_version;

    char *file_name;
    char *host;
};

void process_request(int request_fd);

#endif /* _HTTP_REQUEST_H */
