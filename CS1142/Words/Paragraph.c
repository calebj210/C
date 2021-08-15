/**
 * Construct paragraphs from a specified text file
 * with specified dimensions.
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 19/04/2021
 * Course: CS1141 Spring 2021
 */

#include "Paragraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Driver for generating random paragraphs
 */
int main(int argc, char** argv) {
    // Prompt program usage if needed
    if (argc < 5) {
        printf("Usage: Paragraph <words> <width> <in file> <seed> [header/footer]\n");

        return 0;
    }

    int words;              // Number of words to add to paragraph
    int width;              // Width of paragraph
    FILE* in;               // Input file
    bool debug = false;     // Check for debug lines

    // Load number of words
    words = atoi(argv[1]);
    if (words <= 0) {
        printf("ERROR: words must be positive!\n");

        return 0;
    }

    // Load paragraph width
    width = atoi(argv[2]);
    if (width <= 0) {
        printf("ERROR: width must be positive!\n");

        return 0;
    }

    // Load input file
    in = fopen(argv[3], "r");
    if (in == NULL) {
        printf("ERROR: can't open '%.*s' for input!\n", MAX_FILE_NAME, argv[3]);

        return 0;
    }

    // Load seed
    srand(atoi(argv[4]));

    // Load header/footer debug check
    if (argc > 5 && atoi(argv[5]) != 0) {
        debug = true;
    }
    
    ArrayList list;                             // Create array list for words
    initArrayList(&list);                       // Initialize array list

    readFileInput(&list, in);                   // Read input file into array list
    makeParagraph(&list, words, width, debug);  // Create random paragraph
    
    uninitArrayList(&list);                     // Free up array list memory
    fclose(in);                                 // Close input file

    return 0; 
}

/**
 * Initialize an array list
 */
void initArrayList(ArrayList* list) {
    list -> capacity = 16;
    list -> size     = 0;
    list -> list     = calloc(16, sizeof(char*));
}

/**
 * Clear memory of array list
 */
void uninitArrayList(ArrayList* list) {
    for (int i = 0; i < list -> size; i++) {
        free(list -> list[i]);
    }

    free(list -> list);
}

/**
 * Add a new element to the end of an array list
 */
void addLast(ArrayList* list, const char* word) {
    // Resize array if more space is needed
    if (list -> size == list -> capacity) {
        resizeArrayList(list);
    }

    // Create and store word in array list
    list -> list[list -> size] = calloc(1, sizeof(char) * (strlen(word) + 1));
    strcpy(list -> list[list -> size], word);
        
    list -> size++;     // Increment size of array list
}

/**
 * Get an element in the array list
 */
char* get(ArrayList* list, int idx) {
    // Check that index is valid
    if (idx < 0 || idx >= list -> size) {
        return NULL;
    }

    return list -> list[idx];
}

/**
 * Double the capacity of an array list
 */
void resizeArrayList(ArrayList* list) {
    list -> capacity *= 2;          // Double capacity

    // Resize word array
    list -> list = realloc(list -> list, sizeof(char*) * list -> capacity);
}

/**
 * Read words from a file into an array list
 */
void readFileInput(ArrayList* list, FILE* in) {
    char word[MAX_WORD_LEN + 1] = "";       // Current word from file

    // Read in each word in the file
    while (fscanf(in, "%255s", word) >= 1) {
        addLast(list, word);
    }
}

/**
 * Create a random paragraph from a set of words
 */
void makeParagraph(ArrayList* list, int words, int width, bool debug) {
    // Print header if needed
    if (debug) {
        printDebugLine(width);
    }

    int curLen = 0;                     // Length of current line
    for (int i = 0; i < words; i++) {
        if (curLen >= width) {
            printf("<br>\n");
            curLen = 0;
        }

        char* word = get(list, rand() % (list -> size));    // Get random word
        
        printf("%s ", word);
        curLen += strlen(word) + 1;
    }

    if (curLen != 0) {
        printf("<br>\n");
    }

    // Print footer if needed
    if (debug) {
        printDebugLine(width);
    }
}

/**
 * Print header/footer output
 */
void printDebugLine(int width) {
    for (int i = 1; i <= width; i++) {
        printf("%d", i % 10);
    }

    printf(" <br>\n");
}
