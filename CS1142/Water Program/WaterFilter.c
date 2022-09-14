/**
 * Filter a list of sprinklers so that the only sprinklers left are in the
 * boundaries.
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 03/24/2021
 * Course: CS1141, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Useful data structures
 */
// Sprinkler data structure
typedef struct {
    int ID;     // ID of sprinkler
    int x;      // x-coordinate of sprinkler
    int y;      // y-coordinate of sprinkler
    int r;      // Radius of sprinkler spray
} SPRINKLER;

// Structure for housing sprinkler statitics
typedef struct {
    int min;        // Minimum sprinkler radius
    int max;        // Maximum sprinkler radius
    double avg;     // Average sprinkler radii
    int mode;       // Mode of sprinkler radii
} STATS;

/**
 * Helper methods for filtering sprinklers and displaying sprinkler data
 */
void getValidSprinklers(int width, int height, SPRINKLER *sprinks, int *N);
STATS radiiStats(SPRINKLER *sprinks, int N);
void printData(int width, int height, SPRINKLER *sprinks, int N);

/**
 * Driver for filtering and printing sprinkler data
 */
int main() {
    int width;                      // Width of plot
    int height;                     // Height of plot
    scanf("%d %d", &width, &height);

    int N;                          // Number of sprinklers
    scanf("%d", &N);
    
    // Load sprinklers
    SPRINKLER sprinks[N];           // Unfiltered sprinklers
    for (int i = 0; i < N; i++) {
        SPRINKLER *s = &sprinks[i];
        scanf("%d %d %d %d", &s->ID, &s->x, &s->y, &s->r);
    }

    // Filter the sprinklers
    getValidSprinklers(width, height, sprinks, &N);

    // Print sprinkler data
    printData(width, height, sprinks, N);

    return 0;
}

/**
 * Store valid sprinklers and update array size to only include valid sprinklers
 */
void getValidSprinklers(int width, int height, SPRINKLER *sprinks, int *N) {
    int j = 0;                          // Valid sprinkler counter
    
    // Scan through each sprinkler
    for (int i = 0; i < *N; i++) {
        SPRINKLER s = sprinks[i];       // Current sprinkler

        // Check validity of current sprinkler
        if (0 <= s.x - s.r && s.x + s.r <= width &&  // Validate width-wise spray
            0 <= s.y - s.r && s.y + s.r <= height) { // Validate height-wise spray
            sprinks[j] = s;             // Store valid sprinkler
            j++;
        }
    }

    *N = j;                             // Update valid range of array
}

/**
 * Simple insertion sort for sorting radii of sprinklers
 */
void sort(int *A, int N) {
    int i = 1;

    while (i < N) {
        int x = A[i];
        int j = i - 1;

        while (j >= 0 && A[j] > x) {
            A[j + 1] = A[j];
            j--;
        }

        A[j + 1] = x;
        i++;
    }
}

/**
 * Compute the average value of an integer array
 */
double avg(int *A, int N) {
    double avg = 0.0;

    for (int i = 0; i < N; i++) {
        avg += A[i];
    }

    return avg / N;
}

/**
 * Compute the mode of an integer array
 * NOTE: Requires a non-empty sorted array
 */
int mode(int *A, int N) {
    int cnt = 1;        // Mode counter
    int md = A[0];      // Current mode
    int x = A[0];       // Scanning number
    int xCnt = 1;       // Occurance count of scanning number

    // Scan through each number
    for (int i = 1; i < N; i++) {
        int xNext = A[i];   // Next number to check

        // If scanning number equal next number, then increase occurance
        if (x == xNext) {
            xCnt++;

            // Check if scanning number is the new mode
            if (xCnt > cnt) {
                md = x;         // Update mode
                cnt = xCnt;     // Update count of mode
            }
        } else {
            xCnt = 1;           // Reset scanning count
        }

        x = xNext;              // Store next number
    }

    return md;
}

/**
 * Compute some radii statistics of a set sprinklers
 */
STATS radiiStats(SPRINKLER *sprinks, int N) {
    int r[N];                   // Array of radii

    // Store each radii
    for (int i = 0; i < N; i++) {
        r[i] = sprinks[i].r;
    }

    sort(r, N);                 // Sort the radii
    
    STATS stats;                // Statistics of radii
    stats.min =  r[0];          // Minimum radii
    stats.max =  r[N - 1];      // Maximum radii
    stats.avg =  avg(r, N);     // Average radii
    stats.mode = mode(r, N);    // Mode of radii

    return stats;
}

/**
 * Print sprinkler data and sprinkler statistics
 */
void printData(int width, int height, SPRINKLER *sprinks, int N) {
    // Print plot boundaries
    printf("%d\t%d\n", width, height);

    // Print number sprinklers
    printf("%d\n", N);

    // Print sprinklers and sprinkler data if possible
    if (N > 0) {
        // Compute and print radii stats
        STATS stats = radiiStats(sprinks, N);
        printf("%d\t%d\t%.4lf\t%d\n", stats.min, stats.max, stats.avg, stats.mode);

        // Print each sprinklers data
        for (int i = 0; i < N; i++) {
            SPRINKLER s = sprinks[i];
            printf("%d\t%d\t%d\t%d\n", s.ID, s.x, s.y, s.r);
        }
    }

    return;
}
