#ifndef _HTTP_REQUEST_H
#define _HTTP_REQUEST_H

enum request_type
{
    GET,
    POST,
    HEAD,
    PUT,
    DELETE,
    TRACE,
    OPTIONS,
    CONNECT,
    PATCH,
    INVALID
};

struct request_type_entry
{
    enum request_type request_type;
    char *str;
};

extern struct request_type_entry request_types[];

struct http_request
{
    enum request_type request_type;
    char *file_name;
};

void process_request(int request_fd);

#endif /* _HTTP_REQUEST_H */
