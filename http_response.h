#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include <stdint.h>

#include "http_request.h"

#define CRLF "\r\n"
#define EOR  CRLF CRLF

enum content_type
{
    CT_HTML,
    CT_JPEG,
    CT_GIF,
    CT_PNG,
    CT_STREAM
};

enum request_status
{
    OK,
    NOT_FOUND,
    NOT_IMPLEMENTED
};

extern const char *content_type_text[];
extern const char *request_status_text[];

#define CT_TEXT(content_type)   content_type_text[content_type]
#define RS_TEXT(request_status) request_status_text[request_status]

struct http_response
{
    enum content_type content_type;
    enum request_status request_status;
    uint8_t *body;
};

void send_response(int request_fd, struct http_request *http_req);

#endif /* _HTTP_RESPONSE_H */
