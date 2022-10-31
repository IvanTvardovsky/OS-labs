#include "parent.h"
#include "utils.h"

#include <sys/wait.h>
#include <fcntl.h>

void ParentRoutine(FILE* stream) {
    char fileName[256];
    fscanf(stream, "%s", fileName);

    int file;

    file = open(fileName, O_RDONLY);
        if (file < 0) {
            char message[] = "can't open file\n";
            write(STDERR_FILENO, &message, sizeof(message) - 1);
            exit(EXIT_FAILURE);
        }

    int pipe[2];    
    CreatePipe(pipe);

    int id = fork();
    if (id == 0) {
        
        dup2(file, STDIN_FILENO);
        dup2(pipe[1], STDOUT_FILENO);
        dup2(pipe[1], STDERR_FILENO);

        close(file);
        close(pipe[0]);
        close(pipe[1]);

        char* argv[3];
        argv[0] = "child";
        argv[1] = fileName;
        argv[2] = NULL;

        if (execv("./child", argv) == -1) {
            printf("Failed to exec\n");
            exit(EXIT_FAILURE);
        }

    } else if (id > 0) {
        close(pipe[1]);
        waitpid(id, (int *)NULL, 0);
        float result;
        while (read(pipe[0], &result, sizeof(result))) {
            char buff[50];
            gcvt(result, 7, buff);
            int i;
            for (i = 0; i < 50; i++) {
                if (buff[i] == '\0') {
                    break;
                }
            }
            buff[i] = '\n';
            write(STDOUT_FILENO, &buff, i + 1);
        }
        close(pipe[0]);
    } else {
        printf("Failed to fork\n");
        exit(EXIT_FAILURE);
    }
}