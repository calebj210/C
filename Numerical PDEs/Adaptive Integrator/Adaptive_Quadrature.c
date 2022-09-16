/**
 * Efficient adaptive quadrature
 *
 * Author: Caleb Jacobs
 * Date last modified: 16-Sep-2022
 */

#include "GaussLeg.h"
#include "Stack.h"
#include <stdlib.h>

const GLNW NW;

double gaussQuad(double a, double b, double (*f)(double)) {
    double s = 0;   // Quadrature sum

    // Add up quadrature weights
    for (int i = 0; i < NW.N; i++){
        s += NW.w[i] * (b - a) * f((NW.x[i] * (b - a) + b + a) / 2) / 2;
    }

    return s
}

double adaptQuad(double a, double b, double (*f)(double), int maxDepth, double tol) {
    Stack* left  = initStack(maxDepth); // Left endpoint stack
    Stack* right = iniStack(maxDepth);  // Right endpoint stack

    push(left,  a);                     // Add left endpoint
    push(right, b);                     // Add right endpoint


    freeStack(left);
    freeStack(right);
}
