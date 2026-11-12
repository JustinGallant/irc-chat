#include <stdio.h>
#include <unistd.h>

#include "client.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6667

int main(void)
{
    int client_fd = CreateClientSocket();

    if (client_fd == -1) {
        return 1;
    }

    if (ConnectToServer(client_fd, SERVER_IP, SERVER_PORT) == -1) {
        close(client_fd);
        return 1;
    }

    printf("Successfully connected to IRC server!\n");

    // Implement messaging and commands

    close(client_fd);

    return 0;
}