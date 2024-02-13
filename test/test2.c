#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        // execl("/nonexistent/command", "command", NULL);
        // perror("execl");
        printf("Normal case\n");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        wait(&status);
        printf("%d", status);
    }

    return 0;
}
