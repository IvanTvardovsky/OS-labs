#include "../include/functions.h"

int PrimeCount(int a, int b) {
    int counter = 0;
    int mas[b + 1];
    for (int i = 0; i < b + 1; ++i){
        mas[i] = i;
    }
    for (int i = 2; i*i <= b; ++i){
        if (mas[i]){
            for (int j = i*i; j <= b; j += i){
                mas[j] = 0;
            }
        }
    }
    for (int i = 0; i <= b; ++i){
        if (mas[i] && i >= a && i != 1){
            ++counter;
        }
    }
    return counter;
}

char* Translation(long x) {
    char* res = (char*) malloc(64 * sizeof(char));
    do {
        *--res = x % 3 + '0';
        x /= 3;
    }
    while (x != 0);
    return res;
}
