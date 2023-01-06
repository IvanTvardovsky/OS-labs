#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <math.h>
#include <stdbool.h>

const char LIBRARY1[] = "./library1.so";
const char LIBRARY2[] = "./library2.so";

int main(int argc, char* argv[]) {
    void *library;
    bool type = false;
    int x, a, b;
    long c;

    library = dlopen(LIBRARY2, RTLD_LAZY);
    if (!library) {
        printf("Error dlopen(): %s\n", dlerror());
        return 1;
    }

    int(*PrimeCount)(int x, int y);
    char*(*Translation)(long x);
    *(void**)(&PrimeCount) = dlsym(library, "PrimeCount");
    *(void**)(&Translation) = dlsym(library, "Translation");

    for (;;) {
        scanf("%d", &x);
        if (x == 0) {
            dlclose(library);
            if (type) {
                library = dlopen(LIBRARY2, RTLD_LAZY);
                type = false;
            } else {
                library = dlopen(LIBRARY1, RTLD_LAZY);
                type = true;
            }
            if (!library) {
                printf("Error dlopen(): %s\n", dlerror());
                return 1;
            }
            *(void**)(&PrimeCount) = dlsym(library, "PrimeCount");
            *(void**)(&Translation) = dlsym(library, "Translation");
        } else if (x == 1 ) {
            scanf("%d %d", &a, &b);
            printf("Result: ");
            int n = PrimeCount(a, b);
            printf("%d\n", n);
        } else if (x == 2) {
            scanf("%ld", &c);
            printf("Result: ");
            char* res = Translation(c);
            printf("%s\n", res);
        } else {
            dlclose(library);
            return 0;
        }
    }
    return 0;
}