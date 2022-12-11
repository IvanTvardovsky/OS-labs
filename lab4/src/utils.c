#include "utils.h"

char* ReadString(FILE* stream) {

    if (feof(stream)) {
        return NULL;
    }

    const int chunkSize = 256;
    char* buffer = (char*) malloc(chunkSize);
    int bufferSize = chunkSize;

    if (!buffer) {
        printf("Couldn't allocate buffer");
        exit(EXIT_FAILURE);
    }

    int readChar;
    int idx = 0;
    while ((readChar = getc(stream)) != EOF) {
        buffer[idx++] = readChar;

        if (idx == bufferSize) {
            buffer = realloc(buffer, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

        if (readChar == '\n') {
            break;
        }
    }

    buffer[idx] = '\0';

    return buffer;
}

char* ReadNumber(char* string, int idx) {
    const int chunkSize = 256;
    char* buffer = (char*) malloc(chunkSize);

    int bufferSize = chunkSize;

    if (!buffer) {
        printf("Couldn't allocate buffer");
        exit(EXIT_FAILURE);
    }
    if (string[idx] == ' ' || string[idx] == '\n' || string[idx] == '\0' || string[idx] == EOF) {
        free(buffer);
        return NULL;
    }

    int bufInd = 0;
    while (string[idx] != ' ' && string[idx] != '\n') {
        buffer[bufInd] = string[idx];
        
        ++idx;
        ++bufInd;

        if (bufInd == bufferSize) {
            buffer = realloc(buffer, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

    }

    if (strlen(buffer) == 0) {
        free(buffer);
        return NULL;
    }
    
    buffer[bufInd] = '\0';
    return buffer;
}