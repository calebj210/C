/* Programming activity: functions, arrays, standard input
 *
 * Read in student data from standard input. The data consists of the points
 * each student has earned and an integer code indicating if they are an
 * undergrad (0), masters (1), or PhD (2) student.
 *
 * Replace the TODO sections of code to create a correct implementation.
 *
 */

#include <stdio.h>
#include <math.h>

// Compute the mean of the subset of the nums array that are of the specified type
double mean(int type, int size, int nums[size], int types[size]) {
    double sum = 0.0;
    int count = 0;
    
    for (int i = 0; i < size; i++) {
	if (types[i] == type) {
	    sum += nums[i];
	    count++;
	}
    }
    
    return (double)sum / count;
}

// Compute the variance of the subset of the nums array that are of the specified type
double var(int type, int size, int nums[size], int types[size]) {
    double avg = mean(type, size, nums, types);
    
    double sumSquareDifferences = 0.0;
    int count = 0;

    for (int i = 0; i < size; i++) {
	if (types[i] == type) {
	    double delta = nums[i] - avg;
	    sumSquareDifferences += delta * delta;
	    count++;
	}
    }
    
    return sumSquareDifferences / (count - 1);
}

// Compute the standard deviation of the subset of the nums array that are of the specified type
double stddev(int type, int size, int nums[size], int types[size]) {
    return sqrt(var(type, size, nums, types));
}

int main(void) {
    // First number in the file is how many students are in the data file
    int numStudents = 0;
    scanf("%d", &numStudents);
    
    // Create two parallel arrays that track a student's points and what type of student they are
    int studentPoints[numStudents];
    int studentTypes[numStudents];
    
    // Load the data into the arrays
    for (int i = 0; i < numStudents; i++) {
	scanf("%d %d", &studentPoints[i], &studentTypes[i]);
    }
    
    printf("Read in data for %d students...\n", numStudents);
    
    // Loop over the three student types, 0 = undergrad, 1 = masters, 2 = phd
    for (int type = 0; type < 3; type++) {
	printf("Student type %d\n", type);
	printf("-----------------\n");
	
	double average = mean(type, numStudents, studentPoints, studentTypes);
	printf("Average  : %6.2f\n", average);
	
	double variance = var(type, numStudents, studentPoints, studentTypes);
	printf("Variance : %6.2f\n", variance);
	
	double sd = stddev(type, numStudents, studentPoints, studentTypes);
	printf("Std dev  : %6.2f\n", sd);
	    printf("\n");
    }
}
