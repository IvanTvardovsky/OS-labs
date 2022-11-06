#include "utils.h"
#include "general.h"

double CalculateDiameter(double r, int countThreads, int totalPoints) {
    double diameterArea;

    diameterArea = r * 2;
    pthread_t* th = malloc(sizeof(pthread_t) * countThreads);
    TThreadToken* token = malloc(sizeof(TThreadToken) * countThreads);
    unsigned int* states = malloc(sizeof(unsigned long int) * countThreads);

    if (th == NULL || token == NULL || states == NULL) {
        printf("Can't allocate memory\n");
        exit(EXIT_FAILURE);
    }

    double start = -r;
    double step = (diameterArea / (double)countThreads);
    int points = (totalPoints + countThreads - 1) / countThreads;

    for (int i = 0; i < countThreads; ++i) {
        token[i].start = start;
        token[i].step = &step;
        token[i].r = &r;
        token[i].points = Min(points, totalPoints - i * points);
        token[i].state = &states[i];
        start += step;
    }

    for (int i = 0; i < countThreads; ++i) {
        if (pthread_create(&th[i], NULL, &Integral, &token[i]) != 0) {
            printf("Can't create thread\n");
            exit(EXIT_FAILURE);
        }
    }

    points = 0;

    for (int i = 0; i < countThreads; ++i) {
        if (pthread_join(th[i], NULL) != 0) {
            printf("Can't join threads\n");
            exit(EXIT_FAILURE);
        }
        points += token[i].points;
    }

    free(token);
    free(th);
    free(states);

    return(diameterArea*diameterArea * ((double) points / (totalPoints)));
}
