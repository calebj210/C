/**
 * Test adaptive quadrature
 *
 * Author: Caleb Jacobs
 * Date last modified 16-Sep-2022
 */

#include <stdio.h>
#include <math.h>
#include "Quad.h"
#include "GaussLeg.h"

double f(double x) {
    return log(x) * log(x);
}

int main(int argc, char** argv) {
    int N;
    if (argc == 1) {
        N = 50;
    } else {
        N = atoi(argv[1]);
    }

//     GLNW nw;
//     initGLNW(&nw, N);
//     glNW(&nw);
// 
//     double sum1 = gaussQuad(-2.31, -1.015, exp, nw);
//     printf("Gauss Quad = %10.15f\n", sum1);
//     printf("    Actual = %10.15f\n", exp(-1.015) - exp(-2.31));

    double sum2 = adaptQuad(0, 3, f, 10, N, 2e-16);
    printf("Adaptive Quad = %10.15f\n", sum2);
    printf("       Actual = %10.15f\n", 3 * (f(3) - 2 * log(3) + 2));

//     freeGLNW(&nw);

    return 0;
}
