// Header file for the Set data type
// DO NOT MODIFY!

#ifndef SET_H
#define SET_H

#include <stdbool.h>

// Set data structure that holds a set of unique strings
// The set will automatically expand as strings as needed
typedef struct 
{
    char** items;   // Array of pointers to character buffers
    int capacity;   // Current allocated size of items array (maximum strings we can hold)
    int used;       // Number of currently used positions in items array
} Set;

// Function prototypes
void initSet(Set* set);
bool addToSet(Set* set, const char* str);
void uninitSet(Set* set);

#endif
