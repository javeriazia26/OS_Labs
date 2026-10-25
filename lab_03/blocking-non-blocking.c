
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int main(void)
{
    int fd[2];
    char buffer[100];
    const char *msg = "Hello through pipe";

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
        // Child process: read from the pipe
        close(fd[1]);

        printf("Child: Trying blocking read...\n");
        ssize_t n = read(fd[0], buffer, sizeof(buffer) - 1);

        if (n == -1) {
            perror("read");
            close(fd[0]);
            exit(1);
        }

        buffer[n] = '\0';
        printf("Child received: %s\n", buffer);

        // Enable non-blocking mode
        int flags = fcntl(fd[0], F_GETFL);

        if (flags == -1 ||
            fcntl(fd[0], F_SETFL, flags | O_NONBLOCK) == -1) {
            perror("fcntl");
            close(fd[0]);
            exit(1);
        }

        printf("Child: Trying non-blocking read...\n");

        n = read(fd[0], buffer, sizeof(buffer));

        if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
            printf("Child: No data available; read returned immediately.\n");
        } else if (n == 0) {
            printf("Child: Pipe is closed; no more data.\n");
        } else if (n > 0) {
            printf("Child: Received additional data.\n");
        } else {
            perror("read");
        }

        close(fd[0]);
        exit(0);
    } else {
        // Parent process: write to the pipe
        close(fd[0]);

        sleep(2);
        printf("Parent: Sending message...\n");

        if (write(fd[1], msg, strlen(msg) + 1) == -1) {
            perror("write");
            close(fd[1]);
            wait(NULL);
            return 1;
        }

        close(fd[1]);
        wait(NULL);
    }

    return 0;
}
