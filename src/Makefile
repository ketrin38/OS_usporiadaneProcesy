CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -O2 -s -pedantic -pipe -I.
OBJ=aout.o app.o main.o server.o
LIBS=-lpthread
APPNAME=frinc
RES_DIR=../bin

all: $(OBJ)
	@-gcc -o $(RES_DIR)/$(APPNAME) $^ $(CFLAGS) $(LIBS)

%.o: %.c %.h
	@-$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@-rm -rf *.o
