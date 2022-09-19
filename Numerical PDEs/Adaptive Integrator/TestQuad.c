/**
 * Test adaptive quadrature
 *
 * Author: Caleb Jacobs
 * Date last modified 17-Sep-2022
 */

#include <stdio.h>
#include <math.h>
#include "Quad.h"
#include "GaussLeg.h"

double sign(double x) {
    return (x >= 0) ? 1.0 : -1.0;
}

double f1(double x) {
    return 1;
}

double f2(double x) {
    return x;
}

double f3(double x) {
    return x * x;
}

double f4(double x) {
    return sqrt(x) * pow(sin(x), 2);
}

double f5(double x) {
    double pi = 4.0 * atan(1.0);

    double y = sin(2 * pi * x);

    return sign(y) * pow(fabs(y), 1.0 / 1001); 
}

double f6(double x) {
    double pi = 4.0 * atan(1.0);

    return exp(-x * x) * 2 / sqrt(pi);
}

double f7(double x) {
    return pow(fabs(1 - x), -0.5);
}

double f8(double x) {
    return pow(fabs(x), -0.5);
}

double f9(double x) {
    return log(x);
}

double f10(double x) {
    return log(x) * log(x);
}

int main(int argc, char** argv) {
    int deg = 5;
    if (argc > 1) {
        deg = atoi(argv[1]);
    }

    int maxIntervals = 1000;
    if (argc > 2) {
        maxIntervals = atoi(argv[2]);
    }

    double tol = 1e-14;
    if (argc > 3) {
        tol = atof(argv[3]);
    }

    // 1 test
    printf("1 for x in (0, 100)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 100, f1, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 100.0);
    
    // x test
    printf("x for x in (-5, 5)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(-5, 5, f2, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 0.0);

    // x^2 test
    printf("x^2 for x in (-5, 5)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(-5, 5, f3, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 250.0 / 3);

    // sqrt(x)Sin^2(x) test
    printf("sqrt(x)sin^2(x) for x in (0, 1)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 1, f4, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 0.2307119405425906);

    // sin^(1/1001)(2pi x) test
    printf("sin^(1/1001)(2pi x) for x in (0, 0.5)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 0.5, f5, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 0.499654097397356);

    // 2/sqrt(pi) e^(-x^2) test
    printf("2/sqrt(pi) e^(-x^2) for x in (0, inf)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 10, f6, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 1.0);

    // |1 - x|^-(1/2) test
    printf("|1 - x|^-(1/2) for x in (0, 2), tol = 1e-9\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 2, f7, deg, maxIntervals, 1e-9));
    printf("\tActual = %10.15f\n\n", 4.0);
    //
    // Rescaled |1 - x|^-(1/2) test
    printf("Rescaled |1 - x|^-(1/2) for x in (0, 2)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(-1e5, 1e5, f8, deg, maxIntervals, tol) * pow(1e5, -0.5));
    printf("\tActual = %10.15f\n\n", 4.0);

    // Log(x) test
    printf("log(x) for x in (0, 3)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 3, f9, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 3 * log(3) - 3);

    // Log^2(x) test
    printf("log^2(x) for x in (0, 3)\n");
    printf("\t  Quad = %10.15f\n", adaptQuad(0, 3, f10, deg, maxIntervals, tol));
    printf("\tActual = %10.15f\n\n", 3 * (f10(3) - 2 * log(3) + 2));

    return 0;
}
