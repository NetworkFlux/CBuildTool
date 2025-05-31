#include "cbt.h"
#include "cbt_portability.h"
#include "flux.h"

#define SRC_PATH "./cbt_src"
#define MAIN_PATH SRC_PATH "/main.c"
#define INCLUDE_PATH "./cbt_include"
#define DOTH_PATH INCLUDE_PATH "/project.h"
#define MAKEFILE_PATH "./cbt_Makefile"

#define MAIN_TEMPLATE "./templates/default/main.c.cbt"
#define DOTH_TEMPLATE "./templates/default/project.h.cbt"
#define MAKEFILE_TEMPLATE "./templates/default/Makefile.cbt"

void    create_project_structure(void)
{
    // Create src directory
    if (mkdir(SRC_PATH, 0755) != 0)
    {
        if (errno != EEXIST)
            fprintf(stderr, "Failed to create '%s': %s\n", SRC_PATH, strerror(errno));
    }
    printf("%s directory created!\n", SRC_PATH);
    // Create main.c file
    if (open(MAIN_PATH, O_CREAT, 0644) == -1)
    {
        if (errno != EEXIST)
            fprintf(stderr, "Failed to create '%s': %s\n", MAIN_PATH, strerror(errno));
    }
    printf("%s file created!\n", MAIN_PATH);
    // Create include directory
    if (mkdir(INCLUDE_PATH, 0755) != 0)
    {
        if (errno != EEXIST)
            fprintf(stderr, "Failed to create '%s': %s\n", INCLUDE_PATH, strerror(errno));
    }
    printf("%s directory created!\n", INCLUDE_PATH);
    // Create project.h file
    if (open(DOTH_PATH, O_CREAT, 0644) == -1)
    {
        if (errno != EEXIST)
            fprintf(stderr, "Failed to create '%s': %s\n", DOTH_PATH, strerror(errno));
    }
    printf("%s file created!\n", DOTH_PATH);

    // Create Makefile
    if (open(MAKEFILE_PATH, O_CREAT, 0644) == -1)
    {
        if (errno != EEXIST)
            fprintf(stderr, "Failed to create '%s': %s\n", MAKEFILE_PATH, strerror(errno));
    }
    printf("%s file created!\n", MAKEFILE_PATH);
}

void    fill_project_files()
{
    copy_file(MAIN_TEMPLATE, MAIN_PATH);
    copy_file(DOTH_TEMPLATE, DOTH_PATH);
    copy_file(MAKEFILE_TEMPLATE, MAKEFILE_PATH);
}

void    init_cbt_project(void)
{
    create_project_structure();
    fill_project_files();
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        // One program argument
        if (strcmp(argv[1], "init") == 0)
        {
            printf("Detected command: %s\n", argv[1]);
            init_cbt_project();
        }
        else
            printf("No known command detected for cbt: %s is not a cbt command.\n", argv[1]);
    }
    return (0);
}