CC	= gcc
LD	= gcc
CFLAGS	= -Wall -O3
LDLIBS	= -pthread
RM	= rm

BINDIR	= bin
DEPSDIR = deps
MKDIRS	= $(CURDIR)/{$(BINDIR),$(DEPSDIR)}

TARGET	= webserver
SRCS	= main.c server.c http_request.c http_response.c buffer.c http_header.c
OBJS	= $(addprefix $(BINDIR)/,${SRCS:.c=.o})
DEPS	= $(addprefix $(DEPSDIR)/,${SRCS:.c=.d})

.SUFFIXES :
.SUFFIXES : .o .c

$(shell `mkdir -p $(MKDIRS)`)

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDLIBS)

$(BINDIR)/%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEPSDIR)/%.d : %.c
	@$(CC) -M $(CFLAGS) $< > $@.$$$$;			\
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@;	\
	rm -f $@.$$$$

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

clean :
	-$(RM) -r $(TARGET) $(BINDIR) $(DEPSDIR)

-include $(DEPS)

.PHONY : clean TAGS
