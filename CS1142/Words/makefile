# Makefile for word processor assignment

# Compilation variables
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -pedantic -O1

# Build all files
default: TestSet Words Paragraph Search

# Make set test bench
TestSet: TestSet.c Set.o
	${CC} ${CFLAGS} TestSet.c Set.o -o TestSet

# Make Words
Words: Words.c Words.h Set.o
	${CC} ${CFLAGS} Words.c Set.o -o Words

# Make Paragraph
Paragraph: Paragraph.c Paragraph.h
	${CC} ${CFLAGS} Paragraph.c -o Paragraph

# Make Search
Search: Search.c Search.h
	${CC} ${CFLAGS} Search.c -o Search

# Build set object
Set.o: Set.c Set.h
	${CC} ${CFLAGS} -c Set.c

# Run TestSet with Valgrind
runTestSet: TestSet
	valgrind --leak-check=full --show-leak-kinds=all ./TestSet

# Zip files for submission
zip:
	zip proj2.zip Words.c Words.h Paragraph.c Paragraph.h Search.c Search.h Set.c

# Clean created files
clean:
	rm -rfv TestSet Set.o Words Paragraph Search
