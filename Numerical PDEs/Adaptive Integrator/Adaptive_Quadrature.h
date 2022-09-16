#ifndef ADAPTIVE_QUADRATURE_H
#define ADAPTIVE_QUADRATURE_H

#include "GaussLeg.h"
#include "Stack.h"

extern const GLNW NW;

double gaussQuad(double a, double b, double (*f)(double));
double adaptQuad(double a, double b, double (*f)(double), int maxDepth);

#endif
