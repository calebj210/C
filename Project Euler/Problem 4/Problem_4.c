/**
 * Largest palindrome product
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

/**
 * Check if a number is a palindrome
 */
bool isPalindrome(int n) {
    int rev = 0;        // Reversed number
    int orig = n;       // Original number

    // Reverse the order of the number
    while (n > 0) {
        int r = n % 10;
        rev = rev * 10 + r;
        n /= 10;
    }

    return rev == orig;
}

/**
 * Brute force driver for checking each palindrome product
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Problem_4 <number size>\n");
        return 0;
    }

    int n = atoi(argv[1]);  // Size of n-digit number
    
    int left   = 0;     // Left number
    int right  = 0;     // Right number
    int curMax = 0;     // Current maximum palindrome

    int maxVal = round(pow(10, n) - 1);   // Max value of n-digit number
    int baseVal = round(pow(10, n - 1));  // Minimum value of n-digit number

    // Find the maximum palindrome
    for (int i = baseVal; i <= maxVal; i++) {
        for (int j = i; j <= maxVal; j++) {
            int prod = i * j;       // Next product to check
            
            // Check if product is candidate
            if (prod > curMax && isPalindrome(prod)) {
                left = i;
                right = j;
                curMax = prod;
            }
        }
    }

    printf("The largest palindrome product of two %d-digit numbers is: %d x %d = %d\n", n, left, right, curMax);

    return 0;
}
