/**
 * Even Fibonacci numbers
 */

#include <stdio.h>

int main(){
  int back,front,fib,sum;
  sum   = 0;
  back  = 0;
  front = 1;

  while(fib <= 4000000){
    fib   = front + back;
    back  = front;
    front = fib;

    if(fib % 2 == 0)
      sum += fib;
  }
  printf("The sum of even fibonacci sequence values is equal to: %d\n",sum);
}
    
    
