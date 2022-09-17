#ifndef QUAD_H
#define QUAD_H

#include "GaussLeg.h"
#include "Stack.h"

double gaussQuad(double a, double b, double (*f)(double), GLNW nw);
double adaptQuad(double a, double b, double (*f)(double), int deg, int maxIntervals, double tol);

#endif
