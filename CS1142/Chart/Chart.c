/* Programming activity: Arrays and standard input
 * 
 * This program reads in a number specifying the size
 * of a one-dimensional array. It then reads integers
 * into the array. Finally it prints out a bar chart
 * of the data.
 *
 * Example output:
 * 
 * % ./Chart
 * How many numbers? 3
 * 1
 * 2
 * 4
 * *
 * **
 * ****
 */

#include <stdio.h>

int main(void)
{
    int num = 0;

    printf("How many numbers? ");
    scanf("%d", &num);
    
    int nums[num];
    for (int i = 0; i < num; i++)
    {
        scanf("%d", &nums[i]);
    }

    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < nums[i]; j++) {
	    printf("*");
	}
	printf("\n");
    }

    return 0;
}
