/* Programming activity: functions
 *
 * Simulates the rolling of two dice.
 * Computes the average number of rolls to get 2, 3, ..., 12
 * Create three functions and change the main function to use them.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Draw a random integer uniformly in [start, end]
// Return the random integer.
int getRandomInt(int start, int end) {
    return rand() % (end - start + 1) + start;
}

// Set all the elements of a 1D array to 0
void initArray(int size, int *a) {
    for (int i = 0; i < size; i++) {
	a[i] = 0;
    }
}

// Simulate the rolling of two 6-sided dice.
// Returns the number of rolls required to get a target value. 
int countDiceRolls(int target) {
    int count = 0;		/* Number of rolls before success */
    int roll = 0;		/* Current roll */
    
    // Handle impossible rolls 
    if (target < 2 || target > 12) {
	return -1;
    }

    /* Roll until success */
    while (roll != target) {
	int r1 = getRandomInt(1, 6); /* First die roll */
	int r2 = getRandomInt(1, 6); /* Second die roll */

	roll = r1 + r2;
	count++;
    }

    return count;
}

int main(int argc, char** argv) {
    if (argc < 2) {
	printf("DiceAvg <rolls to simulate>\n");
	return 0;
    }
    
    const int SIM_STEPS = atoi(argv[1]);
    srand(time(NULL));
    
    /* Over sized arrays for storing roll data */
    int sumRolls[13];
    int attempts[13];
    initArray(13, sumRolls);
    initArray(13, attempts);
    
    for (int step = 0; step < SIM_STEPS; step++) {
       	// Choose a random target value in [2, 12]
	int target = getRandomInt(2, 12);
	
	// Keep rolling until the sum of the two dice equals our target
	sumRolls[target] += countDiceRolls(target);
	attempts[target]++;
    }
    
    for (int i = 2; i <= 12; i++) {
	printf("sum %d, avg rolls %.2f\n", i, (double) sumRolls[i] / attempts[i]);
    }
}
