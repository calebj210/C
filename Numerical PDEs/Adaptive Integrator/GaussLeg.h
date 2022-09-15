#ifndef GAUSSLEG_H
#define GAUSSLEG_H

#include <stdlib.h>
#include <math.h>

extern double Pi;

typedef struct {
    int N;
    double* x;
    double* w;
} GLNW;

void     initGLNW(GLNW* nw, int N);
void     freeGLNW(GLNW* nw);
void     glNW(GLNW* nw);

#endif
