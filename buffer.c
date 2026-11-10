#include "buffer.h"

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