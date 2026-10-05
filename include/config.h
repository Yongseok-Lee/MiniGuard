#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    char watch_path[256];
    char server_ip[64];
    int port;
} AppConfig;

int parse_arguments(int argc, char *argv[], AppConfig *config);
void print_config(const AppConfig *config);

#endif
