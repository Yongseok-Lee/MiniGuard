#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "config.h"

int parse_arguments(int argc, char *argv[], AppConfig *config)
{
    // Expect exactly six arguments after the program name.
    if (argc != 7)
        return -1;

    // Require options in the order: -d <path> -h <host> -p <port>.
    if (strcmp(argv[1], "-d") || strcmp(argv[3], "-h") || strcmp(argv[5], "-p"))
        return -1;

    // Reject empty watch paths and server addresses.
    if (argv[2][0] == '\0' || argv[4][0] == '\0')
        return -1;

    // Watch path
    int written;
    written = snprintf(config->watch_path, sizeof(config->watch_path), "%s", argv[2]);
    if (written < 0 || (size_t)written >= sizeof(config->watch_path))
        return -1;

    // Server address
    written = snprintf(config->server_ip, sizeof(config->server_ip), "%s", argv[4]);
    if (written < 0 || (size_t)written >= sizeof(config->server_ip))
        return -1;

    // Parse and validate the destination port.
    char *end;
    errno = 0;
    long port = strtol(argv[6], &end, 10);
    if (errno == ERANGE)
    {
        perror("strtol");
        return -1;
    }
    if (end == argv[6] || *end != '\0' || port < 1 || port > 65535)
        return -1;
    config->port = (int)port;

    return 0;
}

void print_config(const AppConfig *config)
{
    puts("MiniGuard configuration");
    printf("watch_path : %s\n", config->watch_path);
    printf("server     : %s\n", config->server_ip);
    printf("port       : %d\n", config->port);
}
