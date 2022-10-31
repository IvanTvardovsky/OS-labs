#include "utils.h"

void CreatePipe(int pipeFd[2]) {
    if(pipe(pipeFd) != 0) {
        printf("Couldn't create pipe\n");
        exit(EXIT_FAILURE);
    }
}

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
        // printf("Zero string.\n");
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
        // printf("Zero buffer.\n");
        return NULL;
    }
    
    buffer[bufInd] = '\0';
 //   printf("%s %p\n", buffer, buffer);

    return buffer;
}