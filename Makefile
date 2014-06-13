CC=gcc
CFLAGS= -g -Wall
LIBS = -lusb -lcurl
TARGET=sn0wbreak-2
SOURCES=sn0wbreak-2.c \
	partial.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm $(TARGET)
