/**
 * Function prototypes for Search.c
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date last modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>

#define LINE_END "<br>"             // HTML break line phrase

// Data structure for storing word matching data
typedef struct {
    int totalWords;
    int totalLines;
    int matchedWords;
    int matchedLines;
} MatchData;

void findMatches(FILE* in, int tol, const char* key);
void printMatchData(MatchData data);
int  distanceBetween(const char* term, const char* word);

#endif
