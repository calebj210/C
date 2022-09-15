/**
 * Test cases for my stack data structure
 *
 * Author: Caleb Jacobs
 * Date last modified: 14-09-2022
 */

#include <stdio.h>
#include "Stack.h"

int main() {
    Stack* stack = newStack(5);

    if (isFull(stack)) {
        printf("Stack is full\n");
    }
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
    }

    push(stack, 1.0);
    push(stack, 2.0);
    push(stack, 3.0);
    push(stack, 4.0);
    push(stack, 5.0);
    push(stack, 6.0);

    if (isFull(stack)) {
        printf("Stack is full\n");
    }

    for (int i = 1; i <= 5; i++) {
        printf("Stack has size %d\n", size(stack));
        printf("Stack peek has %f\n", peek(stack));
        printf("Pop yields %f\n", pop(stack));
    }

    if (isEmpty(stack)) {
        printf("Stack is empty\n");
    }
    pop(stack);
    peek(stack);

    freeStack(stack);

    return 0;
}
