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

void free_buffer(struct buffer *buf)
{
    free(buf->data);
}

int buffer_append(struct buffer *buf, char *data, int len)
{
    char *tmp;
    int new_len;
    int new_max;

    new_len = buf->len + len;
    if (new_len > SSIZE_MAX)
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
        memcpy(buf->data + buf->len, data, len);

    return 1;
}
