/**
 * Given a filtered set of sprinklers, find a sprinkler configuration
 * such that the most area (or close to) is watered.
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date last modified: 03/24/2021
 * Course: CS1141, Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Pi constant
#undef M_PI
#define M_PI (3.14159265358979323846264338327950288)

/**
 * Sprinkler data structure
 */
typedef struct {
    int ID;         // Sprinkler ID
    int x;          // x-coordinate of sprinkler
    int y;          // y-coordinate of sprinkler
    int r;          // Spray radius of sprinkler
    bool state;     // Sprinkler spraying state
} SPRINKLER;

/**
 * Structure for housing sprinkler statistics
 */
typedef struct {
    int min;        // Minimum sprinkler radius
    int max;        // Maximum sprinkler radius
    double avg;     // Average sprinkler radii
    int mode;       // Mode of sprinkler radii
} STATS;

/**
 * Helper methods
 */
void   getPack(SPRINKLER *sprinks, int N);
double distanceBetween(SPRINKLER s1, SPRINKLER s2);
bool   sprinklerOverlap(SPRINKLER s1, SPRINKLER s2);
void   printActiveSprinklers(int width, int height, STATS stats, SPRINKLER *sprinks, int N);
bool   coordinateCovered(int x, int y, SPRINKLER *sprinks, int N);
void   printWaterPlot(int width, int height, SPRINKLER *sprinks, int N);

/**
 * Driver for packing sprinklers
 *
 * Takes one command line argument to specify the drawing of the sprinkler field
 */
int main(int argc, char **argv) {
    // Get state of verbose output
    bool verbose = false;
    if (argc > 1) {
        if (atof(argv[1]) != 0) {
            verbose = true;
        }
    }

    // Load plot
    int width;              // Width of plot
    int height;             // Height of plot
    scanf("%d %d", &width, &height);

    // Load sprinkler count
    int N;                  // Number of sprinklers
    scanf("%d", &N);

    // Load sprinkler stats
    STATS stats;            // Statistics of sprinklers
    scanf("%d %d %lf %d", &stats.min, &stats.max, &stats.avg, &stats.mode);

    // Load sprinklers
    SPRINKLER sprinks[N];   // Given sprinklers
    for (int i = 0; i < N; i++) {
        SPRINKLER *s = &sprinks[i];
        scanf("%d %d %d %d", &s->ID, &s->x, &s->y, &s->r);
        s->state = false;
    }
    
    // Pack sprinklers
    getPack(sprinks, N);

    // Print field and sprinkler data
    printActiveSprinklers(width, height, stats, sprinks, N);

    // Print water-land plot if verbose is on
    if (verbose) {
        printWaterPlot(width, height, sprinks, N); 
    }

    return 0;
}

/**
 * Sort an array of sprinklers by decending radii using an insertion sort.
 *
 * Sorting the sprinklers greatly increases the ease and efficiency of
 * computing the sprinkler packing. Insertion sort works in such a way
 * as to not disrupt the ID order of sprinklers with the same radii.
 */
void decSort(SPRINKLER *S, int N) {
    int i = 1;
    
    while (i < N) {
        SPRINKLER x = S[i];
        int j = i - 1;
        while (j >= 0 && S[j].r < x.r) {
            S[j + 1] = S[j];
            j--;
        }
        S[j + 1] = x;
        i++;
    }
}

/**
 * Compute the Euclidean distance between two sprinklers, s1 and s2
 */
double distanceBetween(SPRINKLER s1, SPRINKLER s2) {
    double dx = s1.x - s2.x;
    double dy = s1.y - s2.y;

    return sqrt(dx * dx + dy * dy);
}

/**
 * Check if two sprinklers, s1 and s2, overlap in their watering areas
 */
bool sprinklerOverlap(SPRINKLER s1, SPRINKLER s2) {
    double dist = distanceBetween(s1, s2);
    
    return (dist < s1.r + s2.r);
}

/** 
 * Sort and pack a plot of land with sprinklers
 */
void getPack(SPRINKLER *sprinks, int N) {
    decSort(sprinks, N);        // Sort sprinklers by decending radii

    // Begin packing plot of land
    for (int i = 0; i < N; i++) {
        bool addable = true;                    // Reset addable state
        SPRINKLER new = sprinks[i];             // Next potential sprinkler

        for (int j = 0; (addable && j < i); j++) {
            SPRINKLER old = sprinks[j];         // Previously checked sprinkler

            // Check if new sprinkler overlaps previously added sprinklers
            if (old.state && sprinklerOverlap(new, old)) {
                addable = false;
            }
        }
        
        // If sprinkler is still addable, add it to the plot
        if (addable) {
            sprinks[i].state = true;
        }
    }

    return;
}

/**
 * Print activated sprinklers and watering statistics
 */
void printActiveSprinklers(int width, int height, STATS stats, SPRINKLER *sprinks, int N) {
    int    sCntr = 0;               // Number of activated sprinklers
    double area  = 0.0;             // Area of watered land

    // Print Preliminary field and sprinler data
    printf("Field size: %d x %d\n", width, height);
    printf("Total sprinklers: %d\n", N);
    printf("Radius: min %d, max %d, avg %.4lf, mode %d\n", stats.min, stats.max, stats.avg, stats.mode);

    // Print activated sprinkler data
    for (int i = 0; i < N; i++) {
        SPRINKLER cur = sprinks[i];

        if (cur.state) {
            sCntr++;
            area += M_PI * cur.r * cur.r;   // Add to the area
            printf("Add %d, (%d, %d) r=%d\n", cur.ID, cur.x, cur.y, cur.r);
        }
    }

    // Print some more sprinkler data
    printf("Sprinklers added: %d\n", sCntr);
    
    // Compute covered area
    double covered;
    if (width == 0 || height == 0) {
        covered = 100 * (double) sCntr / (width + height);      // Flat land plot 
    } else {
        covered = 100 * area / (width * height);                // 2D land plot
    }

    // Print amount of area covered
    printf("Covered area: %.4lf%%\n", covered);

    return;
}

/**
 * Compute the distance between two integer points
 */
double intDist(int x1, int y1, int x2, int y2) {
    int dx = x1 - x2;               // Change in x-coords
    int dy = y1 - y2;               // Change in y-coords

    return sqrt(dx*dx + dy*dy);     // Distance between points
}

/**
 * Check if a given coordinate is watered by an activated sprinkler
 */
bool coordinateCovered(int x, int y, SPRINKLER *sprinks, int N) {
    bool covered = false;           // Coordinate covered indicator
    
    // Check if any of the activated sprinklers covered the coordinate
    for (int i = 0; i < N; i++) {
        SPRINKLER s = sprinks[i];   // Current sprinkler to check

        // Check active sprinkler
        if (s.state && intDist(x, y, s.x, s.y) <= s.r) {
            covered = true;
            break;
        }
    }

    return covered;
}

/**
 * Display watered plot of land
 */
void printWaterPlot(int width, int height, SPRINKLER *sprinks, int N) {
    for (int y = height; y >= 0; y--) {
        for (int x = 0; x <= width; x++) {
            // Get plot character
            char c = (coordinateCovered(x, y, sprinks, N) ? '@' : '.');

            putchar(c); // Print plot character
        }
        putchar('\n');  // Start a newline
    }
}
