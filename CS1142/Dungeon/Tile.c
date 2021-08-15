/**
 * Handle tile data of a map
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/07/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include "Tile.h"

/**
 * Map a tile character to a tile
 */
Tile tileFromChar(char ch) {
    switch (ch) {
        case 't': return TileInvalid;
        case '.': return TileEmpty;
        case '#': return TileWall;
        case '-': return TileDoor;
        case '=': return TileLockedDoor;
        case 'S': return TileSecretPassage;
        case '*': return TileGem;
        case '+': return TileKey;
        default:  return TileInvalid;
    }
}

/**
 * Display a given tile
 */
void tileDisplay(Tile tile) {
    switch (tile) {
        case TileInvalid:
            return;
        case TileEmpty:
            putchar(' ');
            return;
        case TileWall:
            putchar('#');
            return;
        case TileDoor:
            putchar('-');
            return;
        case TileLockedDoor:
            putchar('=');
            return;
        case TileSecretPassage:
            putchar('#');
            return;
        case TileGem:
            putchar('*');
            return;
        case TileKey:
            putchar('+');
            return;
    }
}

/**
 * Check whether a tile is passable by the player
 */
bool tilePassable(Tile tile) {
    switch (tile) {
        case TileInvalid:
        case TileWall:
        case TileLockedDoor:
            return false;
        case TileEmpty:
        case TileDoor:
        case TileSecretPassage:
        case TileGem:
        case TileKey:
            return true;
    }

    return false;
}
