/**
 * Efficient adaptive quadrature
 *
 * Author: Caleb Jacobs
 * Date last modified: 16-Sep-2022
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

double adaptQuad(double a, double b, double (*f)(double), int deg, int maxDepth, double tol) {
    GLNW nw;                        // Gauss-Legendre node and weight initialization
    initGLNW(&nw, deg);
    glNW(&nw);

    double left[maxDepth];  // Left endpoint array
    double right[maxDepth]; // Right endpoint array
    double s[maxDepth];     // Sub integral array

    left[0]  = a;
    right[0] = b;
    s[0]     = gaussQuad(a, b, f, nw);

    int j = 0;              // Depth counter
    double I = 0;           // Working integral estimate

    for (int i = 1; i < maxDepth; i++) {
        double c  = (left[j] + right[j]) / 2;
        double s1 = gaussQuad(left[j], c, f, nw);
        double s2 = gaussQuad(c, right[j], f, nw);

        if (fabs(s1 + s2 - s[j]) > tol) {
            left[j + 1]  = left[j];

            right[j + 1] = c;

            s[j + 1] = s1;

            left[j] = c;

            s[j] = s2;

            j++;
        } else {
            I += s1 + s2;
            printf("I = %10.16f\n", I);
            j--;
        }

        if (j < 0) {
            freeGLNW(&nw);
            return I;
        }
    }

    freeGLNW(&nw);

    return -210.0;
}
