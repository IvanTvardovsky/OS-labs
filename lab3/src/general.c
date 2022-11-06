#include "../include/utils.h"
#include "../include/general.h"

double function(double R, int CountThreads) {
    int Total_points = 1000000000;
    double Diameter_Area;

    Diameter_Area = R * 2;
    pthread_t* th = malloc(sizeof(pthread_t) * CountThreads);
    ThreadToken* token = malloc(sizeof(ThreadToken) * CountThreads);
    unsigned int* states = malloc(sizeof(unsigned long int) * CountThreads);

    if (th == NULL || token == NULL || states == NULL) {
        printf("Can't allocate memory\n");
        exit(EXIT_FAILURE);
    }

    double start = -R;
    double step = (Diameter_Area / (double)CountThreads);
    int points = (Total_points + CountThreads - 1) / CountThreads;

    for (int i = 0; i < CountThreads; ++i) {
        token[i].start = start;
        token[i].step = &step;
        token[i].R = &R;
        token[i].points = min(points, Total_points - i * points);
        token[i].state = &states[i];
        start += step;
    }

    for (int i = 0; i < CountThreads; ++i) {
        if (pthread_create(&th[i], NULL, &integral, &token[i]) != 0) {
            printf("Can't create thread\n");
            exit(EXIT_FAILURE);
        }
    }

    points = 0;

    for (int i = 0; i < CountThreads; ++i) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Can't join threads\n");
            exit(EXIT_FAILURE);
        }
        points += token[i].points;
    }

    free(token);
    free(th);
    free(states);

    return(Diameter_Area*Diameter_Area * ((double) points / (Total_points)));
}
