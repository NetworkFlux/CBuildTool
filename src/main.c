#include "cbt.h"

void	create_directories(cbt_t *cbt)
{
	flx_str	*dir_path;
	int		fd;

	dir_path = flx_strcat(cbt->project_path->str, SRC_DIR, "/");
	if (mkdir(dir_path->str, 0755) != 0 && errno != EEXIST)
		fprintf(stderr, "Failed to create directory. %s\n", strerror(errno));
	if ((fd = open(flx_strcat(dir_path->str, "cbt_main.c", "/")->str, O_CREAT | O_WRONLY, 0644)) == -1 && errno != EEXIST)
		fprintf(stderr, "Failed to create file. %s\n", strerror(errno));
	if (fd != -1)
		close(fd);
	free(dir_path);


	dir_path = flx_strcat(cbt->project_path->str, INCLUDE_DIR, "/");
	if (mkdir(dir_path->str, 0755) != 0 && errno != EEXIST)
		fprintf(stderr, "Failed to create directory. %s\n", strerror(errno));
	if ((fd = open(flx_strcat(dir_path->str, "cbt_include.h", "/")->str, O_CREAT | O_WRONLY, 0644)) == -1 && errno != EEXIST)
		fprintf(stderr, "Failed to create file. %s\n", strerror(errno));
	if (fd != -1)
		close(fd);
	free(dir_path);
}

void	create_cbt_project(cbt_t *cbt)
{
	create_directories(cbt);
}

int main(int argc, char **argv)
{
	cbt_t	*cbt;

	cbt = create_cbt();
	if (argc == 2)
	{
		if (flx_strcmp(argv[1], "init"))
		{
			cbt->project_path = flx_newstr(cbt->cwd->str);
			cbt->project_name = flx_str_path_tail(cbt->project_path, 1);
			printf("Initializing C project in the current directory.\n");
			printf("Current working directory: %s\n", cbt->cwd->str);
			printf("Project path: %s\n", cbt->project_path->str);
			printf("Project name: %s\n", cbt->project_name->str);

			create_cbt_project(cbt);
		}
	}

	destroy_cbt(cbt);
    return (0);
}
