#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "socket_ops.h"

int sgetline(int fd, char **line)
{
    int buf_size;
    int bytes_read;
    int ret;
    char c;
    char *buf;
    char *newbuf;

    buf_size = 128;
    bytes_read = 0;
    if (!(buf = malloc(buf_size)))
        return -1;

    while (1)
    {
        if ((ret = read(fd, &c, 1)) == -1)
            goto error;

        if (!ret)
            break;

        buf[bytes_read++] = c;

        if (c == '\n' || !c)
            break;

        if (bytes_read >= buf_size)
        {
            buf_size += 128;
            if (!(newbuf = realloc(buf, buf_size)))
                goto error;
            buf = newbuf;
        }
    }

    if (bytes_read == buf_size)
        if (!(newbuf = realloc(buf, buf_size + 1)))
            goto error;
    buf[bytes_read] = '\0';
    *line = buf;

    return bytes_read;
    
error:
    free(buf);
    return -1;
}
