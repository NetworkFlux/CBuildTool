#include "c_builder.h"

int fill_project(project_t *project)
{
	char	temp_path[MAX_PATH];
	FILE	*main_fd, *include_fd, *makefile_fd, *compile_fd;

	sprintf(temp_path, "%s/src", project->path);

	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");

	sprintf(temp_path, "%s/src/main.c", project->path);

	if ((main_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(main_fd, "main.txt", project->name);
	fclose(main_fd);

	sprintf(temp_path, "%s/include", project->path);

	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");

	sprintf(temp_path, "%s/include/%s.h", project->path, project->name);

	if ((include_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(include_fd, "include.txt", project->name);
	fclose(include_fd);

	sprintf(temp_path, "%s/Makefile", project->path);

	if ((makefile_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(makefile_fd, "Makefile.txt", project->name);
	fclose(makefile_fd);
	
	sprintf(temp_path, "%s/compile_commands.json", project->path);
    
    if ((compile_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(compile_fd, "compile_commands.txt", project->name);
	fclose(compile_fd);
	return (0);
}

void copy_file_content(FILE *fd, const char *input_file, const char *project_name)
{
	FILE *inputFile;
	char input_path[MAX_PATH];
	char line[256];
	size_t line_nb = 0;

	sprintf(input_path, "/usr/local/share/CBuildTool/templates/c/%s", input_file);

	inputFile = fopen(input_path, "r");
	if (inputFile == NULL)
	{
		sprintf(input_path, "%s/templates/c/%s", getcwd(NULL, MAX_PATH), input_file);
		inputFile = fopen(input_path, "r");
	}

	if (inputFile == NULL)
	{
		printf("Error: unable to open input file %s\n", input_file);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), inputFile))
	{
		if (strstr(input_file, "main") != NULL && line_nb == 0)
			fprintf(fd, "#include \"%s.h\"\n", project_name);
		else if (strstr(input_file, "Makefile") != NULL && line_nb == 0)
			fprintf(fd, "EXEC = %s\n", project_name);
		else
			fputs(line, fd);
		line_nb++;
	}

	fclose(inputFile);
}

