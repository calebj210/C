/**
 * Compute the maximum adjacent product in a given list of numbers
 */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ULL_INT;

/**
 * Helper methods
 */
ULL_INT maxAdjacent(int width, int height, int A[width][height], int n);
ULL_INT maxLeftRight(int x, int y, int width, int height, int A[width][height], int n);
ULL_INT maxUpDown(int x, int y, int width, int height, int A[width][height], int n);
ULL_INT maxDiag(int x, int y, int width, int height, int A[width][height], int n);

/**
 * Driver for computing the max adjacent product
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Problem_11 <product length>\n");
        return 0;
    }

    int n = atoi(argv[1]);          // Product length

    int width;                      // Width of number array
    int height;                     // Height of number array
    scanf("%d %d", &width, &height);

    int A[width][height];           // Array of data
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    // Compute the max adjacent product
    ULL_INT maxProduct = maxAdjacent(width, height, A, n);

    printf("The max adjacent product of %d numbers is given by %llu.\n", n, maxProduct);

    return 0;
}

ULL_INT max(ULL_INT a, ULL_INT b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

ULL_INT maxLeftRight(int x, int y, int width, int height, int A[width][height], int n) {
    int rb = x + n - 1;         // Right bound
    int lb = x - n + 1;         // Left bound
    
    ULL_INT rProd = 0;              // Right product
    ULL_INT lProd = 0;              // Left product

    // Compute right product
    if (rb < width) {
        rProd = 1;
        for (int i = x; i <= rb; i++) {
            rProd  *= A[i][y];
        }
    }

    // Compute left product
    if (lb >= 0) {
        lProd = 1;
        for (int i = x; i >= lb; i--) {
            lProd *= A[i][y];
        }
    }

    return max(rProd, lProd);
}

ULL_INT maxUpDown(int x, int y, int width, int height, int A[width][height], int n) {
    int ub = y - n + 1;         // Up bound
    int db = y + n - 1;         // Down bound
    
    ULL_INT uProd = 0;              // Up product
    ULL_INT dProd = 0;              // Down product

    // Compute up product
    if (ub >= 0) {
        uProd = 1;
        for (int i = y; i >= ub; i--) {
            uProd  *= A[x][i];
        }
    }

    // Compute down product
    if (db < height) {
        dProd = 1;
        for (int i = y; i <= db; i++) {
            dProd *= A[x][i];
        }
    }

    return max(uProd, dProd);
}

ULL_INT maxDiag(int x, int y, int width, int height, int A[width][height], int n) {
    int ub = y - n + 1;         // Up bound
    int db = y + n - 1;         // Down bound
    int rb = x + n - 1;         // Right bound
    int lb = x - n + 1;         // Left bound
    
    ULL_INT urProd = 0;             // Up-right product
    ULL_INT drProd = 0;             // Down-right product
    ULL_INT ulProd = 0;             // Up-left product
    ULL_INT dlProd = 0;             // Down-left product

    // Compute up-right product
    if (ub >= 0 && rb < width) {
        urProd = 1;
        for (int i = 0; i < n; i++) {
            urProd  *= A[x + i][y - i];
        }
    }
    
    // Compute down-right product
    if (db < height &&  rb < width) {
        drProd = 1;
        for (int i = 0; i < n; i++) {
            drProd  *= A[x + i][y + i];
        }
    }

    // Compute up-left product
    if (ub >= 0 &&  lb >= 0) {
        ulProd = 1;
        for (int i = 0; i < n; i++) {
            ulProd  *= A[x - i][y - i];
        }
    }
    
    // Compute down-left product
    if (db < height &&  lb >= 0) {
        dlProd = 1;
        for (int i = 0; i < n; i++) {
            dlProd  *= A[x - i][y + i];
        }
    }

    return max(urProd, max(drProd, max(ulProd, dlProd)));
}

ULL_INT pointMax(int x, int y, int width, int height, int A[width][height], int n) {
    ULL_INT ud = maxUpDown(x, y, width, height, A, n);
    ULL_INT lr = maxLeftRight(x, y, width, height, A, n);
    ULL_INT d  = maxDiag(x, y, width, height, A, n);

    ULL_INT maxima = max(ud, max(lr, d));

    return maxima;
}

ULL_INT maxAdjacent(int width, int height, int A[width][height], int n) {
    ULL_INT curMax = 0;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            ULL_INT tmp = pointMax(x, y, width, height, A, n);

            if (tmp > curMax) {
                curMax = tmp;
            }
        }
    }

    return curMax;
}
