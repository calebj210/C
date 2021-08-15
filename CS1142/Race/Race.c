/* Programming activity: scanf, operators, conversions
 *
 * Read in the names and time of two racers. Determines which racer won
 * and how much faster that racer was. Reads input from standard input
 * in the format shown below in race1.txt and race2.txt.
 *
 * Correct the code in the five areas denoted by the TODO comments.
 * After fixing an area, run the program and see what output you get.
 * Don't forget to compile after any change to the source!
 *
 * Reference output:
 *  % cat race1.txt
 *  Rabbit  12 minutes, 37.35 seconds
 *  Turtle  13 minutes, 8.77 seconds
 *  % ./Race < race1.txt
 *  Racer 1: Rabbit finished in 12 minutes and 37.35 seconds (757.35 seconds)
 *  Racer 2: Turtle finished in 13 minutes and 8.77 seconds (788.77 seconds)
 *  Racer 1 won and was 4.15% faster
 *
 *  % cat race2.txt
 *  Rabbit  14 minutes, 1.05 seconds
 *  Turtle  11 minutes, 4.01 seconds
 *  % ./Race < race2.txt
 *  Racer 1: Rabbit finished in 14 minutes and 1.05 seconds (841.05 seconds)
 *  Racer 2: Turtle finished in 11 minutes and 4.01 seconds (664.01 seconds)
 *  Racer 2 won and was 26.66% faster
 *
 */

#include <stdio.h>

int main() {
    char name1[100];
    int minutes1 = 0;
    double seconds1 = 0;
    scanf("%99s %d minutes, %lf seconds", name1, &minutes1, &seconds1);
    double time1 = minutes1 * 60 + seconds1;
    printf("Racer 1: %s finished in %d minutes and %.2f seconds (%.2f seconds)\n", name1, minutes1, seconds1, time1);

    char name2[100];
    int minutes2 = 0;
    double seconds2 = 0;
    scanf("%99s %d minutes, %lf seconds", name2, &minutes2, &seconds2);
    double time2 = minutes2 * 60 + seconds2;
    printf("Racer 2: %s finished in %d minutes and %.2f seconds (%.2f seconds)\n", name2, minutes2, seconds2, time2);

    if (time1 == time2) {
        printf("Racer 1 and 2 tied, what are the odds?!?\n");
    }
    else if (time1 < time2) {
        double percentIncrease = (time2 - time1) / time1 * 100.0;
        printf("Racer 1 won and was %.2f%% faster\n", percentIncrease);
    }
    else {
        double percentIncrease = (time1 - time2) / time2 * 100.0;
        printf("Racer 2 won and was %.2f%% faster\n", percentIncrease);
    }

    return 0;
}
