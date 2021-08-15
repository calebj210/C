/**
 * Unigram language encoding model
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/06/2021
 * Course: CS1142 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

// Maximum length of words that we support
#define MAX_WORD_LEN 255

/**
 * Represents a single entry in a bucket's null-terminated linked list
 */
typedef struct node {
    char* word;  	    // Null-terminated string for this word
    unsigned int count; // How often we saw this word in the training file
    struct node* next;  // Pointer to next Node in this bucket
} Node;

/**
 * Basic function prototypes
 */
unsigned int hashString(const char* str);
double calcUnigramLogProb(unsigned int count, unsigned long total);
void uppercaseAndStrip(char* dest, const char* src);

/**
 * Hashmap with linked separate chaining functions prototypes
 */
Node **populateHashtable(int N, unsigned int *total, bool v);
void put(Node **table, int N, char *k, bool v);
void printHashtable(Node **table, int N, unsigned int total);
void cleanupHashtable(Node **table, int N);

/**
 * Test function prototypes
 */
void testHashString();
void testCalcUnigramLogProb();
void testUppercaseAndStrip();
void testFillAllPrintable(char* str);

/**
 * Driver for constructing unigram probabilities
 */
int main(int argc, char** argv) {
    int N;                  // Size hashtable
    unsigned int total = 0; // Number of words in the hashtable
    bool v = false;         // Verbose setting

    // If no command line input we print out a help message and also run test functions
    if (argc <= 1) {
        printf("Usage: Unigram <hash table size> [debug]\n\n");
        testHashString();
        printf("\n");
        testCalcUnigramLogProb();
        printf("\n");
        testUppercaseAndStrip();
        return 0;
    }

    // Get table size
    if (argc > 1) {
        N = atoi(argv[1]);
        if (N <= 0) {
            printf("ERROR: Table size must be positive!\n");
            return 0;
        }
    }

    // Check for verbose setting
    if (argc > 2) {
        v = atoi(argv[2]);
    }
    
    Node **table = populateHashtable(N, &total, v); // Populate hashtable

    printHashtable(table, N, total);                // Display Unigram info

    cleanupHashtable(table, N);                     // Cleanup memory
    
    return 0;
}

/**
 * Compute the hashcode of a given string
 */
unsigned int hashString(const char* str) {
    unsigned int hashcode = 0;      // Hashcode to compute
    
    // Compute hashcode
    for (int i = 0; str[i] != '\0'; i++) {
        hashcode = 31 * hashcode + str[i];
    }

    return hashcode;
}

/**
 * Compute the unigram log probability of a count
 */
double calcUnigramLogProb(unsigned int count, unsigned long total) {
    double frac = (double) count / total;   // Probability of unigram

    return log10(frac);                     // Log probability
}

/**
 * Convert lowercase letters to upper case
 */
char toUpper(char c) {
    if ('a' <= c && c <= 'z') {
        c -= 32;
    }

    return c;
}

/**
 * Convert string to uppercase and strip any non A-Z or apostrophe
 * characters
 */
void uppercaseAndStrip(char* dest, const char* src) {
    int i = 0;
    for (int j = 0; src[j] != '\0'; j++) {
        char c = toUpper(src[j]);               // Current character
        if (('A' <= c && c <= 'Z') || c == '\'') {
            dest[i] = c;                        // Store valid character
            i++;                                // Increment dest counter 
        }
    }

    dest[i] = '\0';                             // Null terminate string
}

/**
 * Populate hash table from input
 */
Node **populateHashtable(int N, unsigned int *total, bool v) {
    Node **table = calloc(N, sizeof(Node *));    // Hashtable of words

    // Initialize linked list heads
    for (int i = 0; i < N; i++) {
        table[i] = calloc(1, sizeof(Node));
    }

    // Begin reading in words and adding them to the hashtable
    char *cur = calloc(MAX_WORD_LEN + 1, sizeof(char)); // Current word
    char ch = EOF;                      // Current char
    while(1) {
        int wordLength = 0;             // Next word length

        // Read in word
        while (wordLength < MAX_WORD_LEN && (ch = getchar()) != EOF) {
            // Stop reading word when white space is found
            if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
                break;
            }
            
            cur[wordLength] = ch;       // Store character
            wordLength++;               // Increment word length
        }

        cur[wordLength] = '\0';         // Null terminate string

        uppercaseAndStrip(cur, cur);    // Strip current word

        // Add word to table if it is not empty
        if (cur[0] != '\0') {
            char *stripped = calloc(strlen(cur) + 1, sizeof(char));
            strcpy(stripped, cur);      // Copy stripped string
            put(table, N, stripped, v); // Add word to hashtable
            (*total)++;                 // Increment number of words added
        }

        if (ch == EOF) {
            break;
        }
    }

    free(cur);                          // Free temporary word space

    return table;
}

/**
 * Put a key into the hash table
 */
void put(Node **table, int N, char *k, bool v) {
    unsigned int hashcode = hashString(k);      // Hashcode of table
    int bucket = hashcode % N;                  // Get the bucket index

    Node *list = table[bucket];                 // Linked list of bucket
    
    while (list -> next != NULL) {
        list = list -> next;                    // Move to next node
        
        // Check if keyword matches
        if (!strcmp(list -> word, k)) {
            list -> count++;                    // Increment word count
            free(k);                            // Free up duplicate word

            // Display verbose output
            if (v) {
                printf("%s -> hash %u, bucket %d, count %u\n", list -> word, hashcode, bucket, list -> count);
            }

            return;
        }
    }

    // Key not found, create a new node
    list = calloc(1, sizeof(Node)); // New node to inserts
    Node *tmp = table[bucket];      // Temporary head node

    list -> word = k;           // Assign new word
    list -> count = 1;          // Assign base cound
    list -> next = tmp -> next; // Set pointer to next
    tmp -> next = list;         // Fix parent pointer

    // Display verbose output
    if (v) {
        printf("%s -> hash %u, bucket %d, count %u\n", list -> word, hashcode, bucket, list -> count);
    }

    return;
}

/**
 * Fill an array entry with all printable ASCII characters
 */
void testFillAllPrintable(char* str) {
    // Create a maximum size string with all printable ASCII characters
    int index = 0;
    char ch = ' ';
    while (index < MAX_WORD_LEN) {
        str[index] = ch;
        ch++;
        if (ch > 126) {
            ch = ' ';
        }
        index++;
    }
}

/**
 * Print hashtable Unigram stats and info
 */
void printHashtable(Node **table, int N, unsigned int total) {
    for (int i = 0; i < N; i++) {
        Node *list = table[i];
        while (list -> next != NULL) {
            list = list -> next;        // Move to next node in the list
            
            double logProb = calcUnigramLogProb(list -> count, total);

            printf("%.6f %s\n", logProb, list -> word);
        }
    }
}

/**
 * Cleanup hashtable memory
 */
void cleanupHashtable(Node **table, int N) {
    // Loop through each table list
    for (int i = 0; i < N; i++) {
        Node *list = table[i];          // Head of table list

        while (list -> next != NULL) {
            Node *next = list -> next;  // Queue up next node
            free(list -> word);         // Free word storage
            free(list);                 // Free node
            list = next;                // Move to next node
        }

        free(list -> word);             // Free up last word in list
        free(list);                     // Free up last node in list
    }

    free(table);                        // Free up the hashtable
}

/**
 * Test function for the hashString function
 */
void testHashString() {
    char tests[][MAX_WORD_LEN + 1] = {"BAD", "DAB", "GOODFELLOWS", "WRITERSHIP", "a", "A", "abcdefghijklmnopqrstuvwxyz", "1234567890!@#$%^&*()", "", ""};
    testFillAllPrintable(tests[8]);
    
    int i = 0;
    while (strlen(tests[i]) > 0) {
        printf("\"%s\" -> %u\n", tests[i], hashString(tests[i]));
        i++;
    }
}

/**
 * Test function for the calcUnigramLogProb function
 */
void testCalcUnigramLogProb() {
    const int SIZE = 10;
    unsigned int  counts[] = { 5 ,  50 ,   1,    1,   1234,   0 , 100, 1, 1        , UINT_MAX - 10000 };
    unsigned long totals[] = {10 , 100 , 100, 2000, 567890, 123 , 100, 1, ULONG_MAX, UINT_MAX         };
    
    for (int i = 0; i < SIZE; i++) {
        printf("%5u %7lu -> %9.6f\n", counts[i], totals[i], calcUnigramLogProb(counts[i], totals[i]));
    }
}

/**
 * Test function for the stripLower function
 */
void testUppercaseAndStrip() {
    char tests[][MAX_WORD_LEN + 1] = {"b", "B", "bad", "BAD", "BaD", "CAN'T", "well-done", "!L00K-", "1234567890", "abcdefghijklmnopqrstuvwxyz", "", ""};
    char dest[MAX_WORD_LEN + 1];
    testFillAllPrintable(tests[10]);
    
    int i = 0;
    while (strlen(tests[i]) > 0) {
        printf("\"%s\" (len %zu) -> ", tests[i], strlen(tests[i]));
        uppercaseAndStrip(dest, tests[i]);
        printf("\"%s\" (len %zu)\n", dest, strlen(dest));
        i++;
    }
}
