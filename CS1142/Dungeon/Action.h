// Header file for the Action data type
// DO NOT MODIFY!

#ifndef ACTION_H
#define ACTION_H

typedef enum {ActionInvalid, ActionNorth, ActionSouth, ActionEast, ActionWest, ActionQuit} Action;

Action actionFromChar(char ch);
const char* actionToString(Action a);

#endif


