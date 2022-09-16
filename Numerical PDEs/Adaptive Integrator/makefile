# makefile for adaptive integrator
CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O1
LDFLAGS = -lm
VL = valgrind
VLFLAGS = --leak-check=full --show-leak-kinds=all

# Test stack data structure
TestStack: TestStack.c Stack.o
	${CC} ${CFLAGS} TestStack.c Stack.o -o TestStack

TestGaussLeg: TestGaussLeg.c GaussLeg.o
	${CC} ${CFLAGS} TestGaussLeg.c GaussLeg.o -o TestGaussLeg ${LDFLAGS}

TestQuad: TestQuad.c Quad.o GaussLeg.o
	${CC} ${CFLAGS} TestQuad.c Stack.o Quad.o GaussLeg.o -o TestQuad ${LDFLAGS}

Stack.o: Stack.c Stack.h
	${CC} ${CFLAGS} -c Stack.c

GaussLeg.o: GaussLeg.c GaussLeg.h
	${CC} ${CFLAGS} -c GaussLeg.c ${LDFLAGS}

Quad.o: Quad.c Quad.h GaussLeg.o Stack.o
	${CC} ${CFLAGS} -c Quad.c ${LDFLAGS}

runStackTest: TestStack
	${VL} ${VLFLAGS} ./TestStack

runGaussLegTest: TestGaussLeg
	${VL} ${VLFLAGS} ./TestGaussLeg

runQuadTest: TestQuad
	${VL} ${VFLAGS} ./TestQuad

clean:
	rm -f TestStack TestGaussLeg TestQuad *.o
