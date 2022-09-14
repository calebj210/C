/*
 * The following program takes a single command line argument
 * that is a positive integer. Fill in the missing lines of
 * code so the program prints out the Collatz sequence
 * including the total steps taken. Recall the rules are:
 * If N = 1 stop
 * If N is even, divide by 2
 * If N is odd, multiply by 3 and add 1
 *
 * Example output:
 * % ./Collatz 10
 * 5 16 8 4 2 1 (6 steps)
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    long num = atol(argv[1]);
    int steps = 0;

    while (num > 1) {
        if (num % 2 == 0) {
            num = num / 2;
        }
        else {
            num = 3 * num + 1;
        }
        printf("Step = %4d, # = %5ld\n", steps, num);
        steps++;
    }
    printf("(%d steps)\n", steps);
    return 0;
}

