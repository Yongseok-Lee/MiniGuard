#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "config.h"

int parse_arguments(int argc, char *argv[], AppConfig *config)
{
    // argc must be 7
    if (argc != 7)
        return -1;

    // option arguments must be -d, -h, and -p
    if (strcmp(argv[1], "-d") || strcmp(argv[3], "-h") || strcmp(argv[5], "-p"))
        return -1;

    // argv[2] and argv[4] must not be empty string
    if (argv[2][0] == '\0' || argv[4][0] == '\0')
        return -1;

    // watch path
    int written;
    written = snprintf(config->watch_path, sizeof(config->watch_path), "%s", argv[2]);
    if (written < 0 || (size_t)written >= sizeof(config->watch_path))
        return -1;

    // server ip
    written = snprintf(config->server_ip, sizeof(config->server_ip), "%s", argv[4]);
    if (written < 0 || (size_t)written >= sizeof(config->server_ip))
        return -1;

    // port
    char *end;
    errno = 0;
    long port = strtol(argv[6], &end, 10);
    if (errno == ERANGE || end == argv[6] || *end != '\0' || port < 1 || port > 65535)
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
