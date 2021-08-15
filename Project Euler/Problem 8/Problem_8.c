/**
 * Program for finding the largest consecutive product given a list of numbers
 */

#include <stdio.h>

int main(int argc, char **argv) {
  // Initialize numbers array and file pointer
  int numbers[1000] = {0};
  FILE *list = fopen(argv[1],"r");

  // Begin reading list of numbers from file
  int i = 0;
  long int tmp;
  while (fscanf(list, "%1li", &tmp) != EOF) {
    if (tmp != '\n') {
      numbers[i] = tmp;
      i++;
    }
  }

  // Close file
  fclose(list);

  // Get the size of the product
  int sze = 0;
  printf("Enter the number of values to use in the product: ");
  scanf("%d", &sze);

  // Begin searching for the largest consecutive product
  long int prod;
  int idx = 0;
  long int max = 0;
  for (int i = 0; i < 1000-sze; i++) {
    prod = 1;
    for (int j = 0; j < sze; j++) {
      prod = prod*numbers[i+j];
    }

    if (prod > max) {
      max = prod;
      idx = i;
    }
  }

  printf("The largest consecutive product is %li with values: ", max);
  for (int i = 0; i < sze-1; i++) {
    printf("%d*", numbers[idx+i]);
  }
  printf("%d\n", numbers[idx+sze-1]);
  
  return 0;
}
