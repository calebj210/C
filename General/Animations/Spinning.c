#include <stdio.h>
#include <unistd.h>

int main() {
    int i;
    const char progress[4] = "|/-\\";

    for (i = 0; i < 100; i += 10) {
        printf("Processing: %3d%%\r",i);
        fflush(stdout);
        sleep(0.25);
    }
    printf("\n");
    fflush(stdout);

    printf("Processing: ");
    for (i = 0; i < 100; i += 10) {
        printf("%c\b", progress[(i/10)%(sizeof(progress))]); /* \b goes one back */
        fflush(stdout);
        sleep(1);
    }

    printf("\n");
    fflush(stdout);
}
