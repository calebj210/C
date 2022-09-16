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

int main(int argc, char** argv) {
    int N;
    if (argc == 1) {
        N = 5;
    } else {
        N = atoi(argv[1]);
    }

    GLNW nw;
    initGLNW(&nw, N);
    glNW(&nw);

    double sum = gaussQuad(-3, 3, exp, nw);
    printf("Gauss Quad = %10.15f\n", sum);
    printf("    Actual = %10.15f\n", exp(3) - exp(-3));

    freeGLNW(&nw);

    return 0;
}
