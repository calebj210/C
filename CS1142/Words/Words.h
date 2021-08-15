/**
 * Function prototypes and data structures for Words.c
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date last modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#ifndef WORDS_H
#define WORDS_H

#include <stdlib.h>
#include <stdio.h>

#define MAX_WORD_LEN 255 // Maximum word length to be read in

/**
 * Word statistics structure
 */
typedef struct {
    int  total;                         // Total number of words
    int  uniqueTotal;                   // Number of unique words
    int  letterCount;                   // Number of letters
    int  vowelCount;                    // Number of vowels
    char shortest[MAX_WORD_LEN + 1];    // Shortest word
    char longest[MAX_WORD_LEN + 1];     // Longest word
} Stats;

void getUniqueWords(int maxWords, FILE* in, FILE* out);
void printStats(Stats* wordStats);
void lowercaseAndStrip(char* dest, const char* src);
int  countVowels(const char* str);

#endif
