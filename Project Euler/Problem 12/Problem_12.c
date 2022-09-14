/**
 * Compute the first triangular number with more than a specified number of
 * divisors
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int countDivisors(int n) {
    int cnt = 0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i) {
                cnt++;
            } else {
                cnt += 2;
            }
        }
    }

    return cnt;
}

int firstAbove(int N) {
    int cur = 0;   // Current divisor count
    int tri = 0;   // First value to test

    int i = 1;
    while (cur <= N) {
        tri += i;

        cur = countDivisors(tri);
        i++;
    }
    
    return tri;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Problem_12 <divisor count>\n");
        return 0;
    }

    int N = atoi(argv[1]);      // Number of divisors

    int val = firstAbove(N);    // First number with more than N divisors

    printf("The first triangle number to have over %d divisors is %d which has %d divisors.\n",
            N, val, countDivisors(val));

    return 0;
}
