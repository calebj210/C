/**
 * Smallest multiple
 */

#include <stdio.h>

int main() {
  int test,i,j,range;
  range = 20;
  j = test = 0;
  while (test != 1) {
    j++;
    for (i = 1; i <= range; i++)
      if (j % i != 0) {
	break;
      } else if (i == range)
	test = 1;
  }
  printf("The smallest positive integer divisble by 1 to 20 is: %d\n", j);
}
