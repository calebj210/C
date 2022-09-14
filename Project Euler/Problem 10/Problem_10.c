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
long int nthPrimeSum(long int n) {
  // Handle the first 2 prime number cases
  switch (n) {
  case 1 :
    return 2;
  case 2 :
    return 5;
  }

  // initialize prime counter
  long int sum = 5;

  // initialize prime canditate
  int i = 5;
    
  // Handle the prime numbers of the form 6k+-1
  while (i < n) {
    // Check 6k-1
    if (isPrime(i) == 1)
      sum = sum + i;

    // Check if 6k+1 is prime
    i = i+2;
    if (isPrime(i) == 1 && i < n)
      sum = sum +i;

    // Move to next possible prime candidate 6k-1
    i = i+4;
  }

  return sum;
}

// Interface for computing the nth prime
int main() {
  // Initialize n
  long int n = 1;
  
  printf("What primes do you want to sum up to? ");
  scanf("%li", &n);

  // Start timer
  clock_t t;
  t = clock();
  
  // compute nth prime
  long int N = nthPrimeSum(n);

  // End timer
  t = clock() - t;
  
  // Display nth prime sum
  printf("The prime sum up to %li is: %li.\n", n, N);

  // Display time needed for computation
  printf("Time taken is: %f.\n", ((double)t)/CLOCKS_PER_SEC);
  
  return 0;
}
