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
    [NOT_FOUND]       = "404 Not Found",
    [OK]              = "200 OK",
    [NOT_IMPLEMENTED] = "501 Not Implemented"
};
