CC=cc
CFLAGS= -g -Wall
LIBS = -lusb -lcurl -lz
TARGET=sn0wbreak-2
SOURCES=sn0wbreak-2.c \
	partial.c

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

clean:
	rm $(TARGET)
