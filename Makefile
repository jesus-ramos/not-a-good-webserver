CC 	= gcc
LD	= gcc
CFLAGS 	= -Wall -O3 -pthread
LDFLAGS = -pthread
TARGET 	= webserver
SRCS 	= main.c server.c http_request.c http_response.c
OBJS 	= ${SRCS:.c=.o}
DEPS 	= ${SRCS:.c=.d}

.SUFFIXES :
.SUFFIXES : .o .c

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

.c.o :
	$(CC) $(CFLAGS) -c $<

%.d : %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; 	\
	rm -f $@.$$$$

-include $(DEPS)

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	-rm $(TARGET) $(OBJS) $(DEPS)

.PHONY : clean TAGS