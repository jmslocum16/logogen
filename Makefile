PF = 

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
LIBS = -lGL -lglut -lz -lX11 -ldl -lXext
INCLUDE = -I/usr/local/include -I/usr/include -I/usr/X11/include -I/p/include -I/usr/include/X11 -I../common
LIBDIR = -L/usr/local/lib -L/usr/lib -L/usr/X11/lib -L/p/lib -L/usr/lib/x86_64-linux-gnu
endif
ifeq ($(UNAME), Darwin)
LIBS = -framework OpenGL -framework GLUT
LIBDIR = -L/usr/lib -L/usr/X11/lib
INCLUDE = -I/usr/include -I../common
endif

CFLAGS = -g $(PF)

CC = g++

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

ALL.O = logogen.o bitmap.o

logogen: $(ALL.O) bitmap.h
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(COMMON.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f *.o logogen
