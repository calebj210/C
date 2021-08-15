/**
 * Create and manage move history by the player
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/07/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "History.h"

/**
 * Initialize History
 */
void historyInit(History *history) {
    history -> first = calloc(1, sizeof(Node)); // Make first node in history
}

/**
 * Add new event to the history
 */
void historyAdd(History *history, Action action) {
    Node *newEvent = calloc(1, sizeof(Node)); // Initialize new event
    newEvent -> action = action;              // Set action of new event

    Node *tmp = history -> first;             // Traversal node
    while (tmp -> next != NULL) {
        tmp = tmp -> next;                    // Move to next node
    }

    tmp -> next = newEvent;                   // Store new event
}

/**
 * Print full history of actions
 */
void historyPrint(const History *history) {
    Node *tmp = history -> first; // Setup traversal node

    while (tmp -> next != NULL) {
        tmp = tmp -> next;        // Move to next point in history
        printf("%s ", actionToString(tmp -> action));
    }

    putchar('\n');                // Move to next line
}

/**
 * Clean memory of history
 */
void historyUninit(History *history) {
    Node *cur = history -> first;   // Get first point in history

    while (cur -> next != NULL) {
        Node *next = cur -> next;   // Store next point in history

        free(cur);                  // Free current history
        cur = next;                 // Assign next point in history
    }

    free(cur);                      // Free last point in history
}
