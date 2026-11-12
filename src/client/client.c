#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "client.h"

int CreateClientSocket(void)
{
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (client_fd == -1) {
        perror("socket");
        return -1;
    }

    return client_fd;
}

int ConnectToServer(int socket_fd, const char *ip, int port)
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) != 1) {
        fprintf(stderr, "Invalid IP address: %s\n", ip);
        return -1;
    }

    if (connect(socket_fd,
                (struct sockaddr *)&server_addr,
                sizeof(server_addr)) == -1) {
        perror("connect");
        return -1;
    }

    printf("Connected to %s:%d\n", ip, port);

    return 0;
}