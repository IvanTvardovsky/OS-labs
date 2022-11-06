#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    double* r;
    double* step;
    double start;
    int points;
    unsigned int* state;
} TThreadToken;

void* Integral(void* arg);
int Min(int a, int b);
int InCircle(double x, double y, double r);