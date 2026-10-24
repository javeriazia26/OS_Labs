

#include <stdio.h>      // for printf()
#include <sys/ipc.h>    // for IPC mechanisms
#include <sys/msg.h>    // for message queue functions
#include <string.h>     // for strcpy()

// define structure for message
struct msg_buffer {
    long msg_type;         // message type (must be long)
    char msg_text[100];    // actual message content
};

int main() {
    // generate unique key using file + integer
    key_t key = ftok("progfile", 65);

    // create or access message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msg_buffer message;  // message structure

    message.msg_type = 1;       // assign message type

    // copy string into message buffer
    strcpy(message.msg_text, "Hello via mailbox");

    // send message to queue
    msgsnd(msgid, &message, sizeof(message), 0);

    printf("Message sent\n");

    // receive message from queue
    msgrcv(msgid, &message, sizeof(message), 1, 0);

    printf("Received: %s\n", message.msg_text);

    // delete message queue after use
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}


