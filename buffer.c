#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "buffer.h"

int init_buffer(struct buffer *buf)
{
    if (!(buf->data = malloc(MIN_BUF_SIZE)))
        return 0;
    buf->len = 0;
    buf->max = MIN_BUF_SIZE;
    return 1;
}

int reset_buffer(struct buffer *buf)
{
    free(buf->data);
    return init_buffer(buf);
}

int buffer_append(struct buffer *buf, const char *data, unsigned int len)
{
    char *tmp;
    unsigned int new_len;
    unsigned int new_max;

    new_len = buf->len + len;
    if (new_len > buf->len)
    {
        fprintf(stderr, "Maxmimum buffer size exceeded\n");
        return 0;
    }
    else if (new_len > buf->max)
    {
        new_max = buf->max + BUF_INC_SIZE *
            ((new_len - buf->len) / BUF_INC_SIZE + 1);
        if (!(tmp = realloc(buf->data, new_max)))
            return 0;
        buf->data = tmp;
        memcpy(buf->data + buf->len, data, len);
        buf->len = new_len;
        buf->max = new_max;
    }
    else
    {
        memcpy(buf->data + buf->len, data, len);
        buf->len = new_len;
    }

    return 1;
}

const char *buffer_getline(struct buffer *line_buf, const char *data)
{
    do
    {
        if (!buffer_append(line_buf, data, 1))
            return 0;
    } while (*data++ != '\n');

    if (!buffer_append(line_buf, "\0", 1))
        return 0;

    return data;
}
