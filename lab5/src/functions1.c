#include "../include/functions.h"

int PrimeCount(int a, int b) {
    int counter = 0;
    for (int i = a; i <= b; ++i) {
        short flag = 1;
        for (int j = 2; j < i; ++j) {
            if (i % j == 0) flag = 0;
        }
        if (flag == 1) ++counter;
    }
    return counter;
}

char* Translation(long x) {
    char* res = (char*) malloc(64 * sizeof(char));
    do {
        *--res = x % 2 + '0';
        x /= 2;
    }
    while (x != 0);
    return res;
}

int main(){
    return 0;
}
