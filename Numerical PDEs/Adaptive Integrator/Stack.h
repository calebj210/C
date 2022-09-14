#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Data structure for stack
*/
typedef struct {
    int maxsize;   // max capacity of stack
    int top;
    double* items;
} Stack;

Stack*  newStack(int capacity);
void    freeStack();
int     size(Stack* pt);
int     isEmpty(Stack* pt);
int     isFull(Stack* pt);
void    push(Stack* pt, double x);
double  peek(Stack* pt);
double  pop(Stack* pt);

#endif
