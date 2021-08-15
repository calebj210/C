/**
 * Read and manage the map and everything inside of it
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/08/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

/**
 * Initialize and populate the dungeon's map
 */
bool mapInit(Map *map, const char *filename) {
    FILE *mapFile = fopen(filename, "r");   // Access map file

    // Check if file opened properly
    if (mapFile == NULL) {
        return false;
    }

    // Load map size
    fscanf(mapFile, "%d %d", &map -> rows, &map -> cols);

    // Load avatars intial position
    fscanf(mapFile, "%d %d", &map -> avatarRow, &map -> avatarCol);
    
    // Allocate space for a 2D array of map tiles
    map -> tiles = malloc(sizeof(Tile*) * (map -> rows));
    for (int i = 0; i < (map -> rows); i++) {
        map -> tiles[i] = malloc(sizeof(Tile) * (map -> cols));
    }

    // Read map file into tile array
    for (int i = 0; i < (map -> rows); i++) {
        for (int j = 0; j < (map -> cols); j++) {
            char ch;                        // Current character
            fscanf(mapFile, " %c", &ch);    // Read next non whitespace character
            
            // Parse character to tile
            map -> tiles[i][j] = tileFromChar(ch);
        }
    }

    fclose(mapFile);

    return true;
}

/**
 * Clean memory of the map
 */
void mapUninit(Map *map) {
    for (int i = 0; i < (map -> rows); i++) {
        free(map -> tiles[i]);          // Free row of tiles
        map -> tiles[i] = NULL;         // Safeguard row
    }

    free(map -> tiles);                 // Free columns
    map -> tiles = NULL;                // Saveguard columns
}

/**
 * Print the current map
 */
void mapDisplay(const Map *map) {
    // Loop through each map entry and print the tile character
    for (int i = 0; i < (map -> rows); i++) {
        for (int j = 0; j < (map -> cols); j++) {
            // Check if avatar is on the current tile
            if (map -> avatarRow == i && map -> avatarCol == j) {
                putchar('@');                       // Display avatar
            } else {
                tileDisplay(map -> tiles[i][j]);    // Display map tile
            }
        }

        putchar('\n');  // Move to next line
    }
}

/**
 * Attempt to move the avatar in the map
 */
bool mapMoveAvatar(Map *map, Avatar *avatar, Action action) {
    int x = map -> avatarCol;       // Column position of moved avatar
    int y = map -> avatarRow;       // Row position of moved avatar

    // Get new position of moved avatar
    switch (action) {
        case ActionSouth:
            y++;
            break;
        case ActionNorth:
            y--;
            break;
        case ActionWest:
            x--;
            break;
        case ActionEast:
            x++;
            break;
        default:
            return false;
    }

    // Check map bounds of player
    if (x < 0 || x >= (map -> cols) || 
        y < 0 || y >= (map -> rows)) {
        return false;
    }

    // Check if player is on a passable tile
    if (!tilePassable(map -> tiles[y][x])) {
        // Encountered a locked door, do we have keys to move through it
        if (map -> tiles[y][x] == TileLockedDoor && avatar -> keys > 0) {
            avatar -> keys--;               // Use key to unlock the door
            map -> avatarCol = x;           // Set avatar's column position
            map -> avatarRow = y;           // Set avatar's row position
            map -> tiles[y][x] = TileDoor;  // Unlock the door

            return true;
        }

        return false;
    }
    
    // Handle passable tiles
    switch (map -> tiles[y][x]) {
        case TileEmpty: 
        case TileDoor:
        case TileSecretPassage:
            break;
        case TileGem:
            avatar -> gems++;
            map -> tiles[y][x] = TileEmpty;
            break;
        case TileKey:
            avatar -> keys++;
            map -> tiles[y][x] = TileEmpty;
        default:
            break;
    }

    map -> avatarCol = x;           // Set avatar's column position
    map -> avatarRow = y;           // Set avatar's row position
    return true;
}

/**
 * Count the number of gems left in the map
 */
int mapGemsRemaining(const Map *map) {
    int gemCount = 0;           // Current gem count

    // Scan each tile
    for (int i = 0; i < map -> rows; i++) {
        for (int j = 0; j < map -> cols; j++) {
            // Check if current tile is a gem
            if (map -> tiles[i][j] == TileGem) {
                gemCount++;     // Increase gem count
            }
        }
    }

    return gemCount;
}
