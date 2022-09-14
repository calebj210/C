/**
 * Read, strip, and store unique words from a file to a given file
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#include "Set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_NAME 255   // Maximum length for a file name
#define MAX_WORD_LEN 255    // Maximum word length to be read in

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

// Function prototypes
void getUniqueWords(int maxWords, FILE* in, FILE* out);
void printStats(Stats* wordStats);
void lowercaseAndStrip(char* dest, const char* src);
int  countVowels(const char* str);

/**
 * Driver for Words routine
 */
int main(int argc, char** argv) {
    // Prompt program usage if needed
    if (argc < 4) {
        printf("Usage: Words <max output words> <in file> <out file>\n");

        return 0;
    }

    // Load max word count
    int maxWords = atoi(argv[1]);
    if (maxWords <= 0) {
        printf("ERROR: max output words must be positive!\n");

        return 0;
    }

    // Load input file
    FILE* in = fopen(argv[2], "r");
    if (in == NULL) {
        printf("ERROR: can't open '%.*s' for input!\n", MAX_FILE_NAME, argv[2]);

        return 0;
    }

    // Load input file
    FILE* out = fopen(argv[3], "w");
    if (out == NULL) {
        printf("ERROR: can't open '%.*s' for output!\n", MAX_FILE_NAME, argv[3]);

        return 0;
    }

    getUniqueWords(maxWords, in, out);  // Read and store unique words

    fclose(in);
    fclose(out);

    return 0; 
}

/**
 * Read and write unique words to a new file
 * while maintaining some stats about the input
 * words
 */
void getUniqueWords(int maxWords, FILE* in, FILE* out) {
    char word[MAX_WORD_LEN + 1] = "";           // Current word to read in
    char stripped[MAX_WORD_LEN + 1] = "";       // Current stripped word
    Stats* stats = calloc(1, sizeof(Stats));    // Statistic storage
    Set* set = malloc(sizeof(Set));             // Unique word list
    initSet(set);                               // Initialize word list

    // Begin reading and processing word file
    while(stats -> uniqueTotal < maxWords && fscanf(in, "%255s", word) > 0) {
        stats -> total++;                       // Increase total read in words
        lowercaseAndStrip(stripped, word);      // Convert and strip current word

        // Try adding new unique word and 
        if (stripped[0] != '\0' && addToSet(set, stripped)){
            stats -> uniqueTotal++;                         // Update unque count
            stats -> vowelCount += countVowels(stripped);   // Update unique vowel count
            stats -> letterCount += strlen(stripped);       // Update unique letter count
            
            // Update shortest word
            if (strlen(stats -> shortest) == 0 || 
                    strlen(stripped) < strlen(stats -> shortest)) {
                strcpy(stats -> shortest, stripped);
            }

            // Update longest word
            if (strlen(stripped) > strlen(stats -> longest)) {
                strcpy(stats -> longest, stripped);
            }
            
            fprintf(out, "%s\n", stripped);     // Add word to output file
        }
    }

    printStats(stats);                          // Output word statistics

    uninitSet(set);                             // Free set data
    free(set);                                  // Free set structure
    free(stats);                                // Free statistics data
}

/**
 * Print unique word statistics
 */
void printStats(Stats* stats) {
    printf("Read %d words\n",  stats -> total);
    printf("Wrote %d words\n", stats -> uniqueTotal);

    if (stats -> uniqueTotal != 0) {
        printf("%.2f%% vowels\n",  (double) stats -> vowelCount / stats -> letterCount * 100);
        printf("Shortest '%s'\n",  stats -> shortest);
        printf("Longest '%s'\n",   stats -> longest);
    }
}

/**
 * Convert and strip a word to lowercase letters or apostrophes and then
 * store it in a destination.
 */
void lowercaseAndStrip(char* dest, const char* src) {
    int idx     = 0;                    // Word index
    int destIdx = 0;                    // Index in destination word

    // Read and strip word
    while (src[idx] != '\0') {
        char c = src[idx];              // Current character

        // Convert character to lowercase if needed 
        if ('A' <= c && c <= 'Z') {
            c += 32;
        }

        // Store character if needed
        if (('a' <= c && c <= 'z') || c == '\'') {
            dest[destIdx++] = c;        // Store character and increment idx
        }

        idx++;
    }
    
    dest[destIdx] = '\0';               // Null terminate destination word
}

/**
 * Count the number of vowels in a word
 */
int countVowels(const char* str) {
    int cnt = 0;            // Number of vowels
    int idx = 0;            // String index

    // Count vowels
    while (str[idx] != '\0') {
        switch (str[idx]) {
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                cnt++;
        }

        idx++;
    }

    return cnt;
}
