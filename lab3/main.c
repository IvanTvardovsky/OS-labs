#include "general.h"
#include  <time.h>

int main(int argc, const char** argv) {

    if (argc < 2) {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    int CountThreads = 0;

    for (int i = 0; argv[1][i] > 0; ++i) {
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            CountThreads = CountThreads * 10 + argv[1][i] - '0';
        }
    }

    double R;

    printf("Given radius is: ");
    scanf("%lf", &R);

    if (R < 0) {
        printf("Given radius is negative\n");
        exit(EXIT_FAILURE);
    }
    
    time_t t0 = time(0);
    printf("Answer is approximately %.20lf\n", function(R, CountThreads));
    time_t t1 = time(0);
    double time_in_seconds = difftime(t1, t0);
    printf("%.8lf\n", time_in_seconds);
    return 0;
}