CC = gcc
CFLAGS = -Wall -pedantic -ansi -g
OBJ1 = TurtleGraphics.o TurtleIO.o LinkedList.o effects.o
OBJ2 = TurtleGraphicsS.o TurtleIO.o LinkedList.o effects.o
OBJ3 = TurtleGraphicsD.o TurtleIO.o LinkedList.o effects.o
EXEC1 = TurtleGraphics
EXEC2 = TurtleGraphicsSimple
EXEC3 = TurtleGraphicsDebug

all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1) : $(OBJ1)
	$(CC) $(OBJ1) -o  $(EXEC1) -lm

$(EXEC2) : $(OBJ2)
	$(CC) $(OBJ2) -o $(EXEC2) -lm

$(EXEC3) : $(OBJ3)
	$(CC) $(OBJ3) -o $(EXEC3) -lm

TurtleGraphics.o: TurtleGraphics.c TurtleGraphics.h TurtleIO.h LinkedList.h effects.h
	$(CC) -c TurtleGraphics.c $(CFLAGS) 

TurtleIO.o: TurtleIO.c TurtleIO.h LinkedList.h TurtleGraphics.h effects.h
	$(CC) -c TurtleIO.c $(CFLAGS)

LinkedList.o: LinkedList.c LinkedList.h
	$(CC) -c LinkedList.c $(CFLAGS)

effects.o: effects.c effects.h
	$(CC) -c effects.c $(CFLAGS)

TurtleGraphicsS.o: TurtleGraphics.c TurtleIO.o LinkedList.o effects.o TurtleGraphics.h
	$(CC) -c TurtleGraphics.c -D SIMPLE=1 $(CFLAGS) -o TurtleGraphicsS.o

TurtleGraphicsD.o: TurtleGraphics.c TurtleIO.o LinkedList.o effects.o TurtleGraphics.h
	$(CC) -c TurtleGraphics.c -D DEBUG=1 $(CFLAGS) -o TurtleGraphicsD.o

valgrind: $(EXEC)
	valgrind --leak-check=full --track-origins=yes ./$(EXEC1) charizard.txt

clean:
	rm -f $(EXEC1) $(OBJ1) $(EXEC2) $(OBJ2) $(EXEC3) $(OBJ3)	
