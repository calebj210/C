/* Programming activity: Reading input from file
 *
 * Complete the missing parts of the program to implement a
 * program that reads in a series of (x, y) points and computes
 * the lower-left and upper-right points that exactly enclose
 * the set of points. Also compute the center of mass.
 *
 * Reference output:
 *   % ./BoundingBox < points10.txt
 *   bounding box (-2.20, -9.20) to (11.10, 6.60)
 *   center of mass (3.22, 0.23)
 *
 *   % ./BoundingBox < points4.txt
 *   bounding box (-1.00, -1.00) to (1.00, 1.00)
 *   center of mass (0.00, 0.00)
 *
 *  % ./BoundingBox < hline.txt
 *  bounding box (-13.70, 2.20) to (12.20, 2.20)
 *  center of mass (-0.50, 2.20)
 *
 *  % ./BoundingBox < vline.txt
 *  bounding box (0.00, -6.33) to (0.00, 2.22)
 *  center of mass (0.00, -1.00)
 *
 * % ./BoundingBox < points1.txt
 * bounding box (5.68, 5.68) to (5.68, 5.68)
 * center of mass (5.68, 5.68)
 *
 */

#include <stdio.h>
#include <float.h>  // Needed to get DBL_MAX constant

int main()
{
   // For holding the latest (x, y) point read from the file
   double x = 0.0;
   double y = 0.0;

   // For keeping track of the current min/max x-coordinate and y-coordinate
   double minX = DBL_MAX;
   double maxX = -DBL_MAX;
   double minY = DBL_MAX;
   double maxY = -DBL_MAX;

   // For tracking the sum and count of points, needed to compute center of mass
   double sumX = 0.0;
   double sumY = 0.0;
   int count = 0;
   
   // Keep looping as long as we successfully read in two double values
   // TODO 1: change true to read in using scanf
   while (scanf("%lf %lf", &x, &y) == 2) {
       if (x < minX) {
	   minX = x;
       }
       if (x > maxX) {
	   maxX = x;
       }

       if (y < minX) {
	   minY = y;
       }
       if (y > maxX) {
	   maxY = y;
       }

       sumX += x;
       sumY += y;
       count++;
   }

   printf("bounding box (%.2f, %.2f) to (%.2f, %.2f)\n", minX, minY, maxX, maxY);
   printf("center of mass (%.2f, %.2f)\n", sumX / count, sumY / count);
}
