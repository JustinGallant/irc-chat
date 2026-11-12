#ifndef CLIENT_H
#define CLIENT_H

int CreateClientSocket(void);

int ConnectToServer(int socket_fd, const char *ip, int port);

#endif