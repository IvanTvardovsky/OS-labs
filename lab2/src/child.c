#include "../include/utils.h"
#include <ctype.h>

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
    
    char* input = (char*) malloc(128 * sizeof(char));
    char* buf;
    
    while ((input = ReadString(stdin)) != NULL) {
        int index = 0, inputLen = strlen(input);
        
        buf = (char*) malloc(128 * sizeof(char));
        buf = ReadNumber(input, index);
        index += strlen(buf) + 1;

        float result = atof(buf);
        free(buf);
        buf = (char*) malloc(128 * sizeof(char));
        int flag = 0;

        while (index < inputLen) {
            if (flag) {
                if (atof(buf) == 0) {
                    exit(EXIT_FAILURE);
                }
                result /= atof(buf);
                free(buf);
                buf = (char*) malloc(128 * sizeof(char));
            } else {
                ++flag;
            }
            buf = ReadNumber(input, index);
            index += strlen(buf) + 1;
            if (buf == NULL) {
                break;
            }
        }
        result /= atof(buf);
        free(buf);
        free(input);
        
        input = (char*) malloc(128 * sizeof(char));
        // printf("%f\n", result);
        write(STDOUT_FILENO, &result, sizeof(result));
    } 
    fclose(out);

    return 0;
}