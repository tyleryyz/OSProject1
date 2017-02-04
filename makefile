CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

sim01 : sim01.o parseConfig.o
	$(CC) $(LFLAGS) sim01.o parseConfig.o -o sim01

sim01.o : sim01.c parseConfig.h
	$(CC) $(CFLAGS) sim01.c

parseConfig.o : parseConfig.c parseConfig.h
	$(CC) $(CFLAGS) parseConfig.c

clean:
	\rm *.o sim01
