/**
 * Test cases for Gauss-Legendre nodes and weights
 *
 * Author: Caleb Jacobs
 * Date last modified: 14-09-2022
 */

#include <stdio.h>
#include "GaussLeg.h"

int main() {
    GLNW nw;
    for (int N = 1; N <= 10; N++) {
        initGLNW(&nw, N);
        glNW(&nw);

        printf("With N = %d, our nodes and weights are\n\tx = [", N);
        for (int i = 0; i < N; i++) {
            printf(" %g ", nw.x[i]);
        }
        printf("]\n\tw = [");
        for (int i = 0; i < N; i++) {
            printf(" %g ", nw.w[i]);
        }
        printf("]\n\n");

        freeGLNW(&nw);
    }

    return 0;
}
