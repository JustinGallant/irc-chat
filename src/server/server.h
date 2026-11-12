#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 32
#define SERVER_PORT 6667

struct Client {
    int socket_fd;
    size_t client_id;
    char username[32];
    int active;
};

struct Room {
    size_t room_id;
    char name[64];

    struct Client* clients[MAX_CLIENTS];
    int client_count;

    struct Message messages[BUFFER_SIZE];
    int head;
    int count;
};

int CreateSocket();

#endif