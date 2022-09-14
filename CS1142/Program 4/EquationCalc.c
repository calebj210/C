/**
 * Get and compute polynomials at a point.
 * 
 * Author: Caleb Jacobs
 * User ID: cajacobs
 * Date last modified: 02/09/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * Driver for computing polynomials at a point
 *
 * EquationCalc <x_value> <a_0> [a_1] ... [a_k]
 */
int main(int argc, char** argv) {
    /* Check required arguments */
    if (argc < 3) {
	printf("Usage: EquationCalc <x_value> <a_0> [a_1] ... [a_k]\n");
	return 0;
    }
    
    double x = atof(argv[1]);	     /* Get x value to evaluate polynomial */
    double xPow = 1.0;		     /* Initialize  power of x */
    double polSum = atof(argv[2]);   /* Intitialize polynomial sum to a_0 */
    double coeff;		     /* Declare a_i */
    
    /* Begin summing polynomial terms */
    for (int i = 3; i < argc; i++) {
	coeff = atof(argv[i]);
	xPow *= x;
	polSum += coeff*xPow;
    }
    
    /* Print final polynomial sum */
    printf("%0.2f\n", polSum);
}
