/**
 * Multiples of 3 and 5
 */

#include <stdio.h>

int main() {
  int i,sum;
  sum = 0;
  
  for(i = 1; i<1000; i++)
    if(i%5==0||i%3==0)
      sum+=i;
  printf("The Sum equals: %d\n",sum);
}
