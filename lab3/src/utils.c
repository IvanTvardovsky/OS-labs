#include "utils.h"

void* Integral(void* arg) {
    TThreadToken token = *((TThreadToken*)arg);
    double x, y, r;
    r = *token.r;
    int *ustate = token.state;
    *ustate = time(NULL) ^ getpid() ^ pthread_self();
    int attempts = token.points;
    token.points = 0;

    for (int i = 0; i < attempts; ++i) {
        x = token.start + ((double)rand_r(ustate) / (double)(RAND_MAX)) * (*token.step);
        y = (((double)rand_r(ustate) / (double)(RAND_MAX)) - 0.5) * 2 * r;
        if (InCircle(x, y, r)) {
            ++token.points;
        }
    }
    ((TThreadToken*)arg) -> points = token.points;
    return arg;
}

int InCircle(double x, double y, double r) {
    return x * x + y * y <= r * r;
}

int Min(int a, int b) {
    return a < b ? a : b;
}
