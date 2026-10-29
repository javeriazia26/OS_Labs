
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define MESSAGE_COUNT 200
#define TEXT_SIZE 256

struct msg_buffer {
    long msg_type;
    char msg_text[TEXT_SIZE];
};

int main(int argc, char *argv[])
{
    if (argc != 2 ||
        (strcmp(argv[1], "blocking") != 0 &&
         strcmp(argv[1], "nowait") != 0)) {
        fprintf(stderr, "Usage: %s blocking|nowait\n", argv[0]);
        return 1;
    }

    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);

    if (msgid == -1) {
        perror("msgget");
        return 1;
    }

    struct msg_buffer message;
    message.msg_type = 1;

    if (strcmp(argv[1], "blocking") == 0) {
        printf("Mode: Blocking message sending\n");

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            msgctl(msgid, IPC_RMID, NULL);
            return 1;
        }

        if (pid == 0) {
            // Child: wait before receiving messages
            sleep(2);

            int received = 0;

            while (received < MESSAGE_COUNT) {
                ssize_t n = msgrcv(
                    msgid,
                    &message,
                    sizeof(message.msg_text),
                    1,
                    0
                );

                if (n == -1) {
                    perror("msgrcv");
                    _exit(1);
                }

                received++;
            }

            printf("Receiver: Received %d messages.\n", received);
            _exit(0);
        }

        // Parent: send messages in blocking mode
        for (int i = 0; i < MESSAGE_COUNT; i++) {
            snprintf(message.msg_text, sizeof(message.msg_text),
                     "Message %d", i + 1);

            if (msgsnd(msgid, &message,
                       sizeof(message.msg_text), 0) == -1) {
                perror("msgsnd");
                waitpid(pid, NULL, 0);
                msgctl(msgid, IPC_RMID, NULL);
                return 1;
            }

            if ((i + 1) % 25 == 0) {
                printf("Sender: Sent %d messages.\n", i + 1);
                fflush(stdout);
            }
        }

        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            msgctl(msgid, IPC_RMID, NULL);
            return 1;
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            fprintf(stderr, "Receiver did not finish successfully.\n");
            msgctl(msgid, IPC_RMID, NULL);
            return 1;
        }

    } else {
        // Non-blocking mode: stop when the queue is full
        printf("Mode: Non-blocking message sending\n");

        int sent = 0;

        while (1) {
            snprintf(message.msg_text, sizeof(message.msg_text),
                     "Message %d", sent + 1);

            if (msgsnd(msgid, &message,
                       sizeof(message.msg_text), IPC_NOWAIT) == -1) {
                if (errno == EAGAIN) {
                    printf("Queue is full; sender did not block.\n");
                    printf("Successfully sent: %d messages.\n", sent);
                    break;
                }

                perror("msgsnd");
                msgctl(msgid, IPC_RMID, NULL);
                return 1;
            }

            sent++;
        }
    }

    // Remove the queue when the demonstration finishes
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        return 1;
    }

    printf("Message queue removed.\n");
    return 0;
}
