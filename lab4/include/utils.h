#ifndef INC_1_UTILS_H
#define INC_1_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char* ReadString(FILE* stream);
char* ReadNumber(char* string, int idx);

#endif //INC_1_UTILS_H