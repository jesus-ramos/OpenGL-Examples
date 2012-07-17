UNAME  	= $(shell uname -s)
CC 	= g++
CFLAGS	= -Wall
LD	= $(CC)
ifeq ($(UNAME),Darwin)
LDLIBS 	= -framework GLUT -framework OpenGL -lobjc -lm -lGLEW
LDFLAGS = -I/opt/local/include -L/opt/local/lib
CFLAGS 	:= -I/opt/local/include
else
LDLIBS 	= -lglut -lGL -lGLU -lGLEW -lX11 -lXmu -lXi -lm
LDFLAGS = -I/usr/include/GL/ -L/usr/include/GL
endif
RM	= rm

TARGET 	= obj-view
SRCS 	= main.cpp obj_loader.cpp mesh.cpp
OBJS	= ${SRCS:.cpp=.o}

.SUFFIXES: #clear
.SUFFIXES: .o .cpp

all : $(TARGET)

depend : .depend

.depend : $(SRCS)
	$(CC) $(CFLAGS) -MM $^ > .depend

include .depend

.c.o :
	$(CC) $(CFLAGS) -c $<

$(TARGET) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

TAGS :
	find . -regex ".*\.[cChH]\(pp\)?" -print | etags -

.PHONY : clean TAGS
clean :
	-$(RM) $(TARGET) $(OBJS)

mrproper :
	-$(RM) $(TARGET) $(OBJS) .depend TAGS
