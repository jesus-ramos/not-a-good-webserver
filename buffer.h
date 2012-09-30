#ifndef _BUFFER_H
#define _BUFFER_H

#define MIN_BUF_SIZE 256
#define BUF_INC_SIZE 256

struct buffer
{
    int len;
    int max;
    char *data;
};

int init_buffer(struct buffer *buf);
void free_buffer(struct buffer *buf);
int buffer_append(struct buffer *buf, char *data, int len);

#endif /* _BUFFER_H */
