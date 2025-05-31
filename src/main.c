#include "cbt.h"

#define SRC_PATH "src"
#define MAIN_PATH SRC_PATH "/main.c"
#define INCLUDE_PATH "include"
#define DOTH_PATH INCLUDE_PATH "/project.h"
#define MAKEFILE_PATH "Makefile"
#define DOTCBT_PATH ".cbt"

#define MAIN_TEMPLATE "templates/default/main.c.cbt"
#define DOTH_TEMPLATE "templates/default/project.h.cbt"
#define MAKEFILE_TEMPLATE "templates/default/Makefile.cbt"


void    create_directory(const char *pathname, const char *directory)
{
    char    fullpath[PATH_SIZE];

    if (directory == NULL)
        snprintf(fullpath, sizeof(fullpath), "%s", pathname);
    else
        snprintf(fullpath, sizeof(fullpath), "%s/%s", pathname, directory);

    if (mkdir(fullpath, 0755) != 0 && errno != EEXIST)
        fprintf(stderr, "Failed to create '%s': %s\n", fullpath, strerror(errno));
    else
        printf("%s directory created!\n", fullpath);
}

void    create_file(const char *pathname, const char *file)
{
    int     fd;
    char    fullpath[PATH_SIZE];

    snprintf(fullpath, sizeof(fullpath), "%s/%s", pathname, file);
    if ((fd = open(fullpath, O_CREAT | O_WRONLY, 0644)) == -1 && errno != EEXIST)
        fprintf(stderr, "Failed to create '%s': %s\n", fullpath, strerror(errno));
    else
        printf("%s file created!\n", fullpath);

    if (fd != -1)
        close(fd);
}

void    create_project_structure(Path *path)
{
    if (path->is_default == FALSE)
        create_directory(path->path, NULL);

    create_directory(path->path, SRC_PATH);
    create_file(path->path, MAIN_PATH);
    create_directory(path->path, INCLUDE_PATH);
    create_file(path->path, DOTH_PATH);
    create_file(path->path, MAKEFILE_PATH);
    create_file(path->path, DOTCBT_PATH);
}

void    fill_project_files(Path *path)
{
    char    fullpath[PATH_SIZE];

    snprintf(fullpath, sizeof(fullpath), "%s/%s", path->path, MAIN_PATH);
    copy_file(MAIN_TEMPLATE, fullpath);
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path->path, DOTH_PATH);
    copy_file(DOTH_TEMPLATE, fullpath);
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path->path, MAKEFILE_PATH);
    copy_file(MAKEFILE_TEMPLATE, fullpath);
}

void    init_cbt_project(char *pathname)
{
    Path    *path;

    path = init_path();
    if (pathname)
    {
        path->path = strdup(pathname);
        path->is_default = FALSE;
    }
    
    if (file_exists_in_path(path->path, ".cbt"))
    {
        printf("Project already initialized!\n");
        return ;
    }

    create_project_structure(path);
    fill_project_files(path);

    destroy_path(path);

    printf("Project successfully initialized!\n");
}

int main(int argc, char **argv)
{
    if (argc > 1)
    {
        if (strcmp(argv[1], "init") == 0)
        {
            if (argc == 2)
            {
                printf("Detected command: %s\n", argv[1]);
                init_cbt_project(NULL);
            }
            if (argc == 3)
            {
                printf("Detected command: %s %s\n", argv[1], argv[2]);
                init_cbt_project(argv[2]);
            }
        }
        else
            printf("No known command detected for cbt: %s is not a cbt command.\n", argv[1]);
    }
    return (0);
}