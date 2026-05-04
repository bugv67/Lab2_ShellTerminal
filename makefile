CC = gcc
CFLAGS = -g -Wall -m32

all: myshell looper printers

myshell: myshell.o LineParser.o
	$(CC) $(CFLAGS) -o myshell myshell.o LineParser.o

looper: Looper.o
	$(CC) $(CFLAGS) -o looper Looper.o

printers: Printers.o
	$(CC) $(CFLAGS) -o printers Printers.o

LineParser.o: LineParser.c LineParser.h
	$(CC) $(CFLAGS) -c LineParser.c

Looper.o: Looper.c
	$(CC) $(CFLAGS) -c Looper.c

Printers.o: Printers.c
	$(CC) $(CFLAGS) -c Printers.c

myshell.o: myshell.c LineParser.h
	$(CC) $(CFLAGS) -c myshell.c

.PHONY: clean all

clean:
	rm -f *.o looper printers myshell