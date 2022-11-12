#include "parent.h"
#include "utils.h"

#include <sys/wait.h>
#include <fcntl.h>
    
void ParentRoutine(FILE* stream) {
    char inputFileName[256];
    fscanf(stream, "%s", inputFileName);

    char outputFileName[256];
    fscanf(stream, "%s", outputFileName);

    int inputFile;

    inputFile = open(inputFileName, O_RDONLY);
    if (inputFile < 0) {
        char message[] = "Can't open input file\n";
        write(STDERR_FILENO, &message, sizeof(message) - 1);
        exit(EXIT_FAILURE);
    }

    int pipe[2];    
    CreatePipe(pipe);

    int id = fork();
    if (id == 0) {
        
        dup2(inputFile, STDIN_FILENO);
        dup2(pipe[1], STDOUT_FILENO);
        dup2(pipe[1], STDERR_FILENO);

        close(inputFile);
        close(pipe[0]);
        close(pipe[1]);

        char* argv[3];
        argv[0] = getenv("child");
        argv[1] = inputFileName;
        argv[2] = NULL;

        if (execv(getenv("child"), argv) == -1) {
            printf("Failed to exec\n");
            exit(EXIT_FAILURE);
        }

    } else if (id > 0) {
        close(pipe[1]);
        waitpid(id, (int *)NULL, 0);
        FILE *outputFile;
        outputFile = fopen(outputFileName, "w");
        float result;
        while (read(pipe[0], &result, sizeof(result))) {
            fprintf(outputFile, "%f\n", result);
        }
        close(pipe[0]);
        fclose(outputFile);
    } else {
        printf("Failed to fork\n");
        exit(EXIT_FAILURE);
    }
}