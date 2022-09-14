// Implementation file for the Set data type
// You need to add the implementation for the uninitSet function

#include "Set.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize a List structure
// DO NOT MODIFY!
void initSet(Set* set)
{
    // Initial capacity of the array
    const int START_SIZE = 4;

    // Create an array with START_SIZE elements are set to NULL
    set->items = malloc(sizeof(char *) * START_SIZE);
    for (int i = 0; i < START_SIZE; i++)
    {
        set->items[i] = NULL;
    }

    set->capacity = START_SIZE;
    set->used = 0;
}

// Add the null terminated string str to the list if it doesn't already exist
// Returns true if str was added, false if str was already in the list
// DO NOT MODIFY!
bool addToSet(Set* set, const char* str)
{
    // Check for match in existing strings
    for (int i = 0; i < set->used; i++)
    {
        if (strcmp(set->items[i], str) == 0)
        {
            return false;
        }
    }

    // If we made it through the loop, we need to add to set
    if (set->used == set->capacity)
    {
        // We have run out of space in the set, double our array size
        char** items2 = realloc(set->items, sizeof(char *) * set->capacity * 2);
        if (items2 == NULL)
        {
            printf("ERROR: failed to realloc set, this shouldn't happen!\n");
            return false;
        }
        set->items = items2;
        set->capacity *= 2;
    }

    // Make a deep copy of the new string to add to set    
    set->items[set->used] = malloc(strlen(str) + 1);
    if (set->items[set->used] == NULL)
    {
        printf("ERROR: failed to malloc word, this shouldn't happen!\n");
        return false;
    }
    strcpy(set->items[set->used], str);
    set->used++;

    return true;
}

// Uninitialize a Set structure by freeing up its allocated memory
void uninitSet(Set* set)
{
    // Clean each word entry
    for (int i = 0; i < (set -> used); i++) {
        free(set -> items[i]);
    }

    // Free word list
    free(set -> items);
}
