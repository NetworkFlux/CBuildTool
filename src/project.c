#include "c_builder.h"
#include <stdlib.h>

project_t   *create_project(void)
{
    project_t   *project;

    project = malloc(sizeof(project_t));
    if (!project)
        err_n_die("malloc() failed in create_project {0}");

    project->name = malloc(sizeof(char) * MAX_NAME);
    if (!project->name)
        err_n_die("malloc() failed in create_project {1}");
    
    project->path = malloc(sizeof(char) * MAX_PATH);
    if (!project->path)
        err_n_die("malloc() failed in create_project {2}");

    return (project);
}

void    delete_project(project_t *project)
{
    if (project)
        free(project);
}
