#include "watcher.h"

#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>

int watcher_run(const char *watch_path)
{
    // Create a blocking inotify instance.
    int fd = inotify_init1(0);
    if (fd == -1)
    {
        perror("inofity_init1");
        return -1;    
    } 

    // Watch for file creation, modification, deletion, and move events.
    const uint32_t watch_mask =
        IN_CREATE     |
        IN_MODIFY     |
        IN_DELETE     |
        IN_MOVED_FROM |
        IN_MOVED_TO;

    int wd = inotify_add_watch(fd, watch_path, watch_mask);
    if (wd == -1)
    {
        perror("inofity_add_watch");
        close(fd);
        return -1;    
    } 

    printf("inotify fd: %d\n", fd);
    printf("watch descriptor: %d\n", wd);

    // Align the raw buffer for inotify_event access.
    _Alignas(struct inotify_event) char buffer[4096];

    while (1)
    {
        // Read the next batch of inotify events.
        ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
        if (bytes_read == -1)
        {
            perror("read");
            close(fd);
            return -1;
        }

        // Process all events returned by read().
        size_t offset = 0;
        while (offset < (size_t)bytes_read)
        {
            struct inotify_event *event = (struct inotify_event *)(buffer + offset);

            if (event->mask & IN_CREATE)
                printf("CREATE %s\n", event->name);

            if (event->mask & IN_MODIFY)
                printf("MODIFY %s\n", event->name);

            if (event->mask & IN_DELETE)
                printf("DELETE %s\n", event->name);

            if (event->mask & IN_MOVED_FROM)
                printf("MOVED_FROM %s\n", event->name);

            if (event->mask & IN_MOVED_TO)
                printf("MOVED_TO %s\n", event->name);

            offset += sizeof(struct inotify_event) + event->len;
        }
    }

    close(fd);
    return 0;
}
