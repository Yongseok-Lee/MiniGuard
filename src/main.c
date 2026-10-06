#include "config.h"
#include "watcher.h"
#include "network.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    AppConfig config;

    if (parse_arguments(argc, argv, &config) != 0)
        return 1;

    print_config(&config);
    putchar('\n');

    int sockfd = network_connect(config.server_host, config.server_port);
    if (sockfd == -1)
        return 1;

    if (watcher_run(config.watch_path) != 0)
        return 1;

    return 0;
}
