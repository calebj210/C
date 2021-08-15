/**
 * Search a file for fuzzy matched strings
 *
 * Author: Caleb Jacobs(cajacobs)
 * Date last modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD_LEN 255        // Max word length
#define LINE_END "<br>"          // HTML break line phrase

// Data structure for storing word matching data
typedef struct {
    int totalWords;
    int totalLines;
    int matchedWords;
    int matchedLines;
} MatchData;

// Function prototypes
void findMatches(FILE* in, int tol, const char* key);
void printMatchData(MatchData data);
int  distanceBetween(const char* term, const char* word);

/**
 * Driver for Search routine
 */
int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Usage: Search <max distance> <in file> <term>\n");

        return 0;
    }

    int tol;                    // Max distance for fuzzy matching
    FILE* in;                   // Input file
    char *key = argv[3];        // Search term key

    // Get the max search distance
    tol = atoi(argv[1]);
    if (tol < 0) {
        printf("ERROR: max distance must be non-negative!\n");

        return 0;
    }

    // Get input file
    in = fopen(argv[2], "r");
    if (in == NULL) {
        printf("ERROR: can't open '%s' for input!\n", argv[2]);

        return 0;
    }

    findMatches(in, tol, key);  // Get and print matches

    fclose(in);                     // Close input file

    return 0;
}

/**
 * Find and print the term matches in an input file
 */
void findMatches(FILE* in, int tol, const char* key) {
    char word[MAX_WORD_LEN + 1] = "";       // Current word
    char endLine[256] = LINE_END;           // Endline phrase
    MatchData data = {0, 0, 0, 0};          // Matching data
    bool thisLineMatched = false;           

    // Begin reading in words
    while (fscanf(in, "%255s", word) > 0) {
        // Check if we are the end of a line
        if (!strcmp(word, endLine)) {
            printf(LINE_END "\n");
            data.totalLines++;

            // Check if we had any matches on this line
            if (thisLineMatched) {
                data.matchedLines++;
                thisLineMatched = false;
            }

            continue;
        }

        data.totalWords++;                      // Increment the number of words read

        int dist = distanceBetween(key, word);  // Fuzzy distance between key and word

        // Check if word is a match
        if (0 <= dist && dist <= tol) {
            data.matchedWords++;                // Increase number of matched words
            thisLineMatched = true;             // Mark the line as matched

            printf("*%s* ", word);
        } else {
            printf("%s ", word);
        }
    }

    printMatchData(data);
}

/**
 * Print the total match results
 */
void printMatchData(MatchData data) {
    printf("Total words: %d\n", data.totalWords);
    printf("Total lines: %d\n", data.totalLines);
    printf("Matched words: %d\n", data.matchedWords);
    printf("Matched lines: %d\n", data.matchedLines);
}

/**
 * Compute the fuzzy distance between two words
 */
int distanceBetween(const char* term, const char* word) {
    int dist = 0;

    // Check if words are different length
    if (strlen(term) != strlen(word)) {
        return -1;
    }

    // Compute word distance
    for (size_t i = 0; i < strlen(term); i++) {
        if (term[i] != word[i]) {
            dist++;
        }
    }

    return dist;
}
