#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

#define CRLF "\r\n"
#define EOR  CRLF CRLF

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

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
    INVALID,
    NUM_REQUEST_TYPES
};

enum connection_type
{
    KEEP_ALIVE,
    CLOSE
};

enum http_version
{
    HTTP_1_0,
    HTTP_1_1
};

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
    NOT_IMPLEMENTED,
    TEAPOT
};

struct request_type_entry
{
    enum request_type request_type;
    char *str;
};

extern struct request_type_entry request_types[];

extern const char *connection_type_text[];
extern const char *http_version_text[];
extern const char *content_type_text[];
extern const char *request_status_text[];

enum request_type get_request_type(char *rq);

#endif /* _HTTP_HEADER_H */
