/**
 * Double array implementation of a stack
 *
 * Author: Caleb Jacobs
 * Date last modified: 14/09/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

/**
 * Initialize stack
 */
Stack* newStack(int capacity) {
    Stack* pt = (Stack*)malloc(sizeof(Stack));

    pt -> maxsize = capacity;
    pt -> top = -1;
    pt -> items = (double*)malloc(sizeof(double) * capacity);

    return pt;
}

/**
 * Free space up from stack 
 */
void freeStack(Stack* pt) {
    free(pt -> items);
    free(pt);
}

/**
 * Get size of stack 
 */
int size(Stack* pt) {
    return pt -> top + 1;
}

/**
 * Check if stack is empty or not
 */
int isEmpty(Stack* pt) {
    return pt -> top == -1;
}

/**
 * Check if stack is full
 */
int isFull(Stack* pt) {
    return pt -> top == pt -> maxsize - 1;
}

/**
 * Read the top element
 */
double peek(Stack* pt) {
    // Check if stack is empty
    if (isEmpty(pt)) {
        printf("Stack is empty!!!\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    return pt -> items[pt -> top];
}

/**
 * Add element to stack
 */
void push(Stack* pt, double x) {
    if (isFull(pt)) {
        printf("Stack is full!!!\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    pt -> items[++pt->top] = x;
}

/**
 * Remove and return top element from stack
 */
double pop(Stack* pt) {
    // Check if stack is empty
    if(isEmpty(pt)) {
        printf("Stack is empty!!!\nProgram Terminated\n");
        exit(EXIT_FAILURE);
    }

    return pt -> items[pt -> top--];
}
