/**
 * ASCII Drawing Program
 * Given a drawing file, this program will create an image in
 * stdout described by the drawing file.
 *
 * Author Caleb Jacobs (cajacobs)
 * CS1142 Spring 2021
 * Date Last Modified: 03/08/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Initialize image array entries to 0.0
void initImage(int width, int height, double image[width][height]) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            image[i][j] = 0.0;
        }
    }
}

// Get greyscale color of a double color value
char greyscale(double val) {
    if (0.0 <= val && val < 0.1) {
        return ' ';
    } else if (val < 0.2) {
        return '.';
    } else if (val < 0.3) {
        return ':';
    } else if (val < 0.4) {
        return '-';
    } else if (val < 0.5) {
        return '=';
    } else if (val < 0.6) {
        return '+';
    } else if (val < 0.7) {
        return '*';
    } else if (val < 0.8) {
        return '#';
    } else if (val < 0.9) {
        return '%';
    } else {
        return '@';
    }
}
// Print image array to stdout with a border
void printImage(int width, int height, double image[width][height]) {
    // Print top border
    printf("+");
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("+\n");

    // Print image
    for (int j = 0; j < height; j++) {
        printf("|");
        for (int i = 0; i < width; i++) {
            printf("%c", greyscale(image[i][j]));
        }
        printf("|\n");
    }

    // Print bottom border
    printf("+");
    for (int i = 0; i < width; i++) {
        printf("-");
    }
    printf("+\n");
}

// Draw a point in an image array
void drawPoint(int width, int height, double image[width][height], int x, int y, double color) {
    if (0 <= x && x < width && 0 <= y && y < height) {
        image[x][y] = color;    
    }
} 

// Draw a rectangle of a specified color, width, height, and position
void drawRectangle(int width, int height, double image[width][height], int left, int top, int recWidth, int recHeight, double color) {
    for (int i = 0; i < recWidth; i++) {
        for (int j = 0; j < recHeight; j++) {
            drawPoint(width, height, image, left + i, top + j, color);
        }
    }
}

// Draw a line specified by endpoints and a color
void drawLine(int width, int height, double image[width][height], int x1, int y1, int x2, int y2, double color) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double step, x, y;
    if (fabs(dx) >= fabs(dy)) {
        step = fabs(dx);
    } else {
        step = fabs(dy);
    }

    dx /= step;
    dy /= step;
    
    x = x1;
    y = y1;
    for (int i = 0; i <= step; i++) {
        drawPoint(width, height, image, round(x), round(y), color);
        x += dx;
        y += dy;
    }
}

// Computer color statistics of a given image
void getImageStats(int width, int height, double image[width][height], double *minCol, double *maxCol, double *avgCol) {
    double min = image[0][0];       // Minimum entry value in image
    double max = image[0][0];       // Maximum entry value in image
    double avg = 0.0;               // Average entry value in image
    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Update min
            if (image[i][j] < min) {
                min = image[i][j];
            }

            // Update max
            if (image[i][j] > max) {
                max = image[i][j];
            }

            // Add to sum of entries
            avg += image[i][j];
        }
    }

    // Compute average from sum of entries
    avg /= width*height;

    // Store min, max, and average
    *minCol = min;
    *maxCol = max;
    *avgCol = avg;
}

// Fill a region of an image with a specified color
void floodFill(int width, int height, double image[width][height], int x, int y, double color) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;                         // Return if (x,y) coordinate is not in frame 
    } else if (image[x][y] >= color) {
        return;                         // Return if color is not darker than current value
    }
    image[x][y] = color;                // Set color

    // Flood value to the:
    floodFill(width, height, image, x - 1, y, color); // West
    floodFill(width, height, image, x + 1, y, color); // East
    floodFill(width, height, image, x, y - 1, color); // South
    floodFill(width, height, image, x, y + 1, color); // North
}

// Print the resulting greyscale image as ASCII art.
int main(void) {
    // Read in the size of the drawing canvas
    int width  = 0;
    int height = 0;
    int result = scanf("%d %d", &width, &height);

    // Program only supports images that are 1x1 or bigger
    if ((width <= 0) || (height <= 0) || (result != 2)) {
        printf("Failed to read a valid width and height from standard input!\n");
        return 0;
    }
    
    // Create the 2D arary and initialize all the greyscale values to 0.0
    double image[width][height];
    initImage(width, height, image);
    
    char command = '\0';
    double color = 0.0;
    
    // Keep reading in drawing commands until we reach the end of the input
    while (scanf(" %c", &command) == 1) {
        switch (command) {		
            case 'p': {
                // Draw a point, read in: x, y, color
                int x = 0;
                int y = 0;
                result = scanf("%d %d %lf", &x, &y, &color);
                if (result != 3) {
                    printf("Invalid point command!\n");
                    return 0;
                }
		
                drawPoint(width, height, image, x, y, color);
                break;
            }
            case 'r': {
                // Draw a rectangle, read in: x, y, w, h, color
                int left = 0;
                int top = 0;
                int rectangleWidth = 0;
                int rectangleHeight = 0;
                result = scanf("%d %d %d %d %lf", &left, &top, &rectangleWidth, &rectangleHeight, &color);
                if (result != 5) {
                    printf("Invalid rectangle command!\n");
                    return 0;
                }
                
                drawRectangle(width, height, image, left, top, rectangleWidth, rectangleHeight, color);
                break;
            }
            case 'l': {
                // Draw a line, read in x1, y1, x2, y2, color
                int x1 = 0;
                int y1 = 0;
                int x2 = 0;
                int y2 = 0;                
                result = scanf("%d %d %d %d %lf", &x1, &y1, &x2, &y2, &color);
                if (result != 5) {
                    printf("Invalid line command!\n");
                    return 0;
                }
                drawLine(width, height, image, x1, y1, x2, y2, color);
                break;
            }            
            case 'f': {
                // Flood fill a color in, read in: x, y, color
                int x = 0;
                int y = 0;
                result = scanf("%d %d %lf", &x, &y, &color);
                if (result != 3)
                {
                    printf("Invalid flood fill command!\n");
                    return 0;
                }
                
                floodFill(width, height, image, x, y, color);
                break;
            }
            default: {
                printf("Unknown command!\n");
                return 0;
            }
        }
    }
	
    // Print the final image
    printImage(width, height, image);
    
    // Finally display some statistics about the image
    double minColor = 0.0;
    double maxColor = 0.0;
    double avgColor = 0.0;
    getImageStats(width, height, image, &minColor, &maxColor, &avgColor);
    printf("Color range [%.2f, %.2f], average %.4f\n", minColor, maxColor, avgColor);
}
