UNAME  	= $(shell uname -s)
CC 	= gcc
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS 	= -framework GLUT -framework OpenGL -lobjc
LDFLAGS = #unused
else
LDLIBS 	= -lglut -lGL -lGLU -lX11 -lXmu -lXi -lm
LDFLAGS = -I /usr/include/GL/ -L /usr/include/GL
endif
RM	= rm

TARGET 	= sierpinski
SRCS 	= main.c
OBJS	= ${SRCS:.c=.o}

.SUFFIXES: #clear them just in case
.SUFFIXES: .o .c

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.cpp.o :
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

TAGS : $(SRCS)
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean
clean :
	-$(RM) $(TARGET) $(OBJS) .depend TAGS