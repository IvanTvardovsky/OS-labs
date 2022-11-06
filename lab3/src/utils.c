#include "../include/utils.h"

void* integral(void* arg) {
    ThreadToken token = *((ThreadToken*)arg);
    double x, y, R;
    R = *token.R;
    int *ustate = token.state;
    *ustate = time(NULL) ^ getpid() ^ pthread_self();
    int attempts = token.points;
    token.points = 0;

    for (int i = 0; i < attempts; ++i) {
        x = token.start + ((double)rand_r(ustate) / (double)(RAND_MAX)) * (*token.step);
        y = (((double)rand_r(ustate) / (double)(RAND_MAX)) - 0.5) * 2 * R;
        if (in_circle(x, y, R)) {
            ++token.points;
        }
    }
    ((ThreadToken*)arg) -> points = token.points;
    return arg;
}

int in_circle(double x, double y, double R) {
    return (x * x + y * y <= R * R);
}

int min(int a, int b) {
    if (a < b) return a;
    return b;
}
