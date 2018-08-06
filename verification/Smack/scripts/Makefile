YDIR = "../../../../rpython"
CC = gcc
CFLAGS =-c -Wall
SOURCES = asm.c \
	asm_gcc_x86.c \
	asm_msvc.c \
	cygwin_wait.c \
	debug_print.c \
	debug_traceback.c \
	dtoa.c \
	entrypoint.c \
	exception.c \
	instrument.c \
	int.c \
	ll_strtod.c \
	mem.c \
	profiling.c \
	rtyper.c \
	signals.c \
	stack.c \
	support.c \
	thread.c \
	threadlocal.c 
        
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = pypy
INCLUDEDIRS = -I$(RPYDIR)/translator/c \
              -I/home/vagrant/smack/examples/dataset/usession-default-2/testing_1 \
	      -I/usr/include
all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 	
	$(CC) $(LDFLAGS) $(INCLUDEDIRS) -fprofile-arcs -ftest-coverage -c  $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDEDIRS) -D IEEE_8087
