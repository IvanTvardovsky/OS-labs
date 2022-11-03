#include "../include/utils.h"

int main(int argc, const char** argv) {
    int Total_points = 100000000;
    double R, Total_Aria_Size;
    int CountThreads;
    
    if (argc < 2) {
        printf("Not enough arguments\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; argv[1][i] > 0; ++i) {
        if (argv[1][i] >= '0' && argv[1][i] <= '9') {
            CountThreads = CountThreads * 10 + argv[1][i] - '0';
        }
    }

    printf("Given radius is: ");
    scanf("%lf", &R);

    if (R < 0) {
        printf("Given radius is negative\n");
        exit(EXIT_FAILURE);
    }

    Total_Aria_Size = R * 2;
    pthread_t* th = malloc(sizeof(pthread_t) * CountThreads);
    ThreadToken* token = malloc(sizeof(ThreadToken) * CountThreads);
    unsigned int* states = malloc(sizeof(unsigned int) * CountThreads);

    if (th == NULL || token == NULL || states == NULL) {
        printf("Can't allocate memory\n");
        exit(EXIT_FAILURE);
    }

    double start = -R;
    double step = (Total_Aria_Size / (double)CountThreads);
    int Cpoints = (Total_points + CountThreads - 1) / CountThreads;

    for (int i = 0; i < CountThreads; ++i) {
        token[i].start = start;
        token[i].step = &step;
        token[i].R = &R;
        token[i].Cpoints = min(Cpoints, Total_points - i*Cpoints);
        token[i].state = &states[i];
        start += step;
    }

    for (int i = 0; i < CountThreads; ++i) {
        if (pthread_create(&th[i], NULL, &integral, &token[i]) != 0) {
            printf("Can't create thread\n");
            exit(EXIT_FAILURE);
        }
    }

    Cpoints = 0;

    for (int i = 0; i < CountThreads; ++i) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Can't join threads\n");
            exit(EXIT_FAILURE);
        }
        Cpoints += token[i].Cpoints;
    }

    printf("Answer is approximately: %.20lf\n",
    Total_Aria_Size*Total_Aria_Size * ((double) Cpoints / (Total_points)));
    free(token);
    free(th);
    free(states);
    return 0;
}
