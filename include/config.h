#ifndef CONFIG_H
#define CONFIG_H

typedef struct
{
    char watch_path[256];
    char server_host[64];
    int server_port;
} AppConfig;

int parse_arguments(int argc, char *argv[], AppConfig *config);
void print_config(const AppConfig *config);

#endif
