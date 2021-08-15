// Test program for the provided Set data type
// DO NOT MODIFY!

#include "Set.h"

#include <stdio.h>

// Test program for this data type
int main(void)
{
    Set set;

    // Test 1: just a single word
    initSet(&set);
    printf("test 1: hello -> added %d, used %d, capacity %d\n", addToSet(&set, "hello"), set.used, set.capacity);    
    printf("test 1: hello -> added %d, used %d, capacity %d\n", addToSet(&set, "hello"), set.used, set.capacity);    
    uninitSet(&set);

    // Test 2: a bunch of words
    initSet(&set);
    const char* words[] = {"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst", "of", "times"};
    for (int i = 0; i < 12; i++)
    {
        printf("test 2: %s -> added %d, used %d, capacity %d\n", words[i], addToSet(&set, words[i]), set.used, set.capacity);
    }
    uninitSet(&set);

    // Test 3: init and uninit but don't add anything
    initSet(&set);
    printf("test 3: used %d, capacity %d\n", set.used, set.capacity);
    uninitSet(&set);

    return 0;
}

