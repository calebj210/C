# makefile for adaptive integrator
CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Wextra -O1
LDFLAGS = -lm

# Test stack data structure
TestStack: TestStack.c Stack.o
	${CC} ${CFLAGS} TestStack.c Stack.o -o TestStack  ${LDFLAGS}

Stack.o: Stack.c Stack.h
	${CC} ${CFLAGS} -c Stack.c

runStackTest: TestStack
	valgrind --leak-check=full --show-leak-kinds=all ./TestStack

clean:
	rm -f TestStack *.o
