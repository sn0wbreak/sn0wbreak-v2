CC=gcc
IDIR=include
SDIR=src
CFLAGS= -g -Wall -I$(IDIR)
LIBS = -lusb-1.0
TARGET = sn0wbreak

SOURCES = sn0wbreak.c libirecovery.c

all: $(TARGET)

$(TARGET): $(SDIR)/$(TARGET).c
	mkdir -p bin
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(foreach src_file, $(SOURCES), src/$(src_file)) $(LIBS)

clean:
	rm -fr bin