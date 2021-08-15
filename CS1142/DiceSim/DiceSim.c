/* Programming activity: Arrays and randomness
 *
 * This program simulates rolling one or more 6-sided dice.
 * The dice are added together and we keep track of how often
 * different sums were generated over a set of trials.
 * After all trials, the probability of each sum is displayed.
 *
 * Command line input:
 *   First argument: the number of dice to be rolled
 *   Second argument: the number of trials
 *
 * Example output:
 * % ./DiceSim 2 1000000
 * P(sum =    2) = 0.028030
 * P(sum =    3) = 0.055525
 * P(sum =    4) = 0.082905
 * P(sum =    5) = 0.111132
 * P(sum =    6) = 0.138408
 * P(sum =    7) = 0.166776
 * P(sum =    8) = 0.139183
 * P(sum =    9) = 0.111272
 * P(sum =   10) = 0.083192
 * P(sum =   11) = 0.055607
 * P(sum =   12) = 0.027970
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
   // Make sure we have at least two command line arguments
   if (argc < 3)
   {
      printf("DiceSim <number of dice> <number of trials>\n");
      return 0;
   }

   // Seed the random number generator based on the time
   srand(time(NULL));

   // Parse the command line input
   const int NUM_DICE = atoi(argv[1]);
   const int NUM_TRIALS = atoi(argv[2]);

   // Calculate the minimum and maximum sum this many dice can result in
   const int MIN_VALUE = NUM_DICE;
   const int MAX_VALUE = NUM_DICE * 6;

   // Create and initialize an array to hold the count of different sums
   int count[MAX_VALUE + 1];
   for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
   {
       count[i] = 0;
   }

   // Conduct a series of simulated rolls of the specified number of dice
   for (int trial = 0; trial < NUM_TRIALS; trial++)
   {
       int sumTrial = 0;
       for (int die = 0; die < NUM_DICE; die++) {
	   int roll = rand() % 6 + 1;
	   sumTrial += roll;
       }
       count[sumTrial]++;
   }

   // Finally print out the probability of each sum
   for (int i = MIN_VALUE; i <= MAX_VALUE; i++)
   {
       printf("P(sum = %4d) = %.6f\n", i, (double)count[i] / NUM_TRIALS);
   }
}

