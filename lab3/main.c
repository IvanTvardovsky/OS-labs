#include "general.h"

int main(int argc, const char** argv) {

    if (argc < 2) {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int countThreads = 0;

    for (int i = 0; argv[1][i] > 0; ++i) {
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            countThreads = countThreads * 10 + argv[1][i] - '0';
        }
    }

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