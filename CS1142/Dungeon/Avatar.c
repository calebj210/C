/**
 * Get and store information about the avatar
 *
 * Author: Caleb Jacobs (cajacobs)
 * Date Last Modified: 04/07/2021
 * Course: CS1141 Spring 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Avatar.h"

/**
 * Create avatar and store name
 */
void avatarInit(Avatar *avatar, const char* name) {
    // Allocate and copy name to avatar
    avatar -> name = calloc(strlen(name) + 1, sizeof(char));
    strcpy(avatar -> name, name);

    avatar -> gems = 0; // Set gem count to zero
    avatar -> keys = 0; // Set key count to zero
}

/**
 * Clean memory of avatar
 */
void avatarUninit(Avatar *avatar) {
    free(avatar -> name);   // Free avatar's name
}

/**
 * Attempt to use key to open door
 */
bool avatarUseKey(Avatar *avatar) {
    // Check if avatar can use an keys
    if (avatar -> keys > 0) {
        avatar -> keys--;
        return true;
    } else {
        return false;
    }
}

/**
 * Add a key to avatars inventory
 */
void avatarAddKey(Avatar *avatar) {
    avatar -> keys++;   // Increase avatar's key count
}

/**
 * Add a gem to avatars inventory
 */
void avatarAddGem(Avatar *avatar) {
    avatar -> gems++;   // Increase avatar's gem count
}

/**
 * Print avatar's information
 */
void avatarDisplay(const Avatar *avatar) {
    printf("%s's inventory: gems %d, keys %d\n", avatar -> name, avatar -> gems, avatar -> keys);
}
