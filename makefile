CC = gcc -std=gnu99
CFLAGS = -Iinclude -g -O0

vpath %.c src/user
vpath %.h include

cmd:main.o
	$(CC) -o cmd main.o $(CFLAGS) -L. -lutils

main.o:main.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
