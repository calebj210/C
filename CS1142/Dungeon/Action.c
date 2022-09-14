/**
 * Read and decode actions
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/07/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include "Action.h"

/**
 * Read a given action
 */
Action actionFromChar(char ch) {
    switch (ch) {
        case 'w': 
            return ActionNorth;
        case 'a':
            return ActionWest;
        case 's':
            return ActionSouth;
        case 'd':
            return ActionEast;
        case 'q':
            return ActionQuit;
        default:
            return ActionInvalid;
    }
}

/**
 * Put an action into a standard word
 */
const char *actionToString(Action a) {
    switch (a) {
        case ActionInvalid:
            return "invalid";
        case ActionNorth:
            return "north";
        case ActionSouth:
            return "south";
        case ActionEast:
            return "east";
        case ActionWest:
            return "west";
        case ActionQuit:
            return "quit";
        default:
            return NULL;
    }
}
