/**
 * Efficient adaptive quadrature
 *
 * Author: Caleb Jacobs
 * Date last modified: 17-Sep-2022
 */

#include "Quad.h"
#include "GaussLeg.h"
#include "Stack.h"
#include <stdlib.h>

const GLNW NW;

double gaussQuad(double a, double b, double (*f)(double), GLNW nw) {
    double sum = 0;             // Quadrature sum
    double c1 = (b - a) / 2;    // Transformation coefficient 1
    double c2 = (b + a) / 2;    // Transformation coefficient 2

    // Add up quadrature weights
    for (int i = 0; i < nw.N; i++){
        sum += nw.w[i] * f(c1 * nw.x[i] + c2);
    }

    return c1 * sum;
}

double adaptQuad(double a, double b, double (*f)(double), int deg, int maxIntervals, double tol) {
    GLNW nw;                    // Gauss-Legendre node and weight initialization
    initGLNW(&nw, deg);
    glNW(&nw);

    double left[maxIntervals];  // Left endpoint array
    double right[maxIntervals]; // Right endpoint array
    double s[maxIntervals];     // Sub integral array

    left[0]  = a;
    right[0] = b;
    s[0]     = gaussQuad(a, b, f, nw);

    int i;
    int j = 0;                  // Current depth counter
    double I = 0;               // Working integral estimate

    for (i = 1; i < maxIntervals; i++) {
        double c  = (left[j] + right[j]) / 2;       // Middle of interval
        double s1 = gaussQuad(left[j], c,  f, nw);  // Integral of left interval
        double s2 = gaussQuad(c, right[j], f, nw);  // Integral of right interval
        double diff = fabs(s1 + s2 - s[j]);         // Sub-integral difference

        // Construct integral via interval refinement
        if (diff > tol || isnan(diff)) {
            left[j + 1]  = left[j];

            right[j + 1] = c;

            s[j + 1] = s1;

            left[j] = c;

            s[j] = s2;

            j++;
        } else {
            I += s1 + s2;
            j--;
        }

        if (j < 0) {
            printf("Converged: subintervals used = %d\n", 2 * i);

            freeGLNW(&nw);
            return I;
        }
    }

    freeGLNW(&nw);

    printf("Failed to converge subintervals used = %d\n", 2 * i);

    return 0.0;
}
