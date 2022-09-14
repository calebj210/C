/**
 * Genetic algorithm for solving: 
 * a0*1 + a1 *2 + ... + a(n-1) n = C.
 *
 * Author: Caleb Jacobs
 * User ID: cajacobs
 * Course: CS1142 Spring 2021
 * Date last modified: 02/13/2021
 */

#include <stdio.h>
#include <stdlib.h>

/* Helper routines */
int genRand(int a, int b);
int getFit(int N, int *gene, int C);
int findMin(int size, int *a);
int findMax(int size, int *a);

/* Verbose routines */
void printGen(int P, int N, int genes[P][N], int *fits, int gen);
void printGene(int N, int *gene);
void printBest(int P, int N, int genes[P][N], int *fits, int gen);

/* Evolutionary routines */
void  cross(int P, int N, int genes[P][N], int *fits, int C, int v);
void mutate(int P, int N, int genes[P][N], int *fits, int C, int v);

/* Simulation driver */
int main(int argc, char **argv) {
    /* Insufficient argument */
    if (argc < 6) {
        printf("Usage: GA <constant> <individuals> <genes> <max steps> <seed> [verbose]\n");
        return 0;
    }

    int C = atoi(argv[1]);	/* Target result */
    int P = atoi(argv[2]);	/* Number of individuals */
    int N = atoi(argv[3]);	/* Number of genes */
    if ((P <= 1) || (N <= 1)) {
        printf("ERROR: number of individuals and genes must be greater than 1!\n");
        return 0;
    }
    int maxIts = atoi(argv[4]);	/* Maximum generations allowed */
    int v = 0;	                /* Verbose setting */
    if (argc > 6) {
        v = 1;
    }

    srand(atoi(argv[5])); 	/* Set random seed */

    /* Initialize first generation of individuals and compute their fitness*/
    int genes[P][N];		/* Gene array */
    int fits[P];		/* Fitness array */
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < N; j++) {
            genes[i][j] = genRand(0, 9);
        }
        fits[i] = getFit(N, genes[i], C);
    }

    /* Begin solving genetically */
    int gen = 0;
    int min = fits[findMin(P, fits)];
    while (gen < maxIts && min != 0) {
        /* If verbose, print current generation */
        if (v != 0) {
            printGen(P, N, genes, fits, gen);
        }

        /* Perform mutation or crossover of genes */
        if (gen % 2 == 0) {
            cross(P, N, genes, fits, C, v);
        } else {
            mutate(P, N, genes, fits, C, v);
        }


        min = fits[findMin(P, fits)]; 	/* Compute the best fitness */

        gen++;			                /* Go to next generation */
    }

    /* Print final generation data if verbose */
    if (v != 0) {
        printGen(P, N, genes, fits, gen);
    }
    printBest(P, N, genes, fits, gen); /* Print best individual */

    return 0;
}

/* Generate a random integer in the range [a, b] */
int genRand(int a, int b) {
    return rand() % (b - a + 1) + a;
}

/* Compute the fitness of an individual */
int getFit(int N, int *gene, int C) {
    int fit = 0; /* Fitness */

    /* Compute gene solution */
    for (int i = 0; i < N; i++) {
        fit += gene[i] * (i + 1);
    }

    /* Find difference between gene solution and true solution */
    fit -= C;

    /* Absolute value of fitness */
    return (fit >= 0) ? fit : -fit;
}

/* Find the index of the smallest value in an array*/
int findMin(int size, int *a) {
    int idx = 0;		/* Minimum index */
    int min = a[0];		/* Minimum value */
    for (int i = 1; i < size; i++) {
        if (a[i] < min) {
            min = a[i];
            idx = i;
        }
    }

    return idx;
}

/* Find the index of the largest value in an array*/
int findMax(int size, int *a) {
    int idx = 0;		/* Maximum index */
    int max = a[0];		/* Maximum value */
    for (int i = 1; i < size; i++) {
        if (a[i] > max) {
            max = a[i];
            idx = i;
        }
    }

    return idx;
}

/* Compute average of array */
double getAvg(int size, int *a) {
    double sum = 0;		/* Sum of fitness values */
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }

    return sum / size;		/* Return average */
}

/* Print current generation of individuals */
void printGen(int P, int N, int genes[P][N], int *fits, int gen) {
    int min = fits[findMin(P, fits)];      /* Smallest fitness value */
    int max = fits[findMax(P, fits)];	   /* Maximum fitness value */
    double avg = getAvg(P, fits);	       /* Average of fitness values */

    /* Print generation data */
    printf("*** Generation %d ***\n", gen);
    for (int i = 0; i < P; i++) {
        printf("%d: ", i);
        printGene(N, genes[i]);
        printf(", fitness=%d\n", fits[i]);
    }
    printf("avg=%.4f, min=%d, max=%d\n", avg, min, max);

    return;
}

/* Print an individual's gene sequence */
void printGene(int N, int *gene) {
    for (int i = 0; i < N; i++) {
        printf("%d", gene[i]);
    }

    return;
}

/* Print the best gene sequence */
void printBest(int P, int N, int genes[P][N], int *fits, int gen) {
    int gmin = findMin(P, fits);       /* Index of best individual */

    /* Print individual's data */
    printf("BEST %d: ", gmin);
    printGene(N, genes[gmin]);
    printf(", fitness=%d, steps=%d\n", fits[gmin], gen);

    return;
}

/* Splice two gene randomly */
void cross(int P, int N, int genes[P][N], int *fits, int C, int v) {
    int g1 = genRand(0, P - 1);	                 /* First gene to splice */
    int g2 = genRand(0, P - 1);		             /* Second gene to splice */
    while (g1 == g2) {
        g2 = genRand(0, P - 1);
    }
    int spliceIdx = genRand(0, N - 2);           /* Splicing index */

    int gr = findMax(P, fits);	                 /* Worst individual */

    /* Splice worst gene with g1 and g2 */
    for (int i = 0; i <= spliceIdx; i++) {
        genes[gr][i] = genes[g1][i];             /* Copy genes from first */
    }
    for (int i = spliceIdx + 1; i < N; i++) {
        genes[gr][i] = genes[g2][i];             /* Copy genes from second */
    }

    fits[gr] = getFit(N, genes[gr], C);          /* Update fit of crossed individual */

    /* Print crossover data if verbose is enabled */
    if (v != 0) {
        printf("Crossover, %d + %d -> %d, splice at %d, new: ", g1, g2, gr, spliceIdx);
        printGene(N, genes[gr]);
        printf("\n");
    }

    return;
}

/* Mutate a gene randomly */
void mutate(int P, int N, int genes[P][N], int *fits, int C, int v) {
    int g1 = genRand(0,P - 1);	         /* Individual to mutate */
    int gIdx = genRand(0, N - 1); 	     /* Gene to replace*/
    int num = genRand(0,9);	 	         /* Value to flip gene to */
    int gm = findMax(P, fits);	         /* Individual to replace */

    /* Build mutated individual */
    for (int i = 0; i < N; i++) {
        if (i == gIdx) {
            genes[gm][gIdx] = num;       /* Set mutated gene */
        } else {
            genes[gm][i] = genes[g1][i]; /* Copy original genes */
        }
    }

    fits[gm] = getFit(N, genes[gm], C);  /* Update fitness value of mutated individual */

    /* If verbose, print mutation data */
    if (v != 0) {
        printf("Mutation, %d -> %d, changed gene %d to value %d, new: ", g1, gm, gIdx, num);
        printGene(N, genes[gm]);
        printf("\n");
    }

    return;
}
