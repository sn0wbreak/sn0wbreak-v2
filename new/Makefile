CC=gcc
INCDIR = include
OUTDIR = bin
CFLAGS= -g -Wall -I$(INCDIR)
TARGET = sn0wbreak

SOURCES = sn0wbreak.c libirecovery.c

ifeq ($(shell gcc -dumpmachine), mingw32)
	LIBS = -lsetupapi
else
	LIBS = -lusb-1.0
endif

all:
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -o $(OUTDIR)/$(TARGET) $(foreach src_file, $(SOURCES), src/$(src_file)) $(LIBS)

clean:
	rm -fr $(OUTDIR)