#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct TThreadToken {
    double* R;
    double* step;
    double start;
    int points;
    unsigned int* state;
} ThreadToken;

void* integral(void* arg);
int min(int a, int b);
int in_circle(double x, double y, double R);