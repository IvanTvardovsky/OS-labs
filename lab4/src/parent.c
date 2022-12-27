#include "parent.h"
#include "utils.h"

#include <sys/mman.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
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

    int id = fork();
    if (id == 0) {

        dup2(inputFile, STDIN_FILENO);

        char* argv[3];
        argv[0] = getenv("child");
        argv[1] = inputFileName;
        argv[2] = NULL;

        if (execv(getenv("child"), argv) == -1) {
            printf("Failed to exec\n");
            exit(EXIT_FAILURE);
        }

    } else if (id > 0) {
        int status;
        waitpid(id, &status, 0);

        // Дочерний завершился из-за необработанного сигнала
        if (WIFSIGNALED(status)) {
            fprintf(stderr, "Child process terminated by signal: %d\n", WTERMSIG(status));
            shm_unlink(MEMORY_NAME);
            exit(EXIT_FAILURE);
        }

        if (WEXITSTATUS(status) != 0) {
            exit(EXIT_FAILURE);
        }

        FILE *outputFile;
        outputFile = fopen(outputFileName, "w");

        int fd = shm_open(MEMORY_NAME, O_CREAT | O_RDWR, 0777);

        if (fd == -1) {
            printf("Can't open shared memory file\n");
            exit(EXIT_FAILURE);
        }

        char *addr = mmap(NULL, MEMORY_SIZE, PROT_READ, MAP_SHARED, fd, 0);

        if (addr == (char*)-1 ) {
            printf("Mmap error\n");
            exit(EXIT_FAILURE);
        }

        fprintf(outputFile, "%s", addr);

        munmap(addr, MEMORY_SIZE);
        shm_unlink(MEMORY_NAME);
        close(fd);
        fclose(outputFile);
    } else {
        printf("Failed to fork\n");
        exit(EXIT_FAILURE);
    }
}