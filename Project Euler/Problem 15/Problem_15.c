/**
 * Lattice paths computer
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Returns value of Binomial Coefficient C(n, k)
 */
unsigned long long int binom(int n, int k)
{
    unsigned long long int res = 1;
 
    // Since C(n, k) = C(n, n-k)
    if (k > n - k)
        k = n - k;
 
    // Calculate value of
    // [n * (n-1) *---* (n-k+1)] / [k * (k-1) *----* 1]
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
 
    return res;
}

/**
 * Driver for computing number of lattice paths
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Problem_15 <Grid_Size>\n");
        return 0;
    }

    int gSize = atoi(argv[1]);      // Grid size
    unsigned long long int numberOfLattice = binom(2 * gSize, gSize);

    printf("Number of lattice paths of a %dx%d grid is: %llu\n", gSize, gSize, numberOfLattice);

    return 0;
}
