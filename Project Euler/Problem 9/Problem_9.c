/**
 * Find the special pythagorean triplet that satifies a + b + c = 1000
 */

#include <stdio.h>
#include <stdbool.h>

bool isTriplet(int a, int b, int c) {
    return (a*a + b*b == c*c);
}


int main() {
    // Triplet numbers
    int a = 0;
    int b = 0;
    int c = 0;

    // Triplet found checker
    bool found = false;

    for (c = 3; c < 1000; c++) {
        for (b = 2; b < c; b++) {
            for (a = 1; a < b; a++) {
                if (isTriplet(a, b, c) && a + b + c == 1000) {
                    found = true;
                    break;
                }
            }

            if (found) {
                break;
            }
        }
        
        if (found) {
            break;
        }
    }
    
    // Print results
    printf("The special triplet is given by a = %d, b = %d, and c = %d.\n", a, b, c);
    printf("These values have a + b + c = %d and abc = %d.\n", a + b + c, a * b * c);
    printf("Furthermore, a^2 + b^2 = %d which equals c^2 = %d.\n", a*a + b*b, c*c);

    return 0;
}
