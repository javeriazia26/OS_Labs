
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    int fd[2];
    char msg[100] = "Hello through pipe";
    char buffer[100];

    // Create the pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process: receive the message
        close(fd[1]);

        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);

        if (n == -1) {
            perror("read");
            close(fd[0]);
            exit(1);
        }

        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);

        close(fd[0]);
        exit(0);
    } else {
        // Parent process: send the message
        close(fd[0]);

        ssize_t n = write(fd[1], msg, strlen(msg) + 1);

        if (n == -1) {
            perror("write");
            close(fd[1]);
            wait(NULL);
            return 1;
        }

        printf("Parent sent: %s\n", msg);

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
