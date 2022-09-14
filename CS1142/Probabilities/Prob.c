/**
 * Working with files to convert probabilities to log probabilities
 */

#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    double prob = 0.0;

    FILE *in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Failed to open %s for input!\n", argv[1]);
        return 1;
    }

    FILE *out = fopen(argv[2], "w");
    if (out == NULL) {
        fclose(in);
        in = NULL;
        printf("Failed to open %s for output!\n", argv[2]);
        return 1;
    }

    while (fscanf(in, "%lf", &prob) == 1) {
        double logProb = log10(prob);
        fprintf(out, "%e\n", logProb);
    }

    fclose(in);
    in = NULL;
    fclose(out);
    out = NULL;

    return 0;
}
