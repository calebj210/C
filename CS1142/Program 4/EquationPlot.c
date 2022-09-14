/**
 * Get, print, and plot polynomials from user.
 * 
 * Author: Caleb Jacobs
 * User ID: cajacobs
 * Date last modified: 02/09/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * Given an array of polynomial coefficients, print the polynomial equation
 *
 * a: array of polynomial coefficients
 * size: number of polynomial terms
 */
int printPol(double* a, int size) {
    printf("y = %0.2f", a[0]);	          /* Print first term in polynomial */

    /* Print the rest of the terms */
    for (int i = 1; i < size; i++) {
	printf(" + %0.2fx^%d", a[i], i);
    }
    printf("\n");
    
    return 0;
}

/**
 * Evaluate polynomial at a point
 *
 * x: x value to evaluate p(x)
 * a: array of polynomial coefficients
 * size: number of polynomial terms
 */
double sumPolTerms(double x, double* a, int size) {
    double xPow = 1.0;		     /* Initialize  power of x */
    double polSum = a[0];            /* Intitialize polynomial sum to a_0 */
    double coeff;		     /* Declare polynomial coefficent a_i */
    
    /* Begin summing polynomial terms */
    for (int i = 1; i < size; i++) {
	coeff = a[i];
	xPow *= x;
	polSum += coeff * xPow;
    }
    
    return polSum;
}

/**
 * Plot polynomial over a specified range
 *
 * x_range: range of x given by [-x_range, x_range]
 * y_range: range of y given by [-y_range, y_range]
 * a: array of polynomial coefficients
 * size: number of polynomial terms
 */
int plotPol(int x_range, int y_range, double* a, int size) {
    int p[2 * x_range + 1];	/* Declare polynomial evalution array */

    /* Compute and round polynomial at each point in x_range */
    for (int x = -x_range; x <= x_range; x++) {
        p[x + x_range] = (int)round(sumPolTerms(x, a, size));
    }

    /* Plot graph window and function */
    for (int y = y_range; y >= -y_range; y--) {
	for (int x = 0; x <= 2 * x_range; x++) {
	    if (p[x] == y) {
		printf("o");
	    } else if (x == x_range && y == 0) {
		printf("+");
	    } else if (x == x_range) {
		printf("|");
	    } else if (y == 0) {
		printf("-");
	    } else {
		printf(" ");
	    }
	}
	printf("\n");
    }
    
    return 0;
}

/**
 * Driver function for getting and plotting polynomials
 *
 * EquationPlot <x_range> <y_range> <a_0> [a_1] ... [a_k]
 */
int main(int argc, char** argv) {
    /* Check required arguments */
    if (argc < 4)
	{
	    printf("Usage: EquationPlot <x_range> <y_range> <a_0> [a_1] ... [a_k]\n");
	    return 0;
	}

    int size = argc - 3;	        /* Number of polynomial terms */
    double a[size];		        /* Declare an array of coefficients */
    for (int i = 0; i < size; i++) {
        a[i] = atof(argv[i + 3]);       /* Initialize array of coefficients */
    }

    printPol(a, size);		        /* Print polynomial */

    int x_range = atoi(argv[1]);        /* Get x_range */
    int y_range = atoi(argv[2]);        /* Get y_range */

    plotPol(x_range, y_range, a, size); /* Plot the polynomial */

    return 0;
}
