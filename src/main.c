#include "config.h"

int main(int argc, char *argv[])
{
    AppConfig config;

    // If argument parsing fails, exit with a failure status.
    if (parse_arguments(argc, argv, &config) != 0)
        return 1;

    print_config(&config);

    return 0;
}
