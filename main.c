#include <stdio.h>
#include <string.h>
#include <stdatomic.h>

#define BUFFER_SIZE 3
#define MESSAGE_SIZE 512

// User structure
struct Sender {
    size_t sender_id;
    char* username;
};

// Message structure
struct Messages {
    char message[MESSAGE_SIZE];
    struct Sender sender;
} Messages;

// Circular buffer
struct MessageBuffer {
    struct Messages messages[BUFFER_SIZE];
    int head;
    int count;
} MessageBuffer;

// Add new message to the buffer
void add_message(struct MessageBuffer* buffer, const char* message) {
    strncpy(buffer->messages[buffer->head].message, message, MESSAGE_SIZE - 1);

    buffer->messages[buffer->head].message[MESSAGE_SIZE - 1] = '\0';

    buffer->head = (buffer->head + 1) % BUFFER_SIZE;

    if (buffer->count < BUFFER_SIZE) {
        buffer->count++;
    }
}

// Print all messages currently in the buffer
void print_messages(struct MessageBuffer *buffer) {
    int oldest = (buffer->head - buffer->count + BUFFER_SIZE) % BUFFER_SIZE;

    for (int i = 0; i < buffer->count; i++) {
        int index = (oldest + i) % BUFFER_SIZE;

        printf("%s\n", buffer->messages[index].message);
    }
}

int main(void) {
    struct MessageBuffer buffer = {0};
    add_message(&buffer, "Hello");
    add_message(&buffer, "World");
    add_message(&buffer, "!");
    add_message(&buffer, "This");
    add_message(&buffer, "Is");
    add_message(&buffer, "Awesome");
    print_messages(&buffer);
}