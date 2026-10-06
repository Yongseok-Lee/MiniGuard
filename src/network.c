#include "network.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>

int network_connect(const char *server_host, int server_port)
{
    // Create a socket file descriptor.
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        return -1;
    }

    // Initialize the server address.
    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);
    int result = inet_pton(AF_INET, server_host, &server_addr.sin_addr);
    if (result == 0)
    {
        fprintf(stderr, "inet_pton: Invalid IPv4 address: %s\n", server_host);
        close(sockfd);
        return -1;
    }
    else if (result == -1)
    {
        perror("inet_pton");
        close(sockfd);
        return -1;
    }

    // Connect the socket to the server.
    if (connect(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

    return sockfd;
}
