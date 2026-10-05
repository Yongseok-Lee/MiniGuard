#include <sys/inotify.h>
#include <unistd.h>
#include <stdio.h>

#include "watcher.h"

int watcher_run(const char *path)
{
    // Create a blocking inotify instance.
    int fd = inotify_init1(0);
    if (fd == -1)
    {
        perror("inofity_init1");
        return -1;    
    } 

    // Watch file creation, modification, and deletion in the target directory.
    int wd = inotify_add_watch(fd, path, IN_CREATE | IN_MODIFY | IN_DELETE);
    if (wd == -1)
    {
        perror("inofity_add_watch");
        close(fd);
        return -1;    
    } 

    printf("inotify fd: %d\n", fd);
    printf("watch descriptor: %d\n", wd);

    close(fd);
    return 0;
}
