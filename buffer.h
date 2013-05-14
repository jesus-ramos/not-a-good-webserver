#ifndef _BUFFER_H
#define _BUFFER_H

#define MIN_BUF_SIZE 256
#define BUF_INC_SIZE 256

struct buffer
{
    unsigned int len;
    unsigned int max;
    char *data;
};

int init_buffer(struct buffer *buf);
int reset_buffer(struct buffer *buf);
int buffer_append(struct buffer *buf, const char *data, unsigned int len);
const char *buffer_getline(struct buffer *line_buf, const char *data);

#endif /* _BUFFER_H */
