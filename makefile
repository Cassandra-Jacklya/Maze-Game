# Makefile Variables
CFLAGS  = -Wall -ansi -pedantic -Werror -g
OBJS = maze.o terminal.o playGame.o LinkedList.o
EXEC = maze
CC = gcc

$(EXEC) : $(OBJS) 
	$(CC) $(OBJS) -o $(EXEC)

maze.o : maze.c terminal.h playGame.h LinkedList.h
	$(CC) $(CFLAGS) -c maze.c

terminal.o : terminal.c terminal.h 
	$(CC) $(CFLAGS) -c terminal.c

LinkedList.o : LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -c LinkedList.c

playGame.o : playGame.c playGame.h 
	$(CC) $(CFLAGS) -c playGame.c

clean :
	rm -f $(EXEC) $(OBJS)
