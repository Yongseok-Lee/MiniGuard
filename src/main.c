#include <stdio.h>

#include "config.h"
#include "watcher.h"

int main(int argc, char *argv[])
{
    AppConfig config;

    if (parse_arguments(argc, argv, &config) != 0)
        return 1;

    print_config(&config);
    putchar('\n');

    if (watcher_run(config.watch_path) != 0)
        return 1;

    return 0;
}
