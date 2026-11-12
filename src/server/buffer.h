#ifndef BUFFER_H
#define BUFFER_H

#include <stdio.h>
#include <string.h>
#include <stdatomic.h>
#include <time.h>

#define BUFFER_SIZE 3
#define MESSAGE_SIZE 512

// Message structure
struct Message {
    char content[MESSAGE_SIZE];
    size_t sender_id;
    time_t timestamp;
};

// Circular buffer
struct MessageBuffer {
    struct Message messages[BUFFER_SIZE];
    int head;
    int count;
};

void add_message(struct MessageBuffer* buffer, const char* message);

void print_messages(struct MessageBuffer *buffer);

#endif