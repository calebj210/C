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
    GLNW nw;                            // Gauss-Legendre node and weight initialization
    initGLNW(&nw, deg);
    glNW(&nw);

    Stack* left  = newStack(maxDepth);  // Left endpoint stack
    Stack* right = newStack(maxDepth);  // Right endpoint stack

    push(left,  a);                     // Add left endpoint
    push(right, b);                     // Add right endpoint
    


    freeGLNW(&nw);
    freeStack(left);
    freeStack(right);
}
