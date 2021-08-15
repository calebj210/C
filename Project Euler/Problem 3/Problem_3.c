/**
 * Routine for finding the largest prime factor of a number
 */

#include <stdio.h>
#include <math.h>

// Largest prime factor function
long int largestPrime(long int n) {
  // Initialize largest factor
  long int N = 1;
  
  // Remove factors of 2
  if (n % 2 == 0) {
    N = 2;
    while (n%2 == 0) {
      n = n/2;
    }
  }

  // Find odd factors up to sqrt(n)
  for (long int i = 3; i <= sqrt(n); i = i+2) {
    // Factor out i from n
    if (n%i == 0) {
      N = i;
      while (n%i == 0) {
	n = n/i;
      }
    }
  }

  // Return n if n is a prime greater than 2
  if (n > 2)
    N = n;
  
  return N;
}

// Driver and interface for largest prime
int main() {
  // Initialize number to be factored and the factor
  long int n, N;

  // Prompt input
  printf("Please enter an integer: ");

  // Store input in n
  scanf("%li", &n);

  // Compute the largest prime factor of n
  N = largestPrime(n);

  // Display largest prime factor of n
  printf("The largest prime factor of %li is %li\n", n, N);
  
  return 0;
}
