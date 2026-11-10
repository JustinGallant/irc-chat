#ifndef BUFFER_H
#define BUFFER_H

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
};

// Circular buffer
struct MessageBuffer {
    struct Messages messages[BUFFER_SIZE];
    int head;
    int count;
};

void add_message(struct MessageBuffer* buffer, const char* message);

void print_messages(struct MessageBuffer *buffer);

#endif