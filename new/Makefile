CC=gcc
IDIR=include
SDIR=src
CFLAGS= -g -Wall -I$(IDIR)
TARGET = sn0wbreak
LIBS = -lusb-1.0
SOURCES = sn0wbreak.c libirecovery.c

all:
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(foreach src_file, $(SOURCES), src/$(src_file)) $(LIBS)

clean:
	rm -fr bin