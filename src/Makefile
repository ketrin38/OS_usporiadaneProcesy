CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -g -pedantic -pipe -I.
OBJ=Front.o Main.o Parser.o Matica.o App.o
LIBS=-lpthread
APPNAME=usp_procesy
RES_DIR=../bin

all: $(OBJ)
	@-gcc -o $(RES_DIR)/$(APPNAME) $^ $(CFLAGS) $(LIBS)

%.o: %.c %.h
	@-$(CC) -c $(CFLAGS) -o $@ $<

clean:
	@-rm -rf *.o
