/**
 * Longest Collatz Sequence Finder
 */

#include <stdio.h>

// Function for computing the next value in the sequence
long int next(long int n) {
  // Compute next value
  if (n%2 == 0) {
    return n/2;
  } else {
    return 3*n+1;
  }
}

//
int main() {
  // Initialize needed variables
  long int n, max;
  int length;
  long int maxStart = 1;
  int maxLength = 0;
  
  // Get upper bound for starting point
  printf("Please enter an upper starting point bound: ");
  scanf("%li", &max);

  // Begin computing the longest length
  for (long int i = 1; i < max; i++) {
    // Set n to the start
    n = i;

    // Reset length to 0
    length = 0;

    // Begin following the Collatz sequence
    while (n != 1){
      n = next(n);
      length++;
    }

    // Check and store max length and start
    if (length > maxLength) {
      maxStart = i;
      maxLength = length;
    }
  }

  printf("The largest Collatz sequence with a start under %li begins at %li and has a length %d.\n", max, maxStart, maxLength);

  return 0;
}
