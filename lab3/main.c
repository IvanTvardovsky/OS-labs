#include "general.h"

int main(int argc, const char** argv) {

    if (argc < 2) {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int countThreads = atoi(argv[1][0]);

    double r;

    printf("Given radius is: ");
    scanf("%lf", &r);

    if (r < 0) {
        printf("Given radius is negative\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Answer is approximately %.20lf\n", CalculateDiameter(r, countThreads, 1000000000));
    return 0;
}