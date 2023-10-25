#include "c_builder.h"

int	main(int argc, char **argv)
{
    project_t   *project;
	char	    *cwd;

	if (argc != 1)
		err_n_die("Usage: %s", argv[0]);

    project = create_project();

	if (!(cwd = getcwd(project->path, MAX_PATH)))
		err_n_die("getcwd() failed");
	
	printf(COLOR_CYAN "Enter project name: " COLOR_RESET);
	scanf("%s", project->name);
	if (project->name[0] == '\0')
		err_n_die("Project name cannot be empty");

	sprintf(project->path, "%s/%s", cwd, project->name);

	printf(COLOR_GREEN "Creating project ...\n" COLOR_RESET);

	if (mkdir(project->name, 0777) < 0)
		err_n_die("mkdir() failed in main()");

	printf(COLOR_GREEN "Project created successfully at %s\n" COLOR_RESET, project->path);

	fill_project(project);

    delete_project(project);

	return (0);
}
