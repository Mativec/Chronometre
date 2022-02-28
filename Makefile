CFLAGS = -ansi -pedantic -Wall
LDFLAGS = -lncurses
CC = gcc
OBJ = Main.o Chrono.o


Chrono: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)


Main.o: Main.c Chrono.h

Chrono.o: Chrono.c Chrono.h

%.o: %.c
	$(CC) -c $< $(CFLAGS)


clean:
	rm -f *.o

uninstall: clean
	rm -f Chrono
