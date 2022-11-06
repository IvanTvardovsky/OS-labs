#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double CalculateDiameter(double r, int countThreads, int totalPoints);