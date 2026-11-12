#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "buffer.h"

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

int CreateSocket() {
    // Create TCP socket using IPv4
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        perror("socket");
        return -1;
    }

    // Allow address reuse
    int opt = 1;

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }

    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, SOMAXCONN);

    return server_fd;
}

int main(void) {
    int server_fd = CreateSocket();

    if (server_fd == -1) {
        return 1;
    }

    printf("Socket created successfully! FD: %d\n", server_fd);

    int client_fd = accept(server_fd, NULL, NULL);
    if (client_fd == -1) {
        perror("accept");
        close(server_fd);
        return 1;
    }

    printf("A client connected!\n");

    close(client_fd);
    close(server_fd);

    return 0;
}