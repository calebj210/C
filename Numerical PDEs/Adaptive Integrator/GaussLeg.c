/**
 * Routines for computing Gauss-Legendre quadrature nodes and weights
 *
 * Author: Caleb Jacobs
 * Date last modified: 14-Sep-2022
 */

#include "GaussLeg.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double Pi = 3.1415926535897932384626433832795028841971;

/**
 * Initialize GL nodes and weights storage
 *
 * N is the number degree of the Legendre polynomial used.
 */
void initGLNW(GLNW* nw, int N) {
    nw -> N = N;
    nw -> x = (double*)malloc(sizeof(double) * N);
    nw -> w = (double*)malloc(sizeof(double) * N);
}

void freeGLNW(GLNW* nw) {
    free(nw -> x);
    free(nw -> w);
}

/**
 * Generate coefficients of Legendre polynomials
 *
 * N is the degree of the Legendre polynomial
 */
void glCoef(int N, double coefs[N + 1][N + 1]) {
    memset(coefs, 0, (N + 1) * (N + 1) * sizeof(double));

    coefs[0][0] = coefs[1][1] = 1;      // Set base coefficients

    // Recursively generate the rest of the coefficients
    for (int n = 2; n <= N; n++) {
        coefs[n][0] = -(n - 1) * coefs[n - 2][0] / n;
        for (int i = 1; i <= n; i++) {
            coefs[n][i] = ((2 * n - 1) * coefs[n - 1][i - 1]
                             - (n - 1) * coefs[n - 2][i]) / n;
        }
    }
}

/**
 * Evaluate Legendre polynomial at a point x
 */
double glEval(int n, double x, int N, double c[N + 1][N + 1]) {
    double s = c[n][n];
    for (int i = n; i > 0; i--)
        s = s * x + c[n][i - 1];
    
    return s;
}

/**
 * Compute derivative of Legendre polynomial at a point x
 */
double glDiff(int n, double x, int N, double c[N + 1][N + 1]) {
    return n * (x * glEval(n, x, n, c) - glEval(n - 1, x, n, c)) / (x * x - 1);
}

/**
 * Generate nodes and weights for GL quadrature
 *
 * N is the degree of Legendre polynomial used
 */
void glNW(GLNW* nw) {
    int N = nw -> N;                                        // Degree of Legendre polynomial
    double x, x1;
    double c[N + 1][N + 1];                                 // Initialize coefficient matrix
    glCoef(N, c);

    for (int i = N / 2 + 1; i <= N; i++) {
        x = cos(Pi * (i - 0.25) / (N + 0.5));               // Initial root guess
        do {
            x1 = x;
            x -= glEval(N, x, N, c) / glDiff(N, x, N, c);   // Newton root finding iterate
        } while (fdim(x, x1) > 2e-16);

        nw -> x[i - 1] = x;                                 // Store root of polynomial

        x1 = glDiff(N, x, N, c);                            // Get derivative at root
        nw -> w[i - 1] = 2 / ((1 - x * x) * x1 * x1);       // Compute quad weight
    }
    
    for (int i = 0; i < N / 2; i++) {
        nw -> x[i] = -(nw -> x[N - i - 1]);
        nw -> w[i] =  (nw -> w[N - i - 1]);
    }
}
