CC = gcc
CFLAGS = -g -Wall
OBJECTS = chunk.o chunk_helper_functions.o

all:chunk

chunk: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o:%.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f chunk
	rm -f chunk.o
	rm -f chunk_helper_functions.o
	rm -f chunk.dSYM
