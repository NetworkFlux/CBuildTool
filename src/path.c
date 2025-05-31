#include "cbt.h"

Path    *init_path(void)
{
    Path    *path;

    if (!(path = malloc(sizeof(Path))))
    {
        fprintf(stderr, "Failed to malloc a Path: %s\n", strerror(errno));
        return (NULL);
    }

    path->user_path = strdup(".");
    path->custom = 0;

    return (path);
}