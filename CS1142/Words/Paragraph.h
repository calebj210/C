/**
 * Data structures and function prototypes needed
 * for Paragraph.c
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date last modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include <stdio.h>
#include <stdbool.h>

#define MAX_FILE_NAME 255
#define MAX_WORD_LEN  255

// Array List data structure for storing words
typedef struct {
    int capacity;   // Max capacity of array list
    int size;       // Number of entries in array list
    char** list;    // Array of words
} ArrayList;

// Array List functions
void  initArrayList(ArrayList* list);
void  uninitArrayList(ArrayList* list);
void  addLast(ArrayList* list, const char* word);
char* get(ArrayList* list, int idx);
void  resizeArrayList(ArrayList* list);

// Paragraph construction functions
void readFileInput(ArrayList* list, FILE* in);
void makeParagraph(ArrayList* list, int words, int width, bool debug);
void printDebugLine(int width);

#endif
