/**
 * Generate a system of random sprinklers
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date last modified: 03/24/2021
 *
 * Course: CS1141, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Sprinkler data structure
 */
typedef struct {
    int ID;     // ID of sprinkler
    int x;      // x-coordinate of sprinkler
    int y;      // y-coordinate of sprinkler
    int r;      // Radius of sprinkler spray
} SPRINKLER;

/**
 * Helper routines 
 */
int       verifyData(int width, int height, int N, int minR, int maxR);
SPRINKLER randSprinkler(int width, int height, int minR, int maxR, int ID);
void      printData(SPRINKLER *data, int N, int width, int height);

/**
 * Driver for generating and displaying random sprinklers
 */
int main(int argc, char **argv) {
    // Prompt user of WaterRand functionality
    if (argc < 7) {
        printf("Usage: WaterRand <east size> <north size> <num> <min radius> <max radius> <seed>");
        return 0;
    }

    // Get and store input data
    int width  = atoi(argv[1]); // East size
    int height = atoi(argv[2]); // North size
    int N      = atoi(argv[3]); // Number of sprinklers
    int minR   = atoi(argv[4]); // Minimum radius of sprinkler
    int maxR   = atoi(argv[5]); // Maximum radius of sprinkler
    int s      = atoi(argv[6]); // Random number seed

    // Verify data
    if (!verifyData(width, height, N, minR, maxR)) {
        printf("ERROR: invalid arguments!\n");
        return 0;
    }
    
    // Seed random number generator
    srand(s);

    // Generate an array of random sprinklers
    SPRINKLER sprinklers[N];
    for (int i = 0; i < N; i++) {
        sprinklers[i] = randSprinkler(width, height, minR, maxR, i);
    }
    
    // Display sprinkler data
    printData(sprinklers, N, width, height);

    return 0;
}

/**
 * Check if the data entered by the user is valid
 */
int verifyData(int width, int height, int N, int minR, int maxR) {
    // Plot constraints
    if (!(width > 0 && height > 0)) {
        return 0;
    }

    // Number of sprinkler constraints
    if (!(1 <= N && N <= 10000)) {
        return 0;
    }

    // Sprinkler constraints
    if (!(1 <= minR && minR <= 100 && 1 <= maxR && maxR <= 100 && minR <= maxR)) {
        return 0;
    }

    return 1;
}

/**
 * Generate a random sprinkler
 */
SPRINKLER randSprinkler(int width, int height, int minR, int maxR, int ID) {
    SPRINKLER sprink;                           // Random sprinkler
    sprink.ID = ID;                             // Set ID
    sprink.x  = rand() % (width + 1);           // Set x-coordinate
    sprink.y  = rand() % (height + 1);          // Set y-coordinate
    sprink.r  = rand() % (maxR - minR + 1) + minR;  // Set radius

    return sprink;
}

/**
 * Print sprinkler and land plot data
 */
void printData(SPRINKLER *sprinks, int N, int width, int height) {
    printf("%d\t%d\n", width, height);      // Print plot size
    printf("%d\n", N);                      // Print number of sprinklers
    
    // Print data of each sprinkler
    for (int i = 0; i < N; i++) {
        SPRINKLER cur = sprinks[i];
        printf("%d\t%d\t%d\t%d\n", cur.ID, cur.x, cur.y, cur.r);
    }

    return;
}
