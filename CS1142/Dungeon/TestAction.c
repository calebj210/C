// Test program for the Action data type

#include "Action.h"
#include <stdio.h>

int main(void)
{
    // Test an invalid character, all the directions, and the quit command
    char chars[] = {'t', 'w', 's', 'a', 'd', 'q'};    
    for (int i = 0; i < 6; i++)
    {
        printf("'%c' -> %d\n", chars[i], actionFromChar(chars[i]));
    }
    printf("\n");
    
    Action actions[] = {ActionInvalid, ActionNorth, ActionSouth, ActionEast, ActionWest, ActionQuit};
    for (int i = 0; i < 6; i++)
    {
        printf("%d -> %s\n", i, actionToString(actions[i]));
    }
    
    return 0;
}
