#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buffer[100];

    pipe(fd);

    if (fork() == 0) {
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
    } else {
        close(fd[0]);
        char msg[] = "Hello from parent";
        write(fd[1], msg, strlen(msg) + 1);
        wait(NULL);
    }

    return 0;
}
