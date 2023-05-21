#include "c_builder.h"

int fill_project(char *pro_path, char *pro_name, int lang)
{
	char	temp_path[MAX_PATH];
	FILE	*main_fd, *include_fd, *makefile_fd;

	sprintf(temp_path, "%s/src", pro_path);

	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");

	if (lang == 0)
		sprintf(temp_path, "%s/src/main.c", pro_path);
	else if (lang == 1)
		sprintf(temp_path, "%s/src/main.cpp", pro_path);

	if ((main_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(main_fd, "main.txt", pro_name, lang);
	fclose(main_fd);

	sprintf(temp_path, "%s/include", pro_path);

	if (mkdir(temp_path, 0777) < 0)
		err_n_die("mkdir() failed");

	if (lang == 0)
		sprintf(temp_path, "%s/include/%s.h", pro_path, pro_name);
	else if (lang == 1)
		sprintf(temp_path, "%s/include/%s.hpp", pro_path, pro_name);

	if ((include_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(include_fd, "include.txt", pro_name, lang);
	fclose(include_fd);

	sprintf(temp_path, "%s/Makefile", pro_path);

	if ((makefile_fd = fopen(temp_path, "w+")) == NULL)
		err_n_die("fopen() failed");

	copy_file_content(makefile_fd, "Makefile.txt", pro_name, lang);
	fclose(makefile_fd);
	return (0);
}

void copy_file_content(FILE *fd, const char *input_file, const char *project_name, int lang)
{
	FILE *inputFile;
	char input_path[MAX_PATH];
	char line[256];
	size_t line_nb = 0;

	if (lang == 0)
		sprintf(input_path, "/usr/local/share/CBuildTool/templates/c/%s", input_file);
	else if (lang == 1)
		sprintf(input_path, "/usr/local/share/CBuildTool/templates/c++/%s", input_file);

	inputFile = fopen(input_path, "r");
	if (inputFile == NULL)
	{
		if (lang == 0)
			sprintf(input_path, "%s/templates/c/%s", getcwd(NULL, MAX_PATH), input_file);
		else if (lang == 1)
			sprintf(input_path, "%s/templates/c++/%s", getcwd(NULL, MAX_PATH), input_file);
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
		{
			if (lang == 0)
				fprintf(fd, "#include \"%s.h\"\n", project_name);
			else if (lang == 1)
				fprintf(fd, "#include \"%s.hpp\"\n", project_name);
		}
		else if (strstr(input_file, "Makefile") != NULL && line_nb == 0)
			fprintf(fd, "EXEC = %s\n", project_name);
		else
			fputs(line, fd);
		line_nb++;
	}

	fclose(inputFile);
}

