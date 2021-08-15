/**
 * Sum square difference
 */

#include <stdio.h>
#define MAX 100

// Create a squaring function ^2
int square(int *arg) {
  int x = *arg;
  return x*x;
}

int main() {
  int sums, ssum, i;
  sums = ssum = 0;

  // Calculate sum of squares
  for(i = 1; i<=MAX; i++)
    sums += square(&i);

  // Calculate square of sums
  for(i = 1; i<=MAX; i++)
    ssum+=i;
  ssum = square(&ssum);

  // Display difference
  printf("The difference between sum of square and square of sums is\n: %d\n", ssum-sums);
}
