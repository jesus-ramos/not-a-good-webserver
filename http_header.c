#include <string.h>

#include "http_header.h"

const char *connection_type_text[] =
{
    [KEEP_ALIVE] = "keep-alive",
    [CLOSE]      = "close"
};

const char *http_version_text[] =
{
    [HTTP_1_0] = "HTTP/1.0",
    [HTTP_1_1] = "HTTP/1.1"
};

const char *content_type_text[] =
{
    [CT_HTML]   = "text/html",
    [CT_JPEG]   = "image/jpeg",
    [CT_GIF]    = "image/gif",
    [CT_PNG]    = "image/png",
    [CT_STREAM] = "application/octet-stream"
};

const char *request_status_text[] =
{
    [OK]              = "200 OK",
    [NOT_FOUND]       = "404 Not Found",
    [TEAPOT]          = "418 I'm a teapot",
    [NOT_IMPLEMENTED] = "501 Not Implemented"
};

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
    REQUEST_ENTRY(PATCH)
};

#undef REQUEST_ENTRY

enum request_type get_request_type(char *rq)
{
    int i;

    for (i = 0; i < ARRAY_SIZE(request_types); i++)
        if (!strcmp(rq, request_types[i].str))
            return request_types[i].request_type;

    return INVALID;
}
