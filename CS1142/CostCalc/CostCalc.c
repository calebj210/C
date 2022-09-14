#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
  if (argc < 4) {
    printf("CostCalc <product> <qty> <price> \n");
    return 0;
  }
  
  char* product = argv[1];
  int quantity = atoi(argv[2]);
  double cost = atof(argv[3]);
  double total = quantity * cost;

  printf("To buy %d ", quantity);
  printf("%s, ", product);
  printf("you need exactly $%.2f, ", total);
  printf("or about $%d\n", (int) round(total));
  return 0;
}
