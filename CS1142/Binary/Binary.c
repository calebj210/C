/**
 * Programming activity: Binary print out
 *
 * This program takes a single unsigned integer in [0, 255] as input.
 * It prints out the 8-bit binary representation of the integer.
 *
 * Example:
 * % gcc -std=c99 -pedantic -Wall -Wextra Binary.c -o Binary
 * % ./Binary 42
 * % 00101010
 *
 * BONUS LEVEL: change to convert an unsigned short to binary
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char** argv) {
    unsigned char remaining = atoi(argv[1]);
    unsigned char divisor = (UCHAR_MAX + 1) / 2;  // (255 + 1) / 2 = 128

    while (divisor > 0) {
        if (remaining >= divisor) {
            printf("1");
            remaining -= divisor;
        } else {
            printf("0");
        }
        divisor /= 2;
    }
    printf("\n");
}
