
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(void)
{
    int x = 5;
    int status;

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        /* Child process */
        x = 15;

        printf("Child process: x = %d\n", x);
        printf("Child process: executing ls -l\n");

        sleep(3);

        execlp("ls", "ls", "-l", (char *)NULL);

        /* This runs only if execlp() fails */
        perror("execlp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* Parent process */
        x = 3;

        printf("Parent process: x = %d\n", x);
        printf("Parent process: waiting for child...\n");

        if (wait(&status) == -1)
        {
            perror("wait failed");
            return 1;
        }

        if (WIFEXITED(status))
        {
            printf("Child exited normally with status: %d\n",
                   WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child terminated by signal: %d\n",
                   WTERMSIG(status));
        }
    }

    return 0;
}
