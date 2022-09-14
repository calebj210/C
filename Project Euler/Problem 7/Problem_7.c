/**
 * Routine for computing the nth prime
 */

#include <stdio.h>
#include <math.h>
#include <time.h>

// Function for testing primality of a number
int isPrime(long int n) {
  // Rule out numbers under 2
  if (n < 2)
    return 0;

  // Test for 2 and 3 divisors
  if (n%2 == 0 || n%3 == 0) {
    if (n == 2 || n == 3) {
      return 1;
    } else {
      return 0;
    }
  }

  // Store sqrt(n)
  long int sqrtn = sqrt(n);
  
  // Test all numbers of the form 6k+1 up to sqrt(n)
  for(long int i = 5; i <= sqrtn; i = i+6) {
    if (n%i == 0 || n%(i+2) == 0)
      return 0;
  }

  // n is prime
  return 1;
}

// Function for computing the nth prime
long int nthPrime(long int n) {
  // Handle the first 2 prime number cases
  switch (n) {
  case 1 :
    return 2;
  case 2 :
    return 3;
  }

  // initialize prime counter
  int count = 2;

  // initialize prime canditate
  int i = 5;
    
  // Handle the prime numbers of the form 6k+-1
  while (1) {
    // Check 6k-1
    if (isPrime(i) == 1)
      count++;

    // Check if we have the nth prime yet
    if (count == n)
      return i;

    // Check if 6k+1 is prime
    i = i+2;
    if (isPrime(i) == 1)
      count++;

    // Check if we have the nth prime yet
    if (count == n)
      return i;

    // Move to next possible prime candidate 6k-1
    i = i+4;
  }

  return i;
}

// Interface for computing the nth prime
int main() {
  // Initialize n
  int n = 1;
  
  printf("What prime do you want to compute? ");
  scanf("%d", &n);

  // Start timer
  clock_t t;
  t = clock();
  
  // compute nth prime
  long int N = nthPrime(n);

  // End timer
  t = clock() - t;
  
  // Display nth prime
  printf("The %dth prime is: %li.\n", n, N);

  // Display time needed for computation
  printf("Time taken is: %f.\n", ((double)t)/CLOCKS_PER_SEC);
  
  return 0;
}
