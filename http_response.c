#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "http_response.h"

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
    [OK]	      = "200 OK",
    [NOT_FOUND]       = "404 Not Found",
    [NOT_IMPLEMENTED] = "501 Not Implemented"
};

void send_response(int request_fd, struct http_request *http_req)
{
    const char status_line[] = "HTTP/1.1 501 Not Implemented\r\n";
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
