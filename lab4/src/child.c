#include "utils.h"

#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(const int argc, const char* argv[]) {
    if (argc != 2) {
        printf("Necessary arguments were not provided\n");
        exit(EXIT_FAILURE);
    }

    FILE* out = fopen(argv[1], "r");
    if (!out) {
        printf("Failed to open file\n");
        exit(EXIT_FAILURE);
    }
    
    int fd = shm_open(MEMORY_NAME, O_CREAT | O_RDWR, 0777);
    if (fd == -1) {
        printf("Can't open shared memory file1\n");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, MEMORY_SIZE) == -1) {
        printf("Can't extent shared memory file\n");
        shm_unlink(MEMORY_NAME);
        exit(EXIT_FAILURE);
    }

    char* addr;

    addr = mmap(NULL, MEMORY_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (addr == (char*)-1 ) {
        printf("Mmap error\n");
        shm_unlink(MEMORY_NAME);
        exit(EXIT_FAILURE);
    }

    char* input;
    char* buf; 
    char* temporary;
    
    const int chunkSize = 256;
    char* outputString = (char*) malloc(chunkSize);
    int bufferSize = chunkSize;
    int currentBufferSize = 0;

    while ((input = ReadString(stdin)) != NULL) {
        int index = 0, inputLen = strlen(input), flag = 0, bufFlag = 1;

        buf = ReadNumber(input, index);
        index += strlen(buf) + 1;

        float result = atof(buf), output;
        free(buf);

        if (index == inputLen) bufFlag = 0;
        while (index < inputLen) {
            if (flag) {
                if (atof(buf) == 0) {
                    exit(EXIT_FAILURE);
                }
                result /= atof(buf);
                free(buf);
            } else {
                ++flag;
            }
            buf = ReadNumber(input, index);
            index += strlen(buf) + 1;
            if (buf == NULL) {
                break;
            }
        }

        if (bufFlag) {
            result /= atof(buf);
            free(buf);
        }
        free(input);
        output = (float)((int)(result * 100)) / 100;
        temporary = (char*) malloc(chunkSize * sizeof(char));
        gcvt(output, 5, temporary);
        currentBufferSize += strlen(temporary) + 1;

        while (currentBufferSize >= bufferSize) {
            outputString = realloc(outputString, bufferSize + chunkSize);
            bufferSize += chunkSize;
        }

        strcat(outputString, temporary);
        strcat(outputString, " ");
        free(temporary);
        close(fd);
    }
    printf("%s\n", outputString);
    memcpy(addr, outputString, (strlen(outputString) + 1) * sizeof(char));
    free(input);
    free(outputString);
    fclose(out);
    return 0;
}