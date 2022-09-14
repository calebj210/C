#include <stdio.h>

void swap(int *A, int i, int j) {
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

int partition(int *A, int n, int p, int r) {
    int pivot = A[r];
    int i = p;
    int j = r - 1;
    while (i <= j) {
        while (i <= j && A[i] <= pivot) {
            i++;
        }
        while (i <= j && A[j] >= pivot) {
            j--;
        }
        if (i < j) {
            swap(A, i, j);
            i++;
            j--;
        }
    }

    swap(A, r, i);
    
    return i;
}

void quickSort(int *A, int n, int p, int r) {
    if (p < r) {
        int q = partition(A, n, p, r);

        printf("p = %d, q = %d, r = %d\n", p, q, r);

        quickSort(A, n, p, q - 1);
        quickSort(A, n, q + 1, r);
    }
}

void sort(int *A, int n) {
    quickSort(A, n, 0, n-1);
}


int main() {
    int A[10] = {1,2,4,9,5,10,3,8,6,7};

    sort(A, 10);

    printf("[");

    for (int i = 0; i < 10; i++) {
        printf("%d, ", A[i]);
    }

    printf("\b\b]\n");

    return 0;
}
